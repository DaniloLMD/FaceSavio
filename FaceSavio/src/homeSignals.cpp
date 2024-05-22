#include <iostream>

#include "../include/homeSignals.hpp"
#include <gtk/gtk.h>
#include "../include/Usuario.hpp"

Interface* interface = NULL;

//FUNCOES DE TESTE (APAGAR DEPOIS)
void on_mudarButton_clicked(){
    std::string novoUser;
    std::string atual = interface->getUsuario()->getNome();
    if(atual == "Danilo"){
        novoUser = "Tiago";
    }
    else if(atual == "Tiago"){
        novoUser = "Caio";
    }
    else{
        novoUser = "Danilo";
    }

    Usuario* novoUsuario = new Usuario(novoUser);
    interface->setUsuario(novoUsuario);
    loadHomeScreen();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void connectHomeSignals(void* newInterface){
    interface = (Interface*) newInterface;
}

void loadHomeScreen(){
    // GtkImage* profileImage = GTK_IMAGE(gtk_builder_get_object(interface->getBuilder(), "profileImageHome"));
    // gtk_image_set_from_file(profileImage, interface->getUsuario()->getFotoFilePath().c_str());
    // setScaledImage(profileImage, interface->getUsuario()->getFotoFilePath().c_str(), 10, 10);

    GtkWidget* profileImage = newScaledImage(interface->getUsuario()->getFotoFilePath().c_str(), 80, 80);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "profileImageHomeButton"));
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);
    
    showPosts();
    showFollowing();
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

    showPosts();
}

void limparGridPosts(){
    GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "gridPosts"));

    while(interface->gridsPost.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridPosts), 1);
        interface->gridsPost.erase(interface->gridsPost.begin() + 0);
    }

    interface->gridsPost.clear();
}

void showPosts(){

    limparGridPosts();
   
    std::vector<Post*> posts = interface->getUsuario()->loadPosts();

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

void showFollowing(){
    limparGridFollowing();

    std::vector<Usuario*> following = interface->getUsuario()->getFollowing();

    for(Usuario* user: following){
        //formando os atributos (imagem do usuario e label com o nome)
        GtkWidget* profile = newScaledImage(user->getFotoFilePath().c_str(), 80, 80);
        GtkWidget* name = gtk_label_new(user->getNome().c_str());

        //formando a nova grid
        GtkWidget* newGrid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
        gtk_widget_set_name(newGrid, "following");

        gtk_grid_insert_row (GTK_GRID(newGrid), 1);

        gtk_grid_attach(GTK_GRID(newGrid), profile, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), name, 2, 1, 1, 1);
        
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
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack"));
    gtk_stack_set_visible_child_name(stack, "home");   
    loadHomeScreen();
}

void on_logoutButton_clicked(){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack"));
    gtk_stack_set_visible_child_name(stack, "login");   
}