#include <iostream>

#include "../include/homeSignals.hpp"
#include <gtk/gtk.h>
#include "../include/Usuario.hpp"

Interface* interface = NULL;

void connectHomeSignals(void* newInterface){
    interface = (Interface*) newInterface;
}

void loadHomeScreen(){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack2"));
    gtk_stack_set_visible_child_name(stack, "home");   
    GtkWidget* profileImage = newScaledImage(interface->getUsuario()->getFotoFilePath().c_str(), 80, 80);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "profileImageHomeButton"));
    GtkLabel* homeUsernameLabel = GTK_LABEL(gtk_builder_get_object(interface->getBuilder(), "homeUsernameLabel"));

    gtk_label_set_text(homeUsernameLabel, interface->getUsuario()->getNome().c_str());
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);
    
    gtk_widget_set_name(GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "searchBar")), "entryNormal");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(interface->getBuilder(), "searchBar")), "Find user");

    showPosts(interface->getUsuario()->loadAllPosts());
    showFollowing();
}

void loadProfileScreen(std::string username){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack2"));


    GtkButton* followButton = GTK_BUTTON(gtk_builder_get_object(interface->getBuilder(), "followButton"));
    if(username == interface->getUsuario()->getNome()){
        gtk_button_set_label(followButton, "Edit");
    }
    else{
        if(interface->getUsuario()->isFollowing(username)){
            gtk_button_set_label(followButton, "Unfollow");
        }
        else{
            gtk_button_set_label(followButton, "Follow");
        }
    }

    gtk_stack_set_visible_child_name(stack, "profile");   

    Usuario* user = new Usuario(username);
    GtkWidget* profileImage = newScaledImage(user->getFotoFilePath().c_str(), 120, 120);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "profileImageButton"));
    GtkLabel* profileUserNameLabel = GTK_LABEL(gtk_builder_get_object(interface->getBuilder(), "profileUserNameLabel"));

    gtk_label_set_text(profileUserNameLabel, user->getNome().c_str());
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);

    showPosts(user->loadSelfPosts());

    interface->reset();
}

/**
 * @brief verifica se o limite de caracteres e de linhas foi atingido. Caso tenha sido, bloqueia a entrada de novos caracteres
*/
void on_textBufferPost_insert_text(GtkTextBuffer *buffer) {
    
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    // Obtém o texto do buffer de texto
    std::string text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    const int MAX_COLUMNS = 100;
    const int MAX_LINES = 10;

    int caracteres = 0;
    int linhas = 0;

    for(char c: text){
        if(c == '\n'){
            caracteres = 0;
            linhas++;
        }
        else{
            caracteres++;
        }
        if(caracteres > MAX_COLUMNS || linhas > MAX_LINES){
            g_signal_stop_emission_by_name(buffer, "insert-text");
        }
    }
}

/**
 * @brief adiciona um post quando o botão é apertado.
*/  
void on_buttonPost_clicked(void* data){

    GtkBuilder* builder = interface->getBuilder();
    GtkTextBuffer* buffer =  GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBufferPost"));

    //buffers para pegar o texto do text view
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    const char* postText = gtk_text_buffer_get_text(buffer, &start, &end, FALSE); 

    interface->getUsuario()->publicar(postText);

    showPosts(interface->getUsuario()->loadAllPosts());
}

void limparGridPosts(){
    GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "gridPosts"));

    while(interface->gridsPost.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridPosts), 1);
        interface->gridsPost.erase(interface->gridsPost.begin() + 0);
    }

    interface->gridsPost.clear();
}

void showPosts(std::vector<Post*> posts){

    // std::cout << "Posts:\n";
    // for(Post* p : posts){
    //     std::cout << p->getTexto() << "\n";
    // }
    // std::cout << '\n';
   

    
    limparGridPosts();
    for(Post* p:  posts){
        Usuario* autor = new Usuario(p->getUsername());

        //formando os atributos do post (imagem, label com nome e label com texto)
        GtkWidget* profile = newScaledImage(autor->getFotoFilePath().c_str(), 80, 80);
        GtkWidget* name = gtk_label_new(p->getUsername().c_str());
        GtkWidget* text = gtk_label_new(p->getTexto().c_str());
        
        //formando a nova grid
        GtkWidget* newGrid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
        gtk_widget_set_name(newGrid, "post");

        gtk_grid_insert_row (GTK_GRID(newGrid), 1);
        gtk_grid_insert_row (GTK_GRID(newGrid), 2);

        gtk_grid_attach(GTK_GRID(newGrid), profile, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), name, 2, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), text, 1, 2, 2, 1);

        interface->gridsPost.push_back(newGrid);

        //inserindo a nova grid na grid de posts
        GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "gridPosts"));
        gtk_grid_insert_row (GTK_GRID(gridPosts), interface->gridsPost.size());
        gtk_grid_attach (GTK_GRID(gridPosts), newGrid, 1, interface->gridsPost.size(), 1, 1);
    }

    interface->reset();
}

void on_name_clicked(GtkWidget *widget){
    GtkButton* button = GTK_BUTTON(widget); 
    std::string name = gtk_button_get_label(button);
    loadProfileScreen(name);
}

void showFollowing(){
    limparGridFollowing();

    std::vector<Usuario*> following = interface->getUsuario()->getFollowing();

    for(Usuario* user: following){
        //formando os atributos (imagem do usuario e label com o nome)
        GtkWidget* profile = newScaledImage(user->getFotoFilePath().c_str(), 80, 80);
        // GtkWidget* name = gtk_label_new(user->getNome().c_str());
        GtkButton* name = GTK_BUTTON(gtk_button_new_with_label(user->getNome().c_str()));
        gtk_widget_set_name(GTK_WIDGET(name), "button");
        g_signal_connect(name, "clicked", G_CALLBACK(on_name_clicked), NULL);

        //formando a nova grid
        GtkWidget* newGrid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
        gtk_widget_set_name(newGrid, "following");

        gtk_grid_insert_row (GTK_GRID(newGrid), 1);

        gtk_grid_attach(GTK_GRID(newGrid), profile, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), GTK_WIDGET(name), 2, 1, 1, 1);
        
        interface->gridsFollowing.push_back(newGrid);

        //inserindo a nova grid na grid de posts
        GtkWidget* gridFollowing = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "gridFollowing"));
        gtk_grid_insert_row (GTK_GRID(gridFollowing), interface->gridsFollowing.size());
        gtk_grid_attach (GTK_GRID(gridFollowing), newGrid, 1, interface->gridsFollowing.size(), 1, 1);
    }

    interface->reset();
}


void limparGridFollowing(){
    GtkWidget* gridFollowing = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "gridFollowing"));

    while(interface->gridsFollowing.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridFollowing), 1);
        interface->gridsFollowing.erase(interface->gridsFollowing.begin() + 0);
    }

    interface->gridsFollowing.clear();
}

/**
 * @brief carrega a tela home
*/
void on_homeButton_clicked(){
    loadHomeScreen();
}

void on_profileButton_clicked(){
    loadProfileScreen(interface->getUsuario()->getNome());
}

void on_logoutButton_clicked(){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack"));
    gtk_stack_set_visible_child_name(stack, "login");   
}

void on_searchBar_activate(){
    GtkSearchEntry* searchBar = GTK_SEARCH_ENTRY(gtk_builder_get_object(interface->getBuilder(), "searchBar"));
    std::string texto = gtk_entry_get_text (GTK_ENTRY(searchBar));

    if(Usuario::isValid(texto)){
        loadProfileScreen(texto);
        gtk_widget_set_name(GTK_WIDGET(searchBar), "entryNormal");
    }
    else{
        gtk_widget_set_name(GTK_WIDGET(searchBar), "entryWrong");
    }
    interface->reset();
}

void on_searchBar_search_changed(){
    GtkSearchEntry* searchBar = GTK_SEARCH_ENTRY(gtk_builder_get_object(interface->getBuilder(), "searchBar"));
    gtk_widget_set_name(GTK_WIDGET(searchBar), "entryNormal");
    interface->reset();
}

void on_profileImageHomeButton_clicked(){
    on_profileButton_clicked(); 
}


//profile
void on_followButton_clicked(){

    GtkButton* followButton = GTK_BUTTON(gtk_builder_get_object(interface->getBuilder(), "followButton"));
    std::string tipo = gtk_button_get_label(followButton);
    
    GtkLabel* profileUserNameLabel = GTK_LABEL(gtk_builder_get_object(interface->getBuilder(), "profileUserNameLabel"));
    std::string user = gtk_label_get_text(profileUserNameLabel);
    
    if(tipo == "Follow"){
        interface->getUsuario()->seguir(user);
        gtk_button_set_label(followButton, "Unfollow");
    }
    else if(tipo == "Unfollow"){
        interface->getUsuario()->desseguir(user);
        gtk_button_set_label(followButton, "Follow");
    }
    else if(tipo == "Edit"){
        
    }

    showFollowing();    
}