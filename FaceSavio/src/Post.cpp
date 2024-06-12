#include "../include/Post.hpp"
#include <iostream>


void Post::newPost(int id, std::string texto, std::string username){
    if(id > Post::getTotalPosts()){ //cria um novo post na memoria
        //string com o caminho para o local que sera armazenado o novo post
        std::string newPostFilePath = Post::getPostsFolderPath();
        newPostFilePath += "post";
        newPostFilePath += std::to_string(id);
        newPostFilePath += ".txt";

        //escrevendo o novo post
        FILE* newPostFilePointer = fopen(newPostFilePath.c_str(), "w");
        fprintf(newPostFilePointer, "%s\n", username.c_str());
        fprintf(newPostFilePointer, "%d\n", id);
        fprintf(newPostFilePointer, "%s", texto.c_str());
        fclose(newPostFilePointer);


        Post::setTotalPosts(Post::getTotalPosts() + 1);
    }
}

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


std::string Post::getPostsFolderPath(){  
    std::string postsFolderPath = "usuarios/posts/";
    return postsFolderPath;
}

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

bool Post::isValid(int id){
    FILE* ptr = fopen(getPostFilePath(id).c_str(), "r");

    if(ptr == NULL){
        return false;
    }

    fclose(ptr);
    return true;
}