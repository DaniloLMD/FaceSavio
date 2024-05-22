#ifndef __POST_HPP__
#define __POST_HPP__

#include <gtk/gtk.h>
#include <string>

class Post{
    public:

        Post(int id, std::string texto, std::string username);

        int getID() { return id; }
        std::string getTexto() { return texto; }
        std::string getUsername() { return username; }

    private:
        int id;
        std::string texto;
        std::string username;
};

// struct Post{
//     GtkWidget* profile; //foto de perfil
//     GtkWidget*  name; //nome do usuario
//     GtkWidget* text; //texto do post
// };

GtkWidget* scaledImage(const gchar *filePath, gint width, gint height);

#endif