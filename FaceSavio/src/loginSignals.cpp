#include "../include/Interface.hpp"

/**
 * @brief retorna a string escrita na Entry dedicada ao nome
 * @return string com o nome
*/
std::string Interface::getName(){
  GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "name"));
  return gtk_entry_get_text (entry);
}

/**
 * @brief retorna a string escrita na Entry dedicada a senha
 * @return string com a senha
*/
std::string Interface::getPassword(){
    GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "password"));
    return gtk_entry_get_text (entry);
}

/**
 * @brief carrega a tela de login
 * @return void
*/
void Interface::loadLoginScreen(){
  GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack"));
  gtk_stack_set_visible_child_name(stack, "login");

  GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
  GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
  gtk_widget_set_name(name, "entryNormal");
  gtk_widget_set_name(password, "entryNormal");
  
  if(!lembrar){
    gtk_entry_set_text(GTK_ENTRY(name), "");
    gtk_entry_set_text(GTK_ENTRY(password), "");
  }

}

/**
 * @brief signal de quando o botao de login é clicado
 * @return void
*/
void Interface::on_login_clicked(){
  if(login(this->getName(), this->getPassword())){
      this->setUsuario(new Usuario(getName()));
      GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack"));
      gtk_stack_set_visible_child_name(stack, "home"); 
      loadHomeScreen();
  }
  else{
      GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
      GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
      
      if(!Usuario::isValid(getName())) gtk_widget_set_name(name, "entryWrong");
      gtk_widget_set_name(password, "entryWrong");
  }
}

/**
 * @brief signal de quando o botao de cadastrar é clicado
 * @return void
*/
void Interface::on_cadastrar_clicked(){
    std::string name = getName();
    std::string password = getPassword();

    if(cadastrar(name, password)){
        Usuario u(name);
        this->popup("Cadastro realizado", "");
        on_name_changed();
    }
    else{
        this->popup("Cadastro falhou", "usuário inválido ou já existente");
    }
}

/**
 * @brief signal de quando a checkbox "Lembrar de mim" é ativada
 * @return void
*/
void Interface::on_remember_toggled(){
  lembrar = !lembrar;
}

/**
 * @brief quando a entry do nome for alterada, ela volta ao seu estagio normal
 * @return void
*/
void Interface::on_name_changed(){
  GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
  GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
  gtk_widget_set_name(name, "entryNormal");
  gtk_widget_set_name(password, "entryNormal");
}

/**
 * @brief quando aperta ENTER na entry de nome
*/
void Interface::on_name_activate(){
  on_login_clicked();
}

/**
 * @brief quando aperta ENTER na entry de senha
*/
void Interface::on_password_activate(){
  on_login_clicked();
}


#include <bits/stdc++.h>
/**
 * @brief checa se o nome e a senha estão compativeis com algum outro registrado no sistema para efetuar login
 * @param userName nome do usuario
 * @param password senha
 * @return true, se for possivel, false caso contrario
*/
bool Interface::login(std::string userName, std::string password) {
  

  std::ifstream file(LOGIN_DATA_FILE_PATH);
  if (!file.is_open()) {
    return false;
  }

  std::string data;
  while(getline(file, data)) {
    std::istringstream iss(data);
    std::string fileUserName, filePassword;

    if (getline(iss, fileUserName, ',') && getline(iss, filePassword)) {
      if (fileUserName == userName && filePassword == password) {
        return true;
      }
    }
  }

  return false;
}

/**
 * @brief tenta cadastrar um novo usuario, caso ele nao exista
 * @param userName nome do usuario
 * @param password senha
 * @return bool, se foi possivel cadastrar, false caso contrario
*/
bool Interface::cadastrar(std::string userName, std::string password) {
  if (Usuario::isValid(userName)) {
    return false;
  }
  if(userName.find(" ") != userName.npos) return false;
  if(!userName.size() || !password.size()) return false;

  FILE* ptr = fopen(LOGIN_DATA_FILE_PATH, "a");
  if(!ptr) return false;

  fprintf(ptr, "%s,%s\n", userName.c_str(), password.c_str());

  fclose(ptr);

  this->loadLoginScreen();

  return true;
}