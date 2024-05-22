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

GtkWidget* newScaledImage(const gchar *filePath, gint width, gint height);
void setScaledImage(GtkImage* image, const gchar *filePath, gint width, gint height);

#endif