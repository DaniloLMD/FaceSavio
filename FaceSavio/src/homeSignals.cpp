#include "../include/Interface.hpp"

void Interface::showProfileImageHomeButton(){
    GtkWidget* profileImage = newScaledImage(this->getUsuario()->getFotoFilePath().c_str(), 80, 80);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "profileImageHomeButton"));
    GtkLabel* homeUsernameLabel = GTK_LABEL(gtk_builder_get_object(this->getBuilder(), "homeUsernameLabel"));
    gtk_label_set_text(homeUsernameLabel, this->getUsuario()->getNome().c_str());
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);
    
}

void Interface::loadHomeScreen(){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack2"));
    gtk_stack_set_visible_child_name(stack, "home");   

    showProfileImageHomeButton();

    gtk_widget_set_name(GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "searchBar")), "entryNormal");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "searchBar")), "Find user");

    std::string postText = "Write here";
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_builder_get_object(this->getBuilder(), "textBufferPost")), postText.c_str(), postText.size());

    showPosts(this->getUsuario()->loadAllPosts());
    showFollowing();
}

void Interface::loadProfileScreen(std::string username){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack2"));

    showProfileImageHomeButton();

    GtkButton* followButton = GTK_BUTTON(gtk_builder_get_object(this->getBuilder(), "followButton"));
    
    GtkWidget* deleteButton = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "deleteUserButton"));

    gtk_stack_set_visible_child_name(stack, "profile");   

    Usuario* user = new Usuario(username);
    GtkWidget* profileImage = newScaledImage(user->getFotoFilePath().c_str(), 120, 120);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "profileImageButton"));
    GtkLabel* profileUserNameLabel = GTK_LABEL(gtk_builder_get_object(this->getBuilder(), "profileUserNameLabel"));

    gtk_label_set_text(profileUserNameLabel, user->getNome().c_str());
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);

    showPosts(user->loadSelfPosts());

    if(username == this->getUsuario()->getNome()){
        gtk_button_set_label(followButton, "Edit");
        gtk_widget_show(deleteButton);
    }
    else{
        gtk_widget_hide(deleteButton);

        if(this->getUsuario()->isFollowing(username)){
            gtk_button_set_label(followButton, "Unfollow");
        }
        else{
            gtk_button_set_label(followButton, "Follow");
        }
    }
}

/**
 * @brief verifica se o limite de caracteres e de linhas foi atingido. Caso tenha sido, bloqueia a entrada de novos caracteres
*/
void Interface::on_textBufferPost_changed(GtkTextBuffer* buffer){
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    // Obtém o texto do buffer de texto
    std::string text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    const int MAX_COLUMNS = 70;
    const int MAX_LINES = 10;

    int caracteres = 0;
    int linhas = 0;

    std::string postText = "";
    for(char c: text){
        if(c == '\n'){
            caracteres = 0;
            linhas++;
        }
        else{
            caracteres++;
        }
        if(caracteres > MAX_COLUMNS){
            gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_builder_get_object(this->getBuilder(), "textBufferPost")), postText.c_str(), postText.size());
            g_signal_stop_emission_by_name(buffer, "insert-text");
            break;
        }
        if(linhas > MAX_LINES){
            gtk_text_buffer_set_text(GTK_TEXT_BUFFER(gtk_builder_get_object(this->getBuilder(), "textBufferPost")), postText.c_str(), postText.size());
            g_signal_stop_emission_by_name(buffer, "insert-text");
            break;
        }
        postText += c;
    }
}

/**
 * @brief adiciona um post quando o botão é apertado.
*/  
void Interface::on_buttonPost_clicked(){

    GtkBuilder* builder = this->getBuilder();
    GtkTextBuffer* buffer =  GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBufferPost"));

    //buffers para pegar o texto do text view
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    const char* postText = gtk_text_buffer_get_text(buffer, &start, &end, FALSE); 

    this->getUsuario()->publicar(postText);

    loadHomeScreen();
}

void Interface::limparGridPosts(){
    GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridPosts"));

    while(this->gridsPost.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridPosts), 1);
        this->gridsPost.erase(this->gridsPost.begin() + 0);
    }

    this->gridsPost.clear();
}

void Interface::showPosts(std::vector<Post*> posts){
    limparGridPosts();
    for(Post* p:  posts){
        Usuario* autor = new Usuario(p->getUsername());

        //formando os atributos do post (imagem, label com nome e label com texto)
        GtkWidget* profile = newScaledImage(autor->getFotoFilePath().c_str(), 100, 100);
        GtkWidget* name = gtk_label_new(p->getUsername().c_str());
        GtkWidget* text = gtk_label_new(p->getTexto().c_str());
        
        //formando a nova grid
        GtkWidget* newGrid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
        gtk_widget_set_name(newGrid, "post");
        gtk_widget_set_name(profile, "postProfile");
        gtk_widget_set_name(name, "postName");
        gtk_widget_set_name(text, "postText");

        gtk_grid_insert_row (GTK_GRID(newGrid), 1);
        gtk_grid_insert_row (GTK_GRID(newGrid), 2);
        gtk_grid_insert_row (GTK_GRID(newGrid), 3);

        //coluna, linha, largura, altura
        gtk_grid_attach(GTK_GRID(newGrid), name, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), profile, 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), text, 1, 1, 3, 3);

        this->gridsPost.push_back(newGrid);

        //inserindo a nova grid na grid de posts
        GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridPosts"));
        gtk_grid_insert_row (GTK_GRID(gridPosts), this->gridsPost.size());
        gtk_grid_attach (GTK_GRID(gridPosts), newGrid, 1, this->gridsPost.size(), 1, 1);
    }

    // this->reset();
    gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridPosts")));  
}

void Interface::on_name_clicked(GtkWidget *widget){
    GtkButton* button = GTK_BUTTON(widget); 
    std::string name = gtk_button_get_label(button);
    loadProfileScreen(name);
}

void Interface::showFollowing(){
    limparGridFollowing();

    std::vector<Usuario*> following = this->getUsuario()->getFollowing();

    for(Usuario* user: following){
        //formando os atributos (imagem do usuario e label com o nome)
        GtkWidget* profile = newScaledImage(user->getFotoFilePath().c_str(), 80, 80);
        // GtkWidget* name = gtk_label_new(user->getNome().c_str());
        GtkButton* name = GTK_BUTTON(gtk_button_new_with_label(user->getNome().c_str()));
        gtk_widget_set_name(GTK_WIDGET(name), "button");

        g_signal_connect(name, "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_name_clicked(widget);
        }), this
    );

        //formando a nova grid
        GtkWidget* newGrid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
        gtk_widget_set_name(newGrid, "following");

        gtk_grid_insert_row (GTK_GRID(newGrid), 1);

        gtk_grid_attach(GTK_GRID(newGrid), profile, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), GTK_WIDGET(name), 2, 1, 1, 1);
        
        this->gridsFollowing.push_back(newGrid);

        //inserindo a nova grid na grid de posts
        GtkWidget* gridFollowing = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridFollowing"));
        gtk_grid_insert_row (GTK_GRID(gridFollowing), this->gridsFollowing.size());
        gtk_grid_attach (GTK_GRID(gridFollowing), newGrid, 1, this->gridsFollowing.size(), 1, 1);
    }

    // this->reset();
    gtk_widget_show_all(GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridFollowing")));  
}


void Interface::limparGridFollowing(){
    GtkWidget* gridFollowing = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridFollowing"));

    while(this->gridsFollowing.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridFollowing), 1);
        this->gridsFollowing.erase(this->gridsFollowing.begin() + 0);
    }

    this->gridsFollowing.clear();
}

/**
 * @brief carrega a tela home
*/
void Interface::on_homeButton_clicked(){
    loadHomeScreen();
}

void Interface::on_profileButton_clicked(){
    loadProfileScreen(this->getUsuario()->getNome());
}

void Interface::on_logoutButton_clicked(){
    this->loadLoginScreen();   
}

void Interface::on_searchBar_activate(GtkSearchEntry* searchBar){
    std::string texto = gtk_entry_get_text (GTK_ENTRY(searchBar));

    if(Usuario::isValid(texto)){
        loadProfileScreen(texto);
        gtk_widget_set_name(GTK_WIDGET(searchBar), "entryNormal");
    }
    else{
        gtk_widget_set_name(GTK_WIDGET(searchBar), "entryWrong");
    }
}

void Interface::on_searchBar_search_changed(GtkSearchEntry* searchBar){
    gtk_widget_set_name(GTK_WIDGET(searchBar), "entryNormal");
}

void Interface::showFileChooserDialog(){
    GtkWidget* fileChooserPopup = gtk_file_chooser_dialog_new("FaceSavio", GTK_WINDOW(this->getMainWindow()), GTK_FILE_CHOOSER_ACTION_OPEN, NULL, NULL);
    
    g_signal_connect(fileChooserPopup, "file-activated",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_fileChooserDialog_file_activated(widget);
        }), this
    );
    
    gtk_widget_show_all(GTK_WIDGET(fileChooserPopup));
    gtk_dialog_run(GTK_DIALOG(fileChooserPopup));
}

void Interface::on_profileImageHomeButton_clicked(){
    loadProfileScreen(this->getUsuario()->getNome());
}

//profile
void Interface::on_followButton_clicked(){

    GtkButton* followButton = GTK_BUTTON(gtk_builder_get_object(this->getBuilder(), "followButton"));
    std::string tipo = gtk_button_get_label(followButton);
    
    GtkLabel* profileUserNameLabel = GTK_LABEL(gtk_builder_get_object(this->getBuilder(), "profileUserNameLabel"));
    std::string user = gtk_label_get_text(profileUserNameLabel);
    
    if(tipo == "Follow"){
        this->getUsuario()->seguir(user);
        gtk_button_set_label(followButton, "Unfollow");
    }
    else if(tipo == "Unfollow"){
        this->getUsuario()->desseguir(user);
        gtk_button_set_label(followButton, "Follow");
    }
    else if(tipo == "Edit"){ 
        showFileChooserDialog();
        loadProfileScreen(this->getUsuario()->getNome());
    }

    showFollowing();  
}

//signals de popup
void Interface::on_popUpOkButton_clicked(){
    gtk_widget_hide(GTK_WIDGET(GTK_MESSAGE_DIALOG(gtk_builder_get_object(this->getBuilder(), "popup"))));
}

void Interface::on_fileChooserDialog_file_activated(GtkWidget* fileChooserPopup){
    std::string filePath = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(fileChooserPopup));

    std::string extensao = "";
    for(int i = filePath.size() - 1; i >= 0; i--){
    if(filePath[i] == '.'){
        for(int j = i+1; j < filePath.size(); j++){
        extensao += filePath[j];
        }
        break;
    }
    }

    if(extensao != "png"){
    this->popup("Extensao invalida", "Por favor selecione um png.");
    return;
    }

    std::string cmd = "cp ";
    cmd += filePath;
    cmd += " ";
    cmd += this->getUsuario()->getFotoFilePath();

    system(cmd.c_str());

    gtk_widget_hide(GTK_WIDGET(fileChooserPopup));  

    showProfileImageHomeButton();
}

