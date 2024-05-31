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
    activateCSS(CSS_FILE_PATH);
    connectSymbols();
    loadLoginScreen();
    gtk_widget_show(mainWindow);
    gtk_main();
}

void Interface::connectSymbols(){   

    g_signal_connect(this->getMainWindow(), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /////////// Signals da pagina login /////////////////////////////////////////////////////////////////////////////
    g_signal_connect_data(gtk_builder_get_object(builder, "login"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_login_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "cadastrar"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_cadastrar_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "remember"), "toggled",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_remember_toggled();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "password"), "activate",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_password_activate();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "name"), "activate",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_name_activate();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "name"), "changed",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_name_changed();
        }), this, NULL, G_CONNECT_AFTER
    );

    /////////// Signals da pagina home /////////////////////////////////////////////////////////////////////////////
    //popup
    g_signal_connect_data(gtk_builder_get_object(builder, "popUpOkButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_popUpOkButton_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );
    
    g_signal_connect_data(gtk_builder_get_object(builder, "textBufferPost"), "changed",
        G_CALLBACK(+[](GtkTextBuffer *buffer, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_textBufferPost_changed(buffer);
        }), this, NULL, G_CONNECT_AFTER
    );
    
    g_signal_connect_data(gtk_builder_get_object(builder, "homeButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_homeButton_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "logoutButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_logoutButton_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "searchBar"), "activate",
        G_CALLBACK(+[](GtkSearchEntry* searchBar, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_searchBar_activate(searchBar);
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "searchBar"), "search_changed",
        G_CALLBACK(+[](GtkSearchEntry* searchBar, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_searchBar_search_changed(searchBar);
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "profileImageHomeButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_profileImageHomeButton_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );


    g_signal_connect_data(gtk_builder_get_object(builder, "profileButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_profileButton_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );

    g_signal_connect_data(gtk_builder_get_object(builder, "buttonPost"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_buttonPost_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );

    /////////// Signals da pagina profile /////////////////////////////////////////////////////////////////////////////
    g_signal_connect_data(gtk_builder_get_object(builder, "followButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
            Interface* self = (Interface*) user_data;
            self->on_followButton_clicked();
        }), this, NULL, G_CONNECT_AFTER
    );
}

void Interface::reset(){
    gtk_widget_show_all(mainWindow);
}

void Interface::popup(std::string title, std::string text){
    GtkMessageDialog *popup = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "popup"));
    g_object_set(popup, "text", title.c_str(), NULL);
    g_object_set(popup, "secondary_text", text.c_str(), NULL);
    
    gtk_widget_show_all(GTK_WIDGET(popup));
    gtk_dialog_run(GTK_DIALOG(popup));
}

GtkBuilder* Interface::getBuilder(){
    return builder;
}