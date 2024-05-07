#ifndef __POST_HPP__
#define __POST_HPP__

#include <gtk/gtk.h>

struct Post{
    GtkWidget* profile; //foto de perfil
    GtkWidget*  name; //nome do usuario
    GtkWidget* text; //texto do post
};

GtkWidget* scaledImage(const gchar *filePath, gint width, gint height);

#endif