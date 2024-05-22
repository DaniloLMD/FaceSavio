#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <vector>

#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/INotificavel.hpp"
#include "Post.hpp"

class Usuario : public INotificavel {
    public:
        Usuario(std::string nome);

        std::string getNome();

        void publicar(std::string msg);

        void seguir(std::string usuario);

        void notificar(std::string msg, std::string autor) override;

        void showPosts();


    private:
        std::string nome;
        GerenciadorNotificacoes* gerenciadorNotificacoes;

        //funcoes de acesso aos arquivos
        int getTotalPosts();
        void setTotalPosts(int quantidade);
        int getQuantidadePosts();
        void setQuantidadePosts(int quantidade);  

        void loadPosts();
        std::vector<Post*> posts;

        std::string getUserFolderPath();
        std::string getTotalPostsFilePath();
        std::string getFollowersFilePath();
        std::string getFollowingFilePath();
        std::string getPostsFolderPath();   
        std::string getPostFilePath(int post); 
        std::string getQuantidadePostsFilePath();
};


#endif