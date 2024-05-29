#include "../include/Interface.hpp"
#include <iostream>

// Construtor
Interface::Interface(const char* gladeFile) : gladeFile(gladeFile){
    gtk_init(NULL, NULL);
    
    builder = gtk_builder_new_from_file(gladeFile);
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    usuario = new Usuario("Danilo"); //testando
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
    activateCSS(CSS_FILE_PATH);
    connectSymbols();
    loadLoginScreen();
    gtk_widget_show(mainWindow);
    gtk_main();
}

void Interface::connectSymbols(){   

    gtk_builder_add_callback_symbols(
        builder,
        "on_main_window_destroy",           G_CALLBACK(gtk_main_quit),

        //signals de popup
        "on_popUpOkButton_clicked",                 G_CALLBACK(on_popUpOkButton_clicked),

        //signals da pagina de login
        "on_login_clicked",                 G_CALLBACK(on_login_clicked),
        "on_cadastrar_clicked",             G_CALLBACK(on_cadastrar_clicked),
        "on_remember_toggled",              G_CALLBACK(on_remember_toggled),
        "on_password_activate",             G_CALLBACK(on_password_activate),
        "on_name_activate",                 G_CALLBACK(on_name_activate),
        "on_name_changed",                  G_CALLBACK(on_name_changed),


        //signals da pagina home
        "on_textBufferPost_changed",                    G_CALLBACK(on_textBufferPost_changed),
        "on_homeButton_clicked",                        G_CALLBACK(on_homeButton_clicked),
        "on_logoutButton_clicked",                      G_CALLBACK(on_logoutButton_clicked),
        "on_searchBar_activate",                        G_CALLBACK(on_searchBar_activate),
        "on_profileImageHomeButton_clicked",            G_CALLBACK(on_profileImageHomeButton_clicked),
        "on_profileButton_clicked",                     G_CALLBACK(on_profileButton_clicked),
        "on_searchBar_search_changed",                  G_CALLBACK(on_searchBar_search_changed),

        //signals da pagina de interface
        "on_followButton_clicked",                      G_CALLBACK(on_followButton_clicked),

        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

    g_signal_connect(gtk_builder_get_object(builder, "buttonPost"), "clicked", G_CALLBACK(on_buttonPost_clicked), NULL);

    connectLoginSignals(this);
}

void Interface::reset(){
    // gtk_main_quit();
    gtk_widget_show_all(mainWindow);
    // gtk_main();
}

void Interface::popup(std::string title, std::string text){
    GtkMessageDialog *popup = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "popup"));
    g_object_set(popup, "text", title.c_str(), NULL);
    g_object_set(popup, "secondary_text", text.c_str(), NULL);
    
    gtk_widget_show_all(GTK_WIDGET(popup));
    gtk_dialog_run(GTK_DIALOG(popup));
}