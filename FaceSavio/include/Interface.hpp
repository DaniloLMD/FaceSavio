#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <vector>

#include <gtk/gtk.h>

#include "loginSignals.hpp"
#include "homeSignals.hpp"
#include "Post.hpp"
#include "Usuario.hpp"
#include "paths.hpp"

typedef struct InterfaceStruct InterfaceStruct;

class Interface{
    public: 
        Interface(const char* gladeFile);

        void activateCSS (const char* cssFile);
    
        void display();
        void reset();

        void popup(std::string title, std::string text);

        GtkBuilder* getBuilder() { return builder; }
        GtkWidget* getMainWindow() { return mainWindow; }
        Usuario* getUsuario() { return usuario; }
        void setUsuario(Usuario* user) { this->usuario = user; }
    
        std::vector<GtkWidget*> gridsPost;
        std::vector<GtkWidget*> gridsFollowing;

    private:
        void connectSymbols();

        const char* gladeFile; //nome do arquivo glade do builder

        GtkBuilder* builder;
        GtkWidget* mainWindow;

        Usuario* usuario;
         
};

struct InterfaceStruct{
    Interface** pointer;
};

// Interface* interface = NULL;

#endif