#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <vector>

#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/INotificavel.hpp"
#include "Post.hpp"

class Usuario : public INotificavel {
    public:
        Usuario(std::string nome);

        void mkDir(std::string name);
        static bool isValid(std::string name);

        std::string getNome();

        void publicar(std::string msg);

        void seguir(std::string usuario);
        void desseguir(std::string usuario);
        
        void apagarUsuario(std::string user);

        void notificar(int postId) override;

        bool isFollowing(std::string user);

        void loadGerenciadorNotificacoes();

        std::vector<Post*> loadFeed();
        std::vector<Post*> loadSelfPosts();
        std::vector<Usuario*> getFollowing();
        std::vector<Usuario*> getFollowers();

        std::string getFotoFilePath();

    private:
        std::string nome;
        GerenciadorNotificacoes* gerenciadorNotificacoes;

        //funcoes de acesso aos arquivos
        int getQuantidadePosts();
        void setQuantidadePosts(int quantidade);  

        void addPostToFeed(int id);

        std::vector<Post*> posts;

        std::string getUserFolderPath();
        std::string getFollowersFilePath();
        std::string getFollowingFilePath();
        // std::string getSelfPostsFolderPath();   
        std::string getSelfPostsFilePath();   
        std::string getQuantidadePostsFilePath();
        std::string getQuantidadeFeedFilePath();
        int getQuantidadeFeed();
        void setQuantidadeFeed(int v);
        // std::string getFeedFolderPath();
        std::string getFeedFilePath();
};


#endif