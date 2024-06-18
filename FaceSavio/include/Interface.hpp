#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <gtk/gtk.h>
#include <vector>

#include "Post.hpp"
#include "Usuario.hpp"

#include <iostream>

class Interface{
    public: 
        Interface();

        ~Interface(){
            delete usuario;
        }

        void activateCSS (const char* cssFile);
    
        void display();
        void reset();

        void popup(std::string title, std::string text);

        GtkBuilder* getBuilder() const { return this->builder; }
        GtkWidget* getMainWindow() const { return mainWindow; }
        Usuario* getUsuario() const { return usuario; }
        void setUsuario(Usuario* user) { 
            delete this->usuario;
            this->usuario = user; 
        }
    
        std::vector<GtkWidget*> gridsPost;
        std::vector<GtkWidget*> gridsFollowing;

        static constexpr char GLADE_FILE_PATH[] = "glade/faceSavio.glade";
        static constexpr char CSS_FILE_PATH[] = "glade/faceSavio.css";
        static constexpr char LOGIN_DATA_FILE_PATH[] = "usuarios/login_data.txt";
        

    private:
        void connectSymbols();


        GtkBuilder* builder;
        GtkWidget* mainWindow;

        Usuario* usuario;

        GtkWidget* newScaledImage(const gchar *filePath, gint width, gint height);
        void setScaledImage(GtkImage* image, const gchar *filePath, gint width, gint height);

        /////// Login Signals ///////////////////////////////////////
        bool lembrar = false;        
        bool login(std::string userName, std::string password);
        bool cadastrar(std::string userName, std::string password);
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

        void showPosts(std::vector<Post> posts);
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
        void on_deleteUserButton_clicked();
        
        //popup
        void on_popUpOkButton_clicked(); 
        void showFileChooserDialog();
        void on_fileChooserDialog_file_activated(GtkWidget* fileChooserPopup);
};

#endif