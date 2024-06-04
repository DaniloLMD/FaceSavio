#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

#include "../include/Usuario.hpp"
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/Post.hpp"

/**
 * @brief construtor da classe Usuario
 * @param nome nome do usuario
 * @return ponteiro para Usuario
*/
Usuario::Usuario(std::string nome) : nome(nome) {
    // gerenciadorNotificacoes = new GerenciadorNotificacoes(this);

    mkDir(nome);
}

void Usuario::mkDir(std::string nome){
    if(Usuario::isValid(nome)) return;

    //criando a pasta com o nome do usuario
    std::string mkdirCommand = "mkdir ";
    mkdirCommand += this->getUserFolderPath();
    system(mkdirCommand.c_str());

    //criando a pasta com os posts do usuario
    mkdirCommand = "mkdir ";
    mkdirCommand += this->getPostsFolderPath();
    system(mkdirCommand.c_str());

    
    //criando o arquivo "foto.png"
    std::string cpCommand = "cp usuarios/fotoPadrao.png ";
    cpCommand += this->getFotoFilePath();
    system(cpCommand.c_str());


    FILE* ptr = NULL;
    //criando o arquivo "followers.txt"
    ptr = fopen(this->getFollowersFilePath().c_str(), "w");
    fclose(ptr);

    //criando o arquivo "following.txt"
    ptr = fopen(this->getFollowingFilePath().c_str(), "w");
    fclose(ptr);

    //criando o arquivo "quantidadePosts.txt"
    ptr = fopen(this->getQuantidadePostsFilePath().c_str(), "w");
    fprintf(ptr, "0\n");
    fclose(ptr);

    //criando a pasta feed
    mkdirCommand = "mkdir ";

    //criando o arquivo quantidadeFeed.txt
}

bool Usuario::isValid(std::string name){
    std::string path = "usuarios/";
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
    // gerenciadorNotificacoes->notificarTodos(msg);

    std::string newPostFilePath = this->getPostsFolderPath();
    newPostFilePath += "post";
    newPostFilePath += std::to_string(this->getQuantidadePosts() + 1);
    newPostFilePath += ".txt";

    FILE* newPostFilePointer = fopen(newPostFilePath.c_str(), "w");
    fprintf(newPostFilePointer, "%d\n", this->getTotalPosts() + 1);
    fprintf(newPostFilePointer, "%s", msg.c_str());
    fclose(newPostFilePointer);

    this->setQuantidadePosts(this->getQuantidadePosts() + 1);
    this->setTotalPosts(this->getTotalPosts() + 1);
}

/**
 * @brief adiciona um usuario na lista de seguidores de outro.
 * @param usuario usuario que está sendo seguido
 * @return void
*/
void Usuario::seguir(std::string username) {
    if(this->nome == username) return;

    Usuario* usuario = new Usuario(username);
    
    std::string followersFilePath = usuario->getFollowersFilePath();
    std::string followingFilePath = this->getFollowingFilePath();

    FILE* followersFilePointer = fopen(followersFilePath.c_str(), "r");

    bool adicionar = true;
    
    char name[50];
    while(fscanf(followersFilePointer, "%[^\n]%*c", name) != EOF){
        if(!strcmp(name, this->getNome().c_str())){
            adicionar = false;
            break;
        }
    }
    fclose(followersFilePointer);
    
    if(adicionar){
        followersFilePointer = fopen(followersFilePath.c_str(), "a");
        fprintf(followersFilePointer, "%s\n", nome.c_str());
        fclose(followersFilePointer);

        FILE* followingFilePointer = fopen(followingFilePath.c_str(), "a");
        fprintf(followersFilePointer, "%s\n", username.c_str());
        fclose(followersFilePointer);
    }
}

void Usuario::desseguir(std::string usuario){

    auto following = this->getFollowing();

    FILE* followingFilePointer = fopen(this->getFollowingFilePath().c_str(), "w");
    for(auto u: following){
        if(u->getNome() == usuario) continue;
        fprintf(followingFilePointer, "%s\n", u->getNome().c_str());
    }
    fclose(followingFilePointer);

    Usuario* user2 = new Usuario(usuario);
    FILE* followersFilePointer = fopen(user2->getFollowersFilePath().c_str(), "w");
    auto followers = user2->getFollowers();
    for(auto u: followers){
        if(u->getNome() == this->getNome()) continue;
        fprintf(followersFilePointer, "%s\n", u->getNome().c_str());
    }
    fclose(followersFilePointer);

    
}

/**
 * @brief o usuario atual recebe uma notificação de que o usuario autor publicou um post.
 * @param msg mensagem do post do autor
 * @param autor usuario que publicou o post
 * @return void
*/
void Usuario::notificar(std::string msg, std::string autor) {
    std::cout << "Sou o usuario " << nome << " e o usuario " << autor << " publicou a mensagem: '" << msg << "'.\n";
}

/**
 * @brief retorna a quantidade total de posts
 * @return int
*/
int Usuario::getTotalPosts(){
    int quantidade;

    std::string totalPostsFilePath = this->getTotalPostsFilePath();
    FILE* totalPostsFilePointer = fopen(totalPostsFilePath.c_str(), "r");

    fscanf(totalPostsFilePointer, "%d", &quantidade);

    fclose(totalPostsFilePointer);

    return quantidade;
}

/**
 * @brief seta a quantidade total de posts para um novo valor
 * @param quantidade valor a ser setado
 * @return void
*/
void Usuario::setTotalPosts(int quantidade){
    std::string totalPostsFilePath = this->getTotalPostsFilePath();

    FILE* totalPostsFilePointer = fopen(totalPostsFilePath.c_str(), "w");
    fprintf(totalPostsFilePointer, "%d\n", quantidade);

    fclose(totalPostsFilePointer);
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
    std::string userFolderPath = "usuarios/";
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
 * @brief retorna uma string com o caminho para a pasta de posts do usuario
 * @return string
*/
std::string Usuario::getPostsFolderPath(){  
    std::string postsFolderPath = this->getUserFolderPath();
    postsFolderPath += "posts/";
    return postsFolderPath;
}

/**
 * @brief retorna o caminho para um post de numero X (nao é o id, é o numero do post na pasta do usuario)
 * @param post numero do post
 * @return string
*/
std::string Usuario::getPostFilePath(int post){

    if(post > this->getQuantidadePosts() || post < 0){
        std::cout << "numero de post invalido!\n";
        return "";
    }

    std::string postFilePath = this->getPostsFolderPath();
    postFilePath += "post";
    postFilePath += std::to_string(post);
    postFilePath += ".txt";
    return postFilePath;
}

/**
 * @brief retorna uma string com o caminho para o arquivo que contem o total de posts
 * @return string
*/
std::string Usuario::getTotalPostsFilePath(){
    std::string totalPostsFilePath = "usuarios/totalPosts.txt";
    return totalPostsFilePath;
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
/**
 * @brief retorna uma string com o caminho para a pasta de feed do usuario
 * @return string
*/
std::string Usuario::getFeedFolderPath(){
    std::string feedFolderPath = this->getUserFolderPath();
    feedFolderPath += "feed/";
    return feedFolderPath;
}

/**
 * @brief retorna uma string com o caminho para a pasta de feed do usuario
 * @param post identificador do post a ser buscado (de 1 ate o numero em quantidadeFeed)
 * @return string
*/
std::string Usuario::getFeedFilePath(int post){
    std::string feedFilePath = this->getFeedFolderPath();
    feedFilePath += "post" + std::to_string(post) + "txt";
    return feedFilePath;
}


bool comp(Post* p1, Post* p2){
    return p1->getID() > p2->getID();
}

std::vector<Post*> Usuario::loadAllPosts(){
    posts = loadSelfPosts();

    auto following = this->getFollowing();

    for(auto u: following){
        std::string username = u->getNome();
        Usuario* user = new Usuario(username);


        for(int i = 1; i <= user->getQuantidadePosts(); i++){
            std::string postFilePath = user->getPostFilePath(i);
            FILE* postFilePointer = fopen(postFilePath.c_str(), "r");
            int id;
            std::string texto;

            
            char c;
            fscanf(postFilePointer, "%d%*c", &id);
            while(fscanf(postFilePointer, "%c", &c) != EOF){
                texto += c;
            }

            Post* newPost = new Post(id, texto, user->getNome());
            posts.push_back(newPost);
            fclose(postFilePointer);
        }
    }

    sort(posts.begin(), posts.end(), comp);

    return posts;
}

std::vector<Post*> Usuario::loadSelfPosts(){
    posts.clear();

    for(int i = 1; i <= this->getQuantidadePosts(); i++){
        std::string postFilePath = this->getPostFilePath(i);
            
        FILE* postFilePointer = fopen(postFilePath.c_str(), "r");
        int id;
        std::string texto = "";


        fscanf(postFilePointer, "%d%*c", &id);
        char x;
        while(fscanf(postFilePointer, "%c", &x) != EOF){
            texto += x;
        }

        Post* newPost = new Post(id, texto, this->getNome());
        posts.push_back(newPost);
        fclose(postFilePointer);
    }

    sort(posts.begin(), posts.end(), comp);
    return posts;
}

bool userComp(Usuario* a, Usuario* b){
    return a->getNome() < b->getNome();   
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

    sort(following.begin(), following.end(), userComp);
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

    sort(followers.begin(), followers.end(), userComp);
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
