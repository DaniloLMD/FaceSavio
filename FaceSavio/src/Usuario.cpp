#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

#include "../include/Usuario.hpp"
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/Post.hpp"

#define dbg(x) std::cout << #x << " = " << x << '\n'

/**
 * @brief construtor da classe Usuario
 * @param nome nome do usuario
 * @return ponteiro para Usuario
*/
Usuario::Usuario(std::string nome) : nome(nome), gerenciadorNotificacoes(new GerenciadorNotificacoes(this)){
    mkDir(nome);
}

void Usuario::mkDir(std::string nome){
    if(Usuario::isValid(nome)) return;

    // criando a pasta com o nome do usuario
    std::string mkdirCommand = "mkdir ";
    mkdirCommand += this->getUserFolderPath();
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

    //criando o arquivo "quantidadePosts.txt": armazena a quantidade de IDs que tem no arquivo "posts.txt"
    ptr = fopen(this->getQuantidadePostsFilePath().c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    //criando o arquivo "quantidadeFeed.txt": armazena a quantidade de IDs que tem no arquivo "feed.txt"
    ptr = fopen(this->getQuantidadeFeedFilePath().c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    //criando o arquivo "posts.txt" : armazena os IDs dos posts que o proprio usuario postou
    ptr = fopen(this->getSelfPostsFilePath().c_str(), "w");
    fclose(ptr);

    //criando o arquivo "feed.txt": armazena os IDs dos posts do proprio usuario e de quem ele segue
    ptr = fopen(this->getFeedFilePath().c_str(), "w");
    fclose(ptr);
}

void Usuario::loadGerenciadorNotificacoes(){
    gerenciadorNotificacoes->clear();
    for(auto x: getFollowers()){
        gerenciadorNotificacoes->adicionar(x);
    }
}

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
    // std::cout << "Eu " << nome << ", publiquei a mensagem '" << msg << "'.\n";

    int id = Post::getTotalPosts() + 1;

    //criando o novo post
    Post::newPost(id, msg, this->getNome());

    //atualizando o arquivo "posts.txt" do usuario com o ID do seu proprio post
    std::string selfPostsFilePath = this->getSelfPostsFilePath();
    FILE* selfPostsFilePointer = fopen(selfPostsFilePath.c_str(), "a");
    fprintf(selfPostsFilePointer, "%d\n", id);
    fclose(selfPostsFilePointer);

    //adicionando o post ao feed do usuario
    addPostToFeed(id);

    //atualizando a quantidade de posts do usuario
    this->setQuantidadePosts(this->getQuantidadePosts() + 1);

    gerenciadorNotificacoes->notificarTodos(id);
}

void Usuario::addPostToFeed(int id){
    std::string feedFilePath = this->getFeedFilePath();
    FILE* feedFilePointer = fopen(feedFilePath.c_str(), "a");
    fprintf(feedFilePointer, "%d\n", id);
    fclose(feedFilePointer);
    setQuantidadeFeed(getQuantidadeFeed() + 1);
}

/**
 * @brief o usuario começa a seguir o username
 * @param username usuario que está sendo seguido
 * @return void
*/
void Usuario::seguir(std::string username) {
    if(this->nome == username) return;

    if(!isFollowing(username)){
        Usuario* usuario = new Usuario(username);
        
        std::string followersFilePath = usuario->getFollowersFilePath();
        std::string followingFilePath = this->getFollowingFilePath();

        FILE* followersFilePointer = fopen(followersFilePath.c_str(), "r");
        followersFilePointer = fopen(followersFilePath.c_str(), "a");
        fprintf(followersFilePointer, "%s\n", nome.c_str());
        fclose(followersFilePointer);

        FILE* followingFilePointer = fopen(followingFilePath.c_str(), "a");
        fprintf(followersFilePointer, "%s\n", username.c_str());
        fclose(followersFilePointer);
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
        if(u->getNome() == usuario) continue;
        fprintf(followingFilePointer, "%s\n", u->getNome().c_str());
    }
    fclose(followingFilePointer);

    //removendo do arquivo followers.txt e do gerenciador de notificacoes do outro usuario
    Usuario* user2 = new Usuario(usuario);
    FILE* followersFilePointer = fopen(user2->getFollowersFilePath().c_str(), "w");
    auto followers = user2->getFollowers();
    for(auto u: followers){
        if(u->getNome() == this->getNome()) continue;
        fprintf(followersFilePointer, "%s\n", u->getNome().c_str());
    }
    fclose(followersFilePointer);

    user2->gerenciadorNotificacoes->remover(this);
}

/**
 * @brief o usuario atual recebe uma notificação de que o usuario autor publicou um post.
 * @param postId id do post do autor
 * @return void
*/
void Usuario::notificar(int postId) {
    // std::cout << "Sou o usuario " << nome << " e o usuario " << autor << " publicou a mensagem: '" << (new Post(postId))->getTexto() << "'.\n";
    addPostToFeed(postId);
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
std::string Usuario::getFeedFilePath(){
    std::string feedFilePath = this->getUserFolderPath();
    feedFilePath += "feed.txt";
    return feedFilePath;
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

std::vector<Post*> Usuario::loadFeed(){
    posts.clear();
    FILE* feedFilePointer = fopen(getFeedFilePath().c_str(), "r");
    for(int i = 0; i < this->getQuantidadeFeed(); i++){
        int id;
        fscanf(feedFilePointer, "%d", &id);
        Post* p = new Post(id);
        posts.push_back(p);
    }
    fclose(feedFilePointer);

    //organizando em ordem cronologica
    sort(posts.begin(), posts.end(), [](Post* p1, Post* p2){ return p1->getID() > p2->getID(); });

    return posts;
}

std::vector<Post*> Usuario::loadSelfPosts(){
    posts.clear();

    std::string selfPostFilePath = this->getSelfPostsFilePath();
    FILE* selfPostFilePointer = fopen(selfPostFilePath.c_str(), "r");

    for(int i = 1; i <= getQuantidadePosts(); i++){
        int id;

        fscanf(selfPostFilePointer, "%d", &id);
        Post* newPost = new Post(id);
        posts.push_back(newPost);
    }

    //ordenando em ordem cronologica
    sort(posts.begin(), posts.end(), [](Post* p1, Post* p2){ return p1->getID() > p2->getID(); });
    return posts;
}

std::vector<Usuario*> Usuario::getFollowing(){
    std::vector<Usuario*> following;

    std::string followingFilePath = this->getFollowingFilePath();

    FILE* followingFilePointer = fopen(followingFilePath.c_str(), "r");

    char nome[100];
    while(fscanf(followingFilePointer, "%[^\n]%*c", nome) != EOF){
        std::string username = nome;
        following.push_back(new Usuario(username));
    }

    fclose(followingFilePointer);

    //ordenando em ordem alfabetica
    sort(following.begin(), following.end(), [](Usuario* a, Usuario* b){ return a->getNome() < b->getNome(); });
    return following;
}

std::vector<Usuario*> Usuario::getFollowers(){
    std::vector<Usuario*> followers;

    std::string followersFilePath = this->getFollowersFilePath();

    FILE* followersFilePointer = fopen(followersFilePath.c_str(), "r");

    char nome[100];
    while(fscanf(followersFilePointer, "%[^\n]%*c", nome) != EOF){
        std::string username = nome;
        followers.push_back(new Usuario(username));
    }

    fclose(followersFilePointer);   

    //ordenando em ordem alfabetica
    sort(followers.begin(), followers.end(), [](Usuario* a, Usuario* b){ return a->getNome() < b->getNome(); });
    return followers;
}

/**
 * @brief retorna um booleano se o usuario segue o usuario de nome "user"
 * @param user nome do usuario que é seguido
 * @return bool
*/
bool Usuario::isFollowing(std::string user){

    for(auto u : this->getFollowing()){
        if(u->getNome() == user){
            return true;
        }
    }

    return false;
}


//Função de aparar um usuario e também remover seus dados do login_data.txt
void Usuario::apagarUsuario(std::string user){
    // std::string userFolderPath = "usuarios/cadastrados/";
    // userFolderPath += user;
    // userFolderPath += "/";

    // std::string rmCommand = "rm -r ";
    // rmCommand += userFolderPath;
    // system(rmCommand.c_str());

    // // FILE* ptr = fopen(LOGIN_DATA_FILE_PATH, "r");
    // FILE* ptr2 = fopen("temp.txt", "w");

    // char name[100], senha[100];
    // while(fscanf(ptr, "%[^,],%[^\n]%*c", name, senha) != EOF){
    //     std::string atual = name;
    //     if(atual == user){
    //         continue;
    //     }
    //     fprintf(ptr2, "%s,%s\n", name, senha);
    // }

    // fclose(ptr);
    // fclose(ptr2);

    // rmCommand = "rm ";
    // // rmCommand += LOGIN_DATA_FILE_PATH;
    // system(rmCommand.c_str());

    // rmCommand = "mv temp.txt ";
    // // rmCommand += LOGIN_DATA_FILE_PATH;
    // system(rmCommand.c_str());
}

std::string Usuario::getSelfPostsFilePath(){
    std::string selfPostsFilePath = this->getUserFolderPath();
    selfPostsFilePath += "posts.txt";
    return selfPostsFilePath;
}