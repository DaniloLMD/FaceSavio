#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <vector>

#include <gtk/gtk.h>

#include "homeSignals.hpp"
#include "Post.hpp"

typedef struct InterfaceStruct InterfaceStruct;

class Interface{
    public: 
        // static Interface* self;

        Interface(const char* gladeFile);

        void activateCSS (const char* cssFile);
    
        void display();
        void reset();

        //Atributos relacionados aos posts
        std::vector<Post> posts;
        std::vector<GtkWidget*> grids;

        //Getters   
        GtkBuilder* getBuilder() { return builder; }
        GtkWidget* getMainWindow() { return mainWindow; }
    
    private:
        //Metodos
        void connectSymbols();

        //Atributos
        const char* gladeFile; //nome do arquivo glade do builder

        GtkBuilder* builder;
        GtkWidget* mainWindow;
};

struct InterfaceStruct{
    Interface** pointer;
};

Interface* interface = NULL;

#endif