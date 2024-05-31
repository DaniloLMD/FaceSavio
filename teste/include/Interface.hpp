#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <gtk/gtk.h>
#include <vector>

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

        GtkBuilder* getBuilder();
        GtkWidget* getMainWindow() { return mainWindow; }
        Usuario* getUsuario() { return usuario; }
        void setUsuario(Usuario* user) { this->usuario = user; }
    
        std::vector<GtkWidget*> gridsPost;
        std::vector<GtkWidget*> gridsFollowing;

    private:
        void connectSymbols();

        const char* gladeFile;

        GtkBuilder* builder;
        GtkWidget* mainWindow;

        Usuario* usuario;

        /////// Login Signals ///////////////////////////////////////
        void loadLoginScreen();
        void on_login_clicked();
        void on_cadastrar_clicked();

        void on_remember_toggled();

        void on_name_changed();
        void on_name_activate();
        void on_password_activate();

        std::string getPassword();
        std::string getName();

        /////// Home Signals ///////////////////////////////////////
        void loadHomeScreen();
        void loadProfileScreen(std::string);

        void on_name_clicked(GtkWidget *widget);

        void on_textBufferPost_changed(GtkTextBuffer* buffer);

        void on_buttonPost_clicked();

        void on_homeButton_clicked();
        void on_logoutButton_clicked();

        void showPosts(std::vector<Post*> posts);
        void showFollowing();
        void showProfileImageHomeButton();

        void limparGridPosts();
        void limparGridFollowing();

        void on_searchBar_activate(GtkSearchEntry* searchBar);
        void on_searchBar_search_changed(GtkSearchEntry* searchBar);

        void on_profileImageHomeButton_clicked();
        void on_profileButton_clicked();


        //profile
        void on_followButton_clicked();

        //popup
        void on_popUpOkButton_clicked(); 
        void showFileChooserDialog();
        void on_fileChooserDialog_file_activated(GtkWidget* fileChooserPopup);
};

#endif