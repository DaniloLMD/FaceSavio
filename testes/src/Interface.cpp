#include "../include/Interface.hpp"
#include <iostream>

// Construtor
Interface::Interface(const char* gladeFile) : gladeFile(gladeFile){
    gtk_init(NULL, NULL);
    
    builder = gtk_builder_new_from_file(gladeFile);
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
}

/**
 * @brief ativa o CSS na interface
 * @param cssFile caminho do arquivo css
*/
void Interface::activateCSS (const char* cssFile) {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, cssFile, 0);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

/**
 * @brief prepara a interface para ser exibida na tela
*/
void Interface::display(){
    connectSymbols();
    gtk_widget_show(mainWindow);
    gtk_main();
}

/**
 * @brief conecta os signals da interface
*/
void Interface::connectSymbols(){

    gtk_builder_add_callback_symbols(
        builder,
        "on_main_window_destroy",           G_CALLBACK(gtk_main_quit),

        //signals da pagina home
        "on_textBufferPost_insert_text",    G_CALLBACK(on_textBufferPost_insert_text),
        "on_homeButton_clicked",            G_CALLBACK(on_homeButton_clicked),
        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

    Interface* selfPointer = this;
    InterfaceStruct data;  
    data.pointer = &selfPointer;

    g_signal_connect(gtk_builder_get_object(builder, "buttonPost"), "clicked", G_CALLBACK(on_buttonPost_clicked), &data);
}

void Interface::reset(){
    gtk_main_quit();
    gtk_widget_show_all(mainWindow);
    gtk_main();
}