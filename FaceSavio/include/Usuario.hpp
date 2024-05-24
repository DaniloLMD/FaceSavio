#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <vector>

#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/INotificavel.hpp"
#include "Post.hpp"

class Usuario : public INotificavel {
    public:
        Usuario(std::string nome);

        static void mkDir(std::string name);
        static bool isValid(std::string name);

        std::string getNome();

        void publicar(std::string msg);

        void seguir(std::string usuario);

        void notificar(std::string msg, std::string autor) override;

        std::vector<Post*> loadAllPosts();
        std::vector<Post*> loadSelfPosts();
        std::vector<Usuario*> getFollowing();

        std::string getFotoFilePath();

    private:
        std::string nome;
        GerenciadorNotificacoes* gerenciadorNotificacoes;

        //funcoes de acesso aos arquivos
        int getTotalPosts();
        void setTotalPosts(int quantidade);
        int getQuantidadePosts();
        void setQuantidadePosts(int quantidade);  

        std::vector<Post*> posts;
        std::vector<Usuario*> following;

        std::string getUserFolderPath();
        std::string getTotalPostsFilePath();
        std::string getFollowersFilePath();
        std::string getFollowingFilePath();
        std::string getPostsFolderPath();   
        std::string getPostFilePath(int post); 
        std::string getQuantidadePostsFilePath();
};


#endif