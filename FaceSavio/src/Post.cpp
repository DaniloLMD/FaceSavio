#include "../include/Post.hpp"
#include <iostream>

//construtor

Post::Post(int id) : id(id) {

    if(id > Post::getTotalPosts() || id < 0){
        std::cout << "ID invalido, post inexistente!\n";
        exit(EXIT_FAILURE);
    }

    std::string postFilePath = this->getPostFilePath(id);
    FILE* postFilePointer = fopen(postFilePath.c_str(), "r");
    
    char c;
    char username[100];
    fscanf(postFilePointer, "%[^\n]%*c", username);
    fscanf(postFilePointer, "%d%*c", &id);

    std::string texto = "";
    while(fscanf(postFilePointer, "%c", &c) != EOF){
        texto += c;
    }

    fclose(postFilePointer);

    this->texto = texto;
    this->username = username;
}

/**
 * @brief cria um novo post e o salva em um txt
 * @param id id do novo post
 * @param texto texto do novo post
 * @param autor autor do novo post
*/
void Post::newPost(int id, std::string texto, std::string autor){
    if(id > Post::getTotalPosts()){ //cria um novo post na memoria
        //string com o caminho para o local que sera armazenado o novo post
        std::string newPostFilePath = Post::getPostsFolderPath();
        newPostFilePath += "post";
        newPostFilePath += std::to_string(id);
        newPostFilePath += ".txt";

        //escrevendo o novo post
        FILE* newPostFilePointer = fopen(newPostFilePath.c_str(), "w");
        fprintf(newPostFilePointer, "%s\n", autor.c_str());
        fprintf(newPostFilePointer, "%d\n", id);
        fprintf(newPostFilePointer, "%s", texto.c_str());
        fclose(newPostFilePointer);


        Post::setTotalPosts(Post::getTotalPosts() + 1);
    }
}

/**
 * @brief retorna a quantidade total de posts
 * @return int
*/
int Post::getTotalPosts(){
    int quantidade;

    std::string totalPostsFilePath = getTotalPostsFilePath();
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
void Post::setTotalPosts(int quantidade){
    std::string totalPostsFilePath = getTotalPostsFilePath();

    FILE* totalPostsFilePointer = fopen(totalPostsFilePath.c_str(), "w");
    fprintf(totalPostsFilePointer, "%d\n", quantidade);

    fclose(totalPostsFilePointer);
}

/**
 * @brief retorna uma string com o caminho para a pasta de posts
 * @return string com o caminho
*/
std::string Post::getPostsFolderPath(){  
    std::string postsFolderPath = "usuarios/posts/";
    return postsFolderPath;
}

/**
 * @brief retorna uma string com o caminho para um post de determinado ID
 * @param id id do post
 * @return string com o caminho para o post
*/
std::string Post::getPostFilePath(int id){

    if(id > getTotalPosts() || id < 0){
        std::cout << "ID invalido.\n";
        return "";
    }

    std::string postFilePath = getPostsFolderPath();
    postFilePath += "post";
    postFilePath += std::to_string(id);
    postFilePath += ".txt";
    return postFilePath;
}

/**
 * @brief retorna uma string com o caminho para o arquivo que contem o total de posts
 * @return string
*/
std::string Post::getTotalPostsFilePath(){
    std::string totalPostsFilePath = "usuarios/totalPosts.txt";
    return totalPostsFilePath;
}

/**
 * @brief verifica se o post de determinado ID realmente existe
 * @param id id do post a ser checado
 * @return true se for valido, false caso contrario
*/
bool Post::isValid(int id){
    FILE* ptr = fopen(getPostFilePath(id).c_str(), "r");

    if(ptr == NULL){
        return false;
    }

    fclose(ptr);
    return true;
}