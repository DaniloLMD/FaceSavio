#include <iostream>
#include "../include/loginSignals.hpp"
#include "../include/paths.hpp"

Interface* interface = NULL;

enum opcoes{
    LOGIN = 1,
    CADASTRO
};

void connectLoginSignals(void* newInterface){
    interface = (Interface*) newInterface;
    connectHomeSignals(newInterface);
}

std::string getName(){
    GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(interface->getBuilder(), "name"));
    return gtk_entry_get_text (entry);
}

std::string getPassword(){
    GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(interface->getBuilder(), "password"));
    return gtk_entry_get_text (entry);
}

bool lembrar = false;
void loadLoginScreen(){
  GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack"));
  gtk_stack_set_visible_child_name(stack, "login");

  GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "name"));
  GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "password"));
  gtk_widget_set_name(name, "entryNormal");
  gtk_widget_set_name(password, "entryNormal");
  
  if(!lembrar){
    gtk_entry_set_text(GTK_ENTRY(name), "Name");
    gtk_entry_set_text(GTK_ENTRY(password), "password");
  }

}

bool solve(int op, std::string userName, std::string password);

void on_login_clicked(){
    if(solve(LOGIN, getName(), getPassword())){
        interface->setUsuario(new Usuario(getName()));
        GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack"));
        gtk_stack_set_visible_child_name(stack, "home"); 
        loadHomeScreen();
    }
    else{
        GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "name"));
        GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "password"));
        
        if(!Usuario::isValid(getName())) gtk_widget_set_name(name, "entryWrong");
        gtk_widget_set_name(password, "entryWrong");
    }
}

void on_cadastrar_clicked(){
    if(solve(CADASTRO, getName(), getPassword())){
        Usuario::mkDir(getName());
        interface->popup("Cadastro realizado", "");
        on_name_changed();
    }
    else{
        interface->popup("Cadastro falhou", "usuário inválido ou já existente");
    }
}

void on_remember_toggled(){
    lembrar = !lembrar;
}

void on_name_changed(){
  GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "name"));
  GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(interface->getBuilder(), "password"));
  gtk_widget_set_name(name, "entryNormal");
  gtk_widget_set_name(password, "entryNormal");
}
void on_name_activate(){
  on_login_clicked();
}
void on_password_activate(){
  on_login_clicked();
}


////////// parte do tiago //////////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define dbg(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef long double ld;
const int N = 2e5+10;
const int mod = 1e9+7;
const ll inf = 1e9+10;

#define vt vector
#define pb push_back
#define sz(x) (int)(x).size()

#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

string toLowerCase(string str) {
  for (int i = 0; i < str.length(); i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}

bool login(string& userName, string& password) {
  ifstream file(LOGIN_DATA_FILE_PATH);
  if (!file.is_open()) {
    cerr << "Error" << endl;
    return false;
  }

//   string lowerUserName = toLowerCase(userName);

  string data;
  while(getline(file, data)) {
    istringstream iss(data);
    string fileUserName, filePassword;

    if (getline(iss, fileUserName, ',') && getline(iss, filePassword)) {
      if (fileUserName == userName && filePassword == password) {
        return true;
      }
    }
  }

  return false;
}

bool userExists(const string& userName) {
  ifstream file(LOGIN_DATA_FILE_PATH);
  if (!file.is_open()) {
    cerr << "Error" << endl;
    return false;
  }

//   string lowerUserName = toLowerCase(userName);

  string data;
  while(getline(file, data)) {
    istringstream iss(data);
    string fileUserName;

    if (getline(iss, fileUserName, ',')) {
      if (fileUserName == userName) {
        return true;
      }
    }
  }

  return false;
}

bool registerUser(string &userName, string& password) {
//   string lowerUserName = toLowerCase(userName);

  if (userExists(userName)) {
    return false;
  }

  ofstream file(LOGIN_DATA_FILE_PATH, ios::app);
  if (!file.is_open()) {
    cerr << "Error!" << endl;
    return false;
  }

  file << userName << "," << password << endl;
  return true;
}

bool solve(int op, string userName, string password){
  if (op == LOGIN) {
    return login(userName, password);
  } 
  else if (op == CADASTRO) {
    return registerUser(userName, password);
  }
  
  return false;
}