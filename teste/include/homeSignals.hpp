#ifndef __HOME_SIGNALS_HPP__
#define __HOME_SIGNALS_HPP__

#include "Interface.hpp"
#include "Post.hpp"

void connectHomeSignals(void* newInterface);

void loadHomeScreen();

void on_textBufferPost_changed(GtkTextBuffer* buffer);

void on_buttonPost_clicked(void* interfaceStruct);

void on_homeButton_clicked();
void on_logoutButton_clicked();

void showPosts(std::vector<Post*> posts);
void showFollowing();
void showProfileImageHomeButton();

void limparGridPosts();
void limparGridFollowing();

void on_searchBar_activate();

void on_profileImageHomeButton_clicked();
void on_profileButton_clicked();

void on_searchBar_search_changed();

//profile
void on_followButton_clicked();


//popup
void on_popUpOkButton_clicked(); 
void showFileChooserDialog();
void on_fileChooserDialog_file_activated(GtkWidget* fileChooserPopup);

#endif