#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

#include "../include/Usuario.hpp"
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/Post.hpp"
#include "../include/Interface.hpp"

#define dbg(x) std::cout << #x << " = " << x << '\n'

/**
 * @brief construtor da classe Usuario
 * @param nome nome do usuario
 * @return ponteiro para Usuario
*/
Usuario::Usuario(std::string nome) : nome(nome), gerenciadorNotificacoes(GerenciadorNotificacoes(this)){
    mkDir(nome);
}

/**
 * @brief destrutor da classe usuario, desaloca a memoria alocada
*/
Usuario::~Usuario(){
    this->gerenciadorNotificacoes.clear();
}

/**
 * @brief caso nao exista, cria as pastas e txt referentes a um usuario no sistema
 * @param nome nome do usuario
 * @return void
*/
void Usuario::mkDir(std::string nome){
    if(Usuario::isValid(nome)) return;

    // criando a pasta com o nome do usuario
    std::string mkdirCommand = "mkdir ";
    mkdirCommand += this->getUserFolderPath();
    system(mkdirCommand.c_str());

    //criando a pasta "feed"
    mkdirCommand = "mkdir ";
    mkdirCommand += this->getFeedFolderPath();
    system(mkdirCommand.c_str());
    
    // criando o arquivo "foto.png"
    std::string cpCommand = "cp usuarios/fotoPadrao.png ";
    cpCommand += this->getFotoFilePath();
    system(cpCommand.c_str());


    FILE* ptr = NULL;
    //criando o arquivo "followers.txt": armazena os nomes dos usuarios que seguem o usuario
    ptr = fopen(this->getFollowersFilePath().c_str(), "w");
    fclose(ptr);

    //criando o arquivo "following.txt": armazena os nomes dos usuarios que o usuario segue
    ptr = fopen(this->getFollowingFilePath().c_str(), "w");
    fclose(ptr);

    //criando o arquivo "quantidadePosts.txt": armazena a quantidade de IDs de posts do proprio usuario
    ptr = fopen(this->getQuantidadePostsFilePath().c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    //criando o arquivo "quantidadeFeed.txt": armazena a quantidade de IDs que tem no arquivo "feed.txt"
    ptr = fopen(this->getQuantidadeFeedFilePath().c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    // //criando o arquivo "posts.txt" : armazena os IDs dos posts que o proprio usuario postou
    // ptr = fopen(this->getSelfPostsFilePath().c_str(), "w");
    // fclose(ptr);
}

/**
 * @brief carrega o gerenciador de notificacoes do usuario com os usuarios que o seguem
 * @return void
*/
void Usuario::loadGerenciadorNotificacoes(){
    gerenciadorNotificacoes.clear();
    for(auto x: getFollowers()){
        Usuario* u = new Usuario(x.getNome());
        this->gerenciadorNotificacoes.adicionar(u);
    }
}

/**
 * @brief retorna se um usuario esta cadastrado no sistema
 * @param name nome do usuario
 * @return bool caso o usuario estiver cadastrado, false caso contrario
*/
bool Usuario::isValid(std::string name){
    std::string path = "usuarios/cadastrados/";
    path += name;
    path += "/quantidadePosts.txt";

    FILE* ptr = fopen(path.c_str(), "r");
    if(ptr){
        fclose(ptr);
        return true;
    }
    return false;
}

/**
 * @brief retorna o nome do usuario
 * @return string com o nome do usuario
*/
std::string Usuario::getNome() {
    return nome;
}

/**
 * @brief publica um post de um usuario
 * @param msg mensagem do post a ser publicado
 * @return void
*/
void Usuario::publicar(std::string msg) {
    int id = Post::getTotalPosts() + 1;
    
    //criando o novo post
    Post::newPost(id, msg, this->getNome());

    //adicionando o post ao feed do usuario
    addPostToFeed(this->getNome(), id);

    //atualizando a quantidade de posts do usuario
    this->setQuantidadePosts(this->getQuantidadePosts() + 1);

    gerenciadorNotificacoes.notificarTodos(id);
}

/**
 * @brief adiciona um post ao feed do usuario
 * @param user nome do usuario
 * @param id id do post a ser adicionado
 * @return void
*/
void Usuario::addPostToFeed(std::string user, int id){
    std::string feedFilePath = this->getFeedFilePath(user);
    FILE* feedFilePointer = fopen(feedFilePath.c_str(), "a");
    if(!feedFilePointer) feedFilePointer = fopen(feedFilePath.c_str(), "w");

    fprintf(feedFilePointer, "%d\n", id);
    fclose(feedFilePointer);
}

/**
 * @brief o usuario começa a seguir o username
 * @param username usuario que está sendo seguido
 * @return void
*/
void Usuario::seguir(std::string username) {
    if(this->nome == username) return;

    if(!isFollowing(username)){
        Usuario usuario(username);
        
        //adicionando no arquivo followers do outro usuario
        std::string followersFilePath = usuario.getFollowersFilePath();
        FILE* followersFilePointer = fopen(followersFilePath.c_str(), "r");
        followersFilePointer = fopen(followersFilePath.c_str(), "a");
        fprintf(followersFilePointer, "%s\n", nome.c_str());
        fclose(followersFilePointer);

        //adicionando no arquivo following desse usuario
        std::string followingFilePath = this->getFollowingFilePath();
        FILE* followingFilePointer = fopen(followingFilePath.c_str(), "a");
        fprintf(followersFilePointer, "%s\n", username.c_str());
        fclose(followersFilePointer);

        //adicionando o arquivo do usuario no feed desse usuario
        std::string feedFilePath = this->getFeedFilePath(username);
        FILE* feedFilePointer = fopen(feedFilePath.c_str(), "w");
        fclose(feedFilePointer);
    }
}

/**
 * @brief o usuario para de seguir o outro
 * @param usuario usuario que está sendo seguido
 * @return void
*/
void Usuario::desseguir(std::string usuario){

    //removendo do arquivo following.txt desse usuario
    auto following = this->getFollowing();
    FILE* followingFilePointer = fopen(this->getFollowingFilePath().c_str(), "w");
    for(auto u: following){
        if(u.getNome() == usuario) continue;
        fprintf(followingFilePointer, "%s\n", u.getNome().c_str());
    }
    fclose(followingFilePointer);

    //removendo do arquivo followers.txt
    Usuario user2(usuario);
    FILE* followersFilePointer = fopen(user2.getFollowersFilePath().c_str(), "w");
    auto followers = user2.getFollowers();
    for(auto u: followers){
        if(u.getNome() == this->getNome()) continue;
        fprintf(followersFilePointer, "%s\n", u.getNome().c_str());
    }
    fclose(followersFilePointer);

    //removendo do gerenciador de notificacoes do outro usuario
    user2.gerenciadorNotificacoes.remover(this);

    //removendo o usuario2 do feed desse usuario
    std::string rmFeedCommand = "rm ";
    rmFeedCommand += getFeedFilePath(usuario);
    system(rmFeedCommand.c_str());
}

/**
 * @brief o usuario atual recebe uma notificação de que o usuario autor publicou um post.
 * @param postId id do post do autor
 * @return void
*/
void Usuario::notificar(std::string autor, int postId) {
    addPostToFeed(autor, postId);
}

/**
 * @brief retorna a quantidade de posts que o usuario ja fez
 * @return int, quantidade de posts
*/
int Usuario::getQuantidadePosts(){
    int quantidade;
    
    std::string quantidadePostsFilePath = this->getQuantidadePostsFilePath();
    FILE* quantidadePostsFilePointer = fopen(quantidadePostsFilePath.c_str(), "r");

    fscanf(quantidadePostsFilePointer, "%d", &quantidade);

    fclose(quantidadePostsFilePointer);

    return quantidade;
}

/**
 * @brief seta a quantidade de posts de um usuario para um valor
 * @param quantidade quantidade de posts a ser setado
 * @return void
*/
void Usuario::setQuantidadePosts(int quantidade){
    std::string quantidadePostsFilePath = this->getQuantidadePostsFilePath();

    FILE* quantidadePostsFilePointer = fopen(quantidadePostsFilePath.c_str(), "w");
    fprintf(quantidadePostsFilePointer, "%d\n", quantidade);

    fclose(quantidadePostsFilePointer);
}

/**
 * @brief retorna uma string com o caminho para a pasta do usuario
 * @return string
*/
std::string Usuario::getUserFolderPath(){
    std::string userFolderPath = "usuarios/cadastrados/";
    userFolderPath += this->getNome();
    userFolderPath += "/";
    return userFolderPath;
}


/**
 * @brief retorna uma string com o caminho para o arquivo de quantidade de posts do usuario
 * @return string
*/
std::string Usuario::getQuantidadePostsFilePath(){
    std::string quantidadePostsFilePath = this->getUserFolderPath();
    quantidadePostsFilePath += "quantidadePosts.txt";
    return quantidadePostsFilePath;
}


/**
 * @brief retorna uma string com o caminho para o arquivo de seguidores do usuario
 * @return string
*/
std::string Usuario::getFollowersFilePath(){
    std::string followersFilePath = this->getUserFolderPath();
    followersFilePath += "followers.txt";
    return followersFilePath;
}

/**
 * @brief retorna uma string com o caminho para o arquivo de pessoas que o usuario segue
 * @return string
*/
std::string Usuario::getFollowingFilePath(){
    std::string followingFilePath = this->getUserFolderPath();
    followingFilePath += "following.txt";
    return followingFilePath;
}

/**
 * @brief retorna uma string com o caminho para a foto de perfil desse usuario
 * @return string com o caminho para a foto
*/
std::string Usuario::getFotoFilePath(){
    std::string fotoFilePath = this->getUserFolderPath();
    fotoFilePath += "foto.png";
    return fotoFilePath;
}

/**
 * @brief retorna uma string com o caminho para o arquivo que contem o total de posts no feed
 * @return string
*/
std::string Usuario::getQuantidadeFeedFilePath(){
    std::string feedFilePath = this->getUserFolderPath();
    feedFilePath += "quantidadeFeed.txt";
    return feedFilePath;
}

/**
 * @brief seta a quantidade de pastas tem no feed desse usuario para um determinado valor
 * @param v valor a ser setado
 * @return void
*/
void Usuario::setQuantidadeFeed(int v){
    std::string quantidadeFeedFilePath = this->getQuantidadeFeedFilePath();
    FILE* quantidadeFeedFilePointer = fopen(quantidadeFeedFilePath.c_str(), "w");
    fprintf(quantidadeFeedFilePointer, "%d\n", v);
    fclose(quantidadeFeedFilePointer);
}

/**
 * @brief retorna uma string com o caminho para a pasta de feed do usuario
 * @param post identificador do post a ser buscado (de 1 ate o numero em quantidadeFeed)
 * @return string
*/
std::string Usuario::getFeedFilePath(std::string username){
    std::string feedFilePath = this->getFeedFolderPath();
    feedFilePath += username;
    feedFilePath += ".txt";
    return feedFilePath;
}

/**
 * @brief retorna uma string com o caminho para a pasta de feed desse usuario
 * @return string com o caminho para a pasta de feed
*/
std::string Usuario::getFeedFolderPath(){
    std::string feedFolderPath = this->getUserFolderPath();
    feedFolderPath += "feed/";
    return feedFolderPath;
}

/**
 * @brief retorna a quantidade de elementos do feed do usuario
 * @return int quantidade de IDs no arquivo "feed.txt" do usuario
*/
int Usuario::getQuantidadeFeed(){
    std::string quantidadeFeedFilePath = this->getQuantidadeFeedFilePath();
    FILE* quantidadeFeedFilePointer = fopen(quantidadeFeedFilePath.c_str(), "r");
    int qtd;
    fscanf(quantidadeFeedFilePointer, "%d", &qtd);
    fclose(quantidadeFeedFilePointer);
    return qtd;
}

/**
 * @brief retorna um vector com todos os posts presentes no feed desse usuario
 * @return vector<Post> com os posts do feed do usuario
*/
std::vector<Post> Usuario::loadFeed(){
    std::vector<Post> posts = loadSelfPosts();

    for(auto x: this->getFollowing()){
        FILE* feedFilePointer = fopen(getFeedFilePath(x.getNome()).c_str(), "r");
        if(!feedFilePointer) continue;

        int id;
        while( fscanf(feedFilePointer, "%d", &id) != EOF ) {
            if(Post::isValid(id)){
                Post p(id);
                posts.push_back(p);
            }

        }

        fclose(feedFilePointer);
    }

    //organizando em ordem cronologica
    sort(posts.begin(), posts.end(), [](Post p1, Post p2){ return p1.getID() > p2.getID(); });

    return posts;
}

/**
 * @brief retorna um vector de posts com os posts publicados por esse usuario
 * @return vector<Post> com os posts publicados por esse usuario
*/
std::vector<Post> Usuario::loadSelfPosts(){
    std::vector<Post> posts;
    posts.clear();

    std::string selfPostFilePath = this->getSelfPostsFilePath();
    FILE* selfPostFilePointer = fopen(selfPostFilePath.c_str(), "r");

    for(int i = 1; i <= getQuantidadePosts(); i++){
        int id;

        fscanf(selfPostFilePointer, "%d", &id);
        Post newPost(id);

        posts.push_back(newPost);
    }

    //ordenando em ordem cronologica
    sort(posts.begin(), posts.end(), [](Post p1, Post p2){ return p1.getID() > p2.getID(); });
    return posts;
}

/**
 * @brief retorna um vector de usuarios que esse usuario segue
 * @return vector<Usuario> com os usuarios que esse usuario segue
*/
std::vector<Usuario> Usuario::getFollowing(){
    std::vector<Usuario> following;

    std::string followingFilePath = this->getFollowingFilePath();

    FILE* followingFilePointer = fopen(followingFilePath.c_str(), "r");

    char nome[100];
    while(fscanf(followingFilePointer, "%[^\n]%*c", nome) != EOF){
        std::string username = nome;
        following.push_back(Usuario(username));
    }

    fclose(followingFilePointer);

    //ordenando em ordem alfabetica
    sort(following.begin(), following.end(), [](Usuario a, Usuario b){ return a.getNome() < b.getNome(); });
    return following;
}

/**
 * @brief retorna um vector de usuarios que seguem esse usuario
 * @return vector<Usuario> com os usuarios que seguem esse usuario
*/
std::vector<Usuario> Usuario::getFollowers(){
    std::vector<Usuario> followers;

    std::string followersFilePath = this->getFollowersFilePath();

    FILE* followersFilePointer = fopen(followersFilePath.c_str(), "r");

    char nome[100];
    while(fscanf(followersFilePointer, "%[^\n]%*c", nome) != EOF){
        std::string username = nome;
        followers.push_back(Usuario(username));
    }

    fclose(followersFilePointer);   

    //ordenando em ordem alfabetica
    sort(followers.begin(), followers.end(), [](Usuario a, Usuario b){ return a.getNome() < b.getNome(); });
    
    return followers;
}

/**
 * @brief retorna um booleano se o usuario segue o usuario de nome "user"
 * @param user nome do usuario que é seguido
 * @return bool
*/
bool Usuario::isFollowing(std::string user){

    for(auto u : this->getFollowing()){
        if(u.getNome() == user){
            return true;
        }
    }

    return false;
}

/**
 * @brief apaga esse usuario do sistema, deletando todos seus registros
 * @return void
*/
void Usuario::apagarUsuario(){

    for(auto x: this->getFollowing()){
        this->desseguir(x.getNome());
    }

    for(auto x: this->getFollowers()){
        x.desseguir(this->getNome());
    }

    std::string userFolderPath = this->getUserFolderPath();

    std::string rmCommand = "rm -rf ";
    rmCommand += userFolderPath;
    system(rmCommand.c_str());

    FILE* ptr = fopen(Interface::LOGIN_DATA_FILE_PATH, "r");
    FILE* ptr2 = fopen("temp.txt", "w");

    char name[100], senha[100];
    while(fscanf(ptr, "%[^,],%[^\n]%*c", name, senha) != EOF){
        std::string atual = name;
        if(atual == getNome()){
            continue;
        }
        fprintf(ptr2, "%s,%s\n", name, senha);
    }

    fclose(ptr);
    fclose(ptr2);

    rmCommand = "rm ";
    rmCommand += Interface::LOGIN_DATA_FILE_PATH;
    system(rmCommand.c_str());

    rmCommand = "mv temp.txt ";
    rmCommand += Interface::LOGIN_DATA_FILE_PATH;
    system(rmCommand.c_str());
}

/**
 * @brief retorna uma string com o caminho para o arquivo de posts desse usuario
 * @return string com o caminho para o arquivo de posts desse usuario
*/
std::string Usuario::getSelfPostsFilePath(){
    std::string selfPostsFilePath = this->getFeedFilePath(this->getNome());
    return selfPostsFilePath;
}