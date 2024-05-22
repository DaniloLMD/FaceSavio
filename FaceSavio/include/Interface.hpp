#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <vector>

#include <gtk/gtk.h>

#include "homeSignals.hpp"
#include "Post.hpp"
#include "Usuario.hpp"

typedef struct InterfaceStruct InterfaceStruct;

class Interface{
    public: 
        Interface(const char* gladeFile);

        void activateCSS (const char* cssFile);
    
        void display();
        void reset();

        // std::vector<Post> posts;

        GtkBuilder* getBuilder() { return builder; }
        GtkWidget* getMainWindow() { return mainWindow; }
        Usuario* getUsuario() { return usuario; }
    
        std::vector<GtkWidget*> grids;
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