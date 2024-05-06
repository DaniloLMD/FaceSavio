#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <gtk/gtk.h>

#include "homeSignals.hpp"

class Interface{
    public: 
        Interface(const char* gladeFile);

        void activateCSS (const char* cssFile);
    
        void display();

        //Getters   
        GtkBuilder* getBuilder() { return builder; }
        GtkWidget* getMainWindow() { return mainWindow; }

        //Setters
    
    private:
        //Metodos
        void connectSymbols();

        //Atributos
        const char* gladeFile;

        GtkBuilder* builder;
        GtkWidget* mainWindow;

        //Atributos da pagina home
        GtkTextView* textView;
};


#endif