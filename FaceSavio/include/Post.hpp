#ifndef __POST_HPP__
#define __POST_HPP__

#include <gtk/gtk.h>
#include <string>

class Post{
    public:

        Post(int id);

        int getID() { return id; }
        std::string getTexto() { return texto; }
        std::string getUsername() { return username; }

        static void newPost(int id, std::string texto, std::string autor);
        static int getTotalPosts();
        static void setTotalPosts(int quantidade);
        static std::string getTotalPostsFilePath();
        static std::string getPostsFolderPath();
        static std::string getPostFilePath(int id);

        static bool isValid(int id);

    private:
        int id;
        std::string texto;
        std::string username;
};

#endif