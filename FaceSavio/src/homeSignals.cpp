#include <iostream>

#include "../include/homeSignals.hpp"
#include <gtk/gtk.h>

/**
 * @brief verifica se o limite de caracteres e de linhas foi atingido. Caso tenha sido, bloqueia a entrada de novos caracteres
*/
void on_textBufferPost_insert_text(GtkTextBuffer *buffer) {
    // Conta o numero de linhas no buffer de texto e
    // Verifica se o número de linhas excede o limite permitido
    gint line_count = gtk_text_buffer_get_line_count(buffer);
    const int MAX_LINES = 10;
    if (line_count > MAX_LINES) {
        // Se exceder, cancela a inserção do texto
        g_signal_stop_emission_by_name(buffer, "insert-text");
    }

     // Conta o numero de colunas no buffer de texto e
     // Verifica se o número de colunas excede o limite permitido
     GtkTextIter start, end;
     gtk_text_buffer_get_start_iter(buffer, &start);
     gtk_text_buffer_get_end_iter(buffer, &end);
     // Obtém o texto do buffer de texto
     std::string text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
     const int MAX_COLUMNS = 100;

    int caracteres = 0;
    for(char c: text){
        if(c == '\n'){
            caracteres = 0;
        }
        else{
            caracteres++;
        }
        if(caracteres > MAX_COLUMNS){
            g_signal_stop_emission_by_name(buffer, "insert-text");
        }
    }
}

/**
 * @brief adiciona um post quando o botão é apertado.
*/
void on_buttonPost_clicked(void* userdata){
    GtkBuilder* builder = interface->getBuilder(); 
    
    GtkTextBuffer* buffer =  GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBufferPost"));

    //buffers para pegar o texto do text view
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    //criando o novo post
    Post newPost;
    newPost.profile = scaledImage("../interface/imagens/gauloish.png", 80, 80);

    char name[100];
    snprintf(name, 100, "USUARIO %lu", interface->posts.size() + 1);
    newPost.name = gtk_label_new(name);

    const char* postText = gtk_text_buffer_get_text(buffer, &start, &end, FALSE); 
    newPost.text = gtk_label_new(postText);

    interface->posts.push_back(newPost);

    //formando a nova grid
    GtkWidget* newGrid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
    gtk_widget_set_name(newGrid, "post");

    gtk_grid_insert_row (GTK_GRID(newGrid), 1);
    gtk_grid_insert_row (GTK_GRID(newGrid), 2);

    gtk_grid_attach(GTK_GRID(newGrid), newPost.profile, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(newGrid), newPost.name, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(newGrid), newPost.text, 1, 2, 2, 1);
    interface->grids.push_back(newGrid);

    //inserindo a nova grid na grid de posts
    GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(builder, "gridPosts"));
    gtk_grid_insert_row (GTK_GRID(gridPosts), interface->grids.size());
    gtk_grid_attach (GTK_GRID(gridPosts), newGrid, 1, interface->grids.size(), 1, 1);

    interface->reset();
}

/**
 * @brief TEMPORARIO - reseta os posts
*/
void on_homeButton_clicked(){

    GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "gridPosts"));
    
    // for(auto x: interface->grids){
    //     gtk_grid_remove (gridPosts, x);
    // }

    while(interface->grids.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridPosts), 1);
        interface->grids.erase(interface->grids.begin() + 0);
    }

    interface->posts.clear();
    interface->grids.clear();
    interface->reset();
}