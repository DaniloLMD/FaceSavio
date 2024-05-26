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

        GtkBuilder* getBuilder() { return builder; }
        GtkWidget* getMainWindow() { return mainWindow; }
        Usuario* getUsuario() { return usuario; }
    
        std::vector<GtkWidget*> gridsPost;
        std::vector<GtkWidget*> gridsFollowing;

        //TESTE (APAGAR DEPOIS)
        void setUsuario(Usuario* u){ usuario = u; }

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