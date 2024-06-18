# Documentação - POO - Projeto FaceSavio (Observer)

Tópicos

Autores

- *MARCELLO RONALD JOSÉ DA SILVA*
- *PEDRO HENRIQUE DOS SANTOS PEREIRA*
- *DANILO LOURENÇO MACEDO DIAS*
- *TIAGO FONSECA PIO*
- *CAIO PEREIRA FARIAS*

## Ferramentas/Linguagens e Tecnologias utilizadas

> Linguagem Utilizada: C++
Diagramação UML: LucidChart
Padrão de Projeto: Observer
> 

## Visão geral

O projeto visa a criação de uma rede social simples, na qual um dado usuário pode ter amigos, quando um usuário realiza um post, os amigos deste usuário são notificados.

---

## Funcionalidades/Requisitos

1. O programa permite ao usuário seguir um outro usuário já cadastrado
2. Validação de Login/Cadastro
3. Personalização de Perfil
4. Postagem de mensagens
5. Seguir/Parar de seguir usuários cadastrados
---

## Slides de apresentação → Os Slides explicitam de forma clara como o Padrão Observer foi aplicado no código.

[https://docs.google.com/presentation/d/1YX9zDxAPEjBk3EmqXn7jldUaGZHVJVwEl9I7Km_Nh0g/edit#slide=id.p](https://docs.google.com/presentation/d/1YX9zDxAPEjBk3EmqXn7jldUaGZHVJVwEl9I7Km_Nh0g/edit#slide=id.p)

---

## Regras de negócio.

- 1: O Programa deve ser compilado e executado em uma distro Unix Like - (Linux SO)

---

## Repositório - Código fonte

[link do repositório](https://github.com/DaniloLMD/POO/tree/main)

---

## Como executar o programa?

1. Clone o repositório na sua máquina local
2. A partir do terminal acesse o diretório clonado e em seguida acessa o diretório “FaceSavio”
3. Digite “make” no terminal

---

## Documentação da Implementação - Código Fonte

### Estrutura do Projeto:

**apps**: Contém arquivos de código fonte essencial para o funcionamento/montagem do programa

**bin**: Binários executáveis/compilados do programa.

**glade**: Contém os arquivos de interface de usuário.

**imagens**: Destinado a armazenas imagens utilizadas no projeto

**include**: Contém arquivos de cabeçalho.

**obj**: Arquivos .o, .obj são armazenados aqui após a compilação dos arquivos fontes.

**src**: Código fonte principal do programa, contém as classes e definições essenciais
**usuarios**: Banco de dados do Projeto.

MakeFile: Arquivo de automação de compilação para montagem do executavel.

### Apps:

faceSavio.cpp:

```cpp
#include "../include/Interface.hpp"
#include "../include/paths.hpp"

int main(int argc, char* argv[]){
    Interface* interface = new Interface(GLADE_FILE_PATH);
    interface->display();

    return 0;
}
```

Código de ponto de entrada do programa, Após a inclusão das bibliotecas é criado uma nova instância de “interface” passando GLADE_FILE_PATH como argumento para o constructor, o GLADE_FILE_PATH é então usado para carregar a descrição da interface gráfica.
E a linha seguinte chama o método display() da instância “interface”, exibindo assim ao usuário.

### Bin:

Contém o arquivo executável do programa: faceSavio

### Glade:

Contém arquivos .css e .glade
faceSavio.css: Estilização dos componentes de interface
faceSavio.glade: Definição das estruturas e dos componentes de interface

### Include:

- **GerenciadorNotificacoes.hpp**
    
    ```cpp
    #ifndef __GERENCIADOR_NOTIFICACOES_HPP__
    #define __GERENCIADOR_NOTIFICACOES_HPP__
    
    #include <vector>
    
    class Usuario; //declaração do usuario para poder compilar
    
    class GerenciadorNotificacoes{
        public:
            GerenciadorNotificacoes(Usuario* usuario);
    
            void adicionar(Usuario* notificavel);
    
            void notificarTodos(std::string msg);
    
        private:
            std::vector<Usuario*> notificaveis;
            Usuario* usuario;
    };
    
    #endif
    ```
    
    As duas primeiras linhas são chamadas de guardas de inclusão e servem para evitar que o conteúdo do arquivo de cabeçalho seja incluído mais de uma vez em um mesmo arquivo fonte o que poderia levar a erros de compilação.
    Na linha 4 é incluída a biblioteca padrão de vetores para c++
    Na linha 6 ocorre uma declaração antecipada, usada para informar ao compilador que a classe `Usuário` Existe ( É necessário pois é referenciado no cabeçalho )
    A partir da linha 8 inicia a definição da classe `GerenciadorNotificacoes`
    A classe é dividida entre membros públicos e privados
    
    - GerenciadorNotificacoes(Usuario* usuario); :
    O construtor aceita um ponteiro para um objeto `Usuario` e inicializa o objeto `GerenciadorNotificacoes` com ele.
    - void adicionar(Usuario* notificavel) : Este método aceita um ponteiro para um objeto `Usuario` e o adiciona à lista de notificáveis.
    - void notificarTodos(std::string msg) : Este método aceita uma string `msg` e envia essa mensagem a todos os usuários na lista de notificáveis.
    - std::vector<Usuario*> notificaveis : Um vetor de ponteiros para objetos `Usuario`. Este vetor armazena todos os usuários que devem ser notificados.
    - Usuario* usuario : Por fim Um ponteiro para um objeto `Usuario`. Este membro representa o usuário associado a este gerenciador de notificações.
    - #endif para encerrar as guardas de inclusão.
    
- **homeSignals.hpp**
    
    Arquivo feito apenas para garantir a inclusão do cabeçalho `interface.hpp` 
    
- **INotificavel.hpp**
    
    ```cpp
    class INotificavel{
        public:
            virtual void notificar(std::string msg, std::string autor){};
            virtual ~INotificavel() {}
    
        private:
    };
    ```
    
    INotificavel é uma interface, o cabeçalho define um método notificar que espera receber como parâmetro uma mensagem e o autor da mensagem, define também um destrutor, importante para evitar vazamentos de memória e garantir que todos os recursos alocados pela classe derivada sejam liberados corretamente.
    
- Interface.hpp
    
    ```
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
    ```
    
    Inclui uma série de bibliotecas: gtk, vector, Post, Usuario, paths.
    Define uma Estrutura InterfaceStruct e inicia uma definição para a classe Interface a partir da linha 13
    
    Constructor
    
    - Interface(const char* gladeFile) : Inicializa a interface carregando o arquivo Glade especificado, recebe como parâmetro o caminho para o arquivo Glade
    
    Métodos públicos esperados pelo cabeçalho:
    
    - `void activateCSS(const char* cssFile)`
        - : Aplica um arquivo CSS à interface para estilização, recebe como parâmetro o caminho para o arquivo css
    - `void display()`
        - : Exibe a janela principal da aplicação.
    - `void reset()`
        - : Redefine a interface para seu estado inicial
    - `void popup(std::string title, std::string text)`
        - : Exibe uma janela pop-up com um título e texto especificado que são passados como parâmetros
    - `GtkBuilder* getBuilder()`
        - : Retorna o ponteiro para o objeto `GtkBuilder` usado para construir a interface
    - `GtkWidget* getMainWindow()`
        - : Retorna o ponteiro para a janela principal
    - `Usuario* getUsuario()`
        - : Retorna o ponteiro para o `usuario` atual
    - `void setUsuario(Usuario* user)`
        - : Define o usuário atual, recebe no parâmetro um ponteiro para o objeto `Usuario`
    
    Atributos Públicos:
    
    - std::vector<GtkWidget*> gridsPost : Vetor de ponteiros para widgets de grade que exibem posts
    - std::vector<GtkWidget*> gridsFollowing : Vetor de ponteiros para widgets de grade que exibem os seguidores
    
    Métodos Privados : 
    
    - `void connectSymbols();`
        - **Descrição:** Conecta os sinais (eventos) da interface aos seus respectivos manipuladores.
    - `void loadLoginScreen();`
        - **Descrição:** Carrega a tela de login.
    - `void on_login_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão de login.
    - `void on_cadastrar_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão de cadastrar.
    - `void on_remember_toggled();`
        - **Descrição:** Manipulador do evento de toggle no botão de lembrar.
    - `void on_name_changed();`
        - **Descrição:** Manipulador do evento de mudança de texto no campo de nome.
    - `void on_name_activate();`
        - **Descrição:** Manipulador do evento de ativação do campo de nome.
    - `void on_password_activate();`
        - **Descrição:** Manipulador do evento de ativação do campo de senha.
    - `std::string getPassword();`
        - **Descrição:** Obtém a senha inserida pelo usuário.
        - **Retorno:** `std::string`: Senha do usuário.
    - `std::string getName();`
        - **Descrição:** Obtém o nome inserido pelo usuário.
        - **Retorno:** `std::string`: Nome do usuário.
    - `void loadHomeScreen();`
        - **Descrição:** Carrega a tela inicial (home).
    - `void loadProfileScreen(std::string);`
        - **Descrição:** Carrega a tela de perfil de um usuário específico.
        - **Parâmetros:**
            - `std::string`: Nome do usuário cujo perfil será carregado.
    - `void on_name_clicked(GtkWidget* widget);`
        - **Descrição:** Manipulador do evento de clique no nome do usuário.
        - **Parâmetros:**
            - `widget`: Ponteiro para o widget que foi clicado.
    - `void on_textBufferPost_changed(GtkTextBuffer* buffer);`
        - **Descrição:** Manipulador do evento de mudança no buffer de texto do post.
        - **Parâmetros:**
            - `buffer`: Ponteiro para o buffer de texto.
    - `void on_buttonPost_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão de postar.
    - `void on_homeButton_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão home.
    - `void on_logoutButton_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão de logout.
    - `void showPosts(std::vector<Post*> posts);`
        - **Descrição:** Exibe uma lista de posts na interface.
        - **Parâmetros:**
            - `posts`: Vetor de ponteiros para objetos `Post`.
    - `void showFollowing();`
        - **Descrição:** Exibe a lista de seguidores na interface.
    - `void showProfileImageHomeButton();`
        - **Descrição:** Exibe a imagem do perfil no botão home.
    - `void limparGridPosts();`
        - **Descrição:** Limpa a grade de posts exibidos.
    - `void limparGridFollowing();`
        - **Descrição:** Limpa a grade de seguidores exibidos.
    - `void on_searchBar_activate(GtkSearchEntry* searchBar);`
        - **Descrição:** Manipulador do evento de ativação da barra de busca.
        - **Parâmetros:**
            - `searchBar`: Ponteiro para a barra de busca.
    - `void on_searchBar_search_changed(GtkSearchEntry* searchBar);`
        - **Descrição:** Manipulador do evento de mudança na barra de busca.
        - **Parâmetros:**
            - `searchBar`: Ponteiro para a barra de busca.
    - `void on_profileImageHomeButton_clicked();`
        - **Descrição:** Manipulador do evento de clique na imagem do perfil no botão home.
    - `void on_profileButton_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão de perfil.
    - `void on_followButton_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão de seguir (no perfil).
    - `void on_popUpOkButton_clicked();`
        - **Descrição:** Manipulador do evento de clique no botão OK da janela pop-up.
    - `void showFileChooserDialog();`
        - **Descrição:** Exibe a caixa de diálogo para escolha de arquivos.
    - `void on_fileChooserDialog_file_activated(GtkWidget* fileChooserPopup);`
        - **Descrição:** Manipulador do evento de ativação da caixa de diálogo de escolha de arquivos.
        - **Parâmetros:**
            - `fileChooserPopup`: Ponteiro para o widget da caixa de diálogo.
    
    Atributos privados:
    
    - `const char* gladeFile;`
        - **Descrição:** Caminho para o arquivo Glade que define a interface.
    - `GtkBuilder* builder;`
        - **Descrição:** Ponteiro para o objeto `GtkBuilder` usado para construir a interface.
    - `GtkWidget* mainWindow;`
        - **Descrição:** Ponteiro para a janela principal.
    - `Usuario* usuario;`
        - **Descrição:** Ponteiro para o usuário atual.
- Post.hpp
    
    ```cpp
    #ifndef __POST_HPP__
    #define __POST_HPP__
    
    #include <gtk/gtk.h>
    #include <iostream>
    
    class Post{
        public:
    
            Post(int id);
    
            int getID() { return id; }
            std::string getTexto() { return texto; }
            std::string getUsername() { return username; }
    
            static void newPost(int id, std::string texto, std::string autor);
            static int getTotalPosts();
            static void setTotalPosts(int quantidade);
            static std::string getTotalPostsFilePath();
            static std::string getPostsFolderPath();
            static std::string getPostFilePath(int id);
    
            static bool isValid(int id);
    
        private:
            int id;
            std::string texto;
            std::string username;
    };
    
    #endif
    ```
    
    O cabeçalho Post inclui as libs: gtk e uma de string.
    
    Construtor: `newPost(int id, std::string texto, std::string autor`
    Na definição de métodos/atributos públicos têm-se: 
    Get: `int getID() { return id; }` → retorna o ID do post
    
    std::string `getTexto() { return texto; }` → retorna o texto do post
    std::string `getUsername() { return username; }` → retorna o nome do usuário que fez o post.
    
    os outros são getters e setters relativos aos caminhos dos posts e demais arquivos
    
- Usuario.hpp

```cpp
#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <vector>

#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/INotificavel.hpp"
#include "Post.hpp"

class Usuario : public INotificavel {
    public:
        Usuario(std::string nome);

        ~Usuario();

        void mkDir(std::string name);
        static bool isValid(std::string name);

        std::string getNome();

        void publicar(std::string msg);

        void seguir(std::string usuario);
        void desseguir(std::string usuario);
        
        void apagarUsuario();

        void notificar(std::string autor, int postId) override;

        bool isFollowing(std::string user);

        void loadGerenciadorNotificacoes();

        std::vector<Post> loadFeed();
        std::vector<Post> loadSelfPosts();
        std::vector<Usuario> getFollowing();
        std::vector<Usuario> getFollowers();

        std::string getFotoFilePath();

    private:
        std::string nome;
        GerenciadorNotificacoes gerenciadorNotificacoes;

        //funcoes de acesso aos arquivos
        int getQuantidadePosts();
        void setQuantidadePosts(int quantidade);  

        void addPostToFeed(std::string user, int id);
        std::string getUserFolderPath();
        std::string getFollowersFilePath();
        std::string getFollowingFilePath();
        // std::string getSelfPostsFolderPath();   
        std::string getSelfPostsFilePath();   
        std::string getQuantidadePostsFilePath();
        std::string getQuantidadeFeedFilePath();
        int getQuantidadeFeed();
        void setQuantidadeFeed(int v);
        std::string getFeedFolderPath();
        std::string getFeedFilePath(std::string username);
};

#endif
```

Construtor: `Usuário(std::string nome);` 

métodos estáticos
`static void mkDir(std::string name)` : Cria um diretório com o nome especificado

`static bool isValid(std::string name)` :   Verifica se o nome especificado é válido para uso como nome de usuário

métodos de acesso:

- `getNome`: Retorna o nome do usuário.
- `getFotoFilePath`: Retorna o caminho do arquivo da foto do usuário.

Ações do usuário: 

- `publicar`: Permite que o usuário publique uma mensagem.
- `seguir`: Permite que o usuário siga outro usuário.
- `desseguir`: Permite que o usuário deixe de seguir outro usuário.
- `notificar` : Este método é chamado para notificar o usuário sobre uma nova mensagem publicada por outro usuário
- `isfollowing` : Verifica se o usuário está seguindo outro usuário especificado.

Métodos de carregamento de dados:

- `loadAllPosts`: Carrega todos os posts feitos por este usuário e pelos usuários que ele segue.
- `loadSelfPosts`: Carrega apenas os posts feitos por este usuário.
- `getFollowing`: Retorna uma lista dos usuários que este usuário está seguindo.
- `getFollowers`: Retorna uma lista dos usuários que estão seguindo este usuário.

Á parte dos getters e setters, destaca-se o método `void` `addPostToFeed(std::string user, int id);` o qual tem sua declaração auto-explicativa.

## SRC

### GerenciadorNotificacoes.cpp

```cpp
#include <iostream>
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/Usuario.hpp"

// Construtor
GerenciadorNotificacoes::GerenciadorNotificacoes(Usuario* usuario) : usuario(usuario) {}

/**
 * @brief adiciona um usuario ao gerenciador de notificacoes 
 * @param notificavel usuario a ser adicionado
 * @return void
*/
void GerenciadorNotificacoes::adicionar(Usuario* notificavel) {
    notificaveis.push_back(notificavel);
}

/**
 * @brief remove um usuario do gerenciador de notificacoes
 * @param notificavel usuario a ser removido
 * @return void
*/
void GerenciadorNotificacoes::remover(Usuario* notificavel){
    for(int i = 0; i < notificaveis.size(); i++){
        if(notificaveis[i]->getNome() == notificavel->getNome()){
            notificaveis.erase(notificaveis.begin() + i);
            break;
        }
    }
}

/**
 * @brief limpa totalmente o gerenciador de notificacoes
 * @return void
*/
void GerenciadorNotificacoes::clear(){
    for(auto x: notificaveis){
        delete x;
    }
    notificaveis.clear();
}

/**
 * @brief notifica todos os usuarios desse gerenciador de notificacoes sobre um post
 * @param postId ID do post a ser notificado
 * @return void
*/
void GerenciadorNotificacoes::notificarTodos(int postId) {
    for (auto notificavel : notificaveis) {
        notificavel->notificar(this->usuario->getNome(), postId);
    }
}
```

A partir daqui as funções especificadas no cabeçalho são implementadas, suas funcionalidades são descritas nos comentários.

### homeSignals.cpp

Este arquivo estabelece um ligamento entre a Interface gráfica da aplicação e a lógica da aplicação, contém diversas funções que são chamadas em resposta a eventos na interface do usuário.

1. showProfileImageHomeButton() : Atualizar a interface com a imagem de perfil e o nome do usuário

```cpp
void Interface::showProfileImageHomeButton(){
    GtkWidget* profileImage = newScaledImage(this->getUsuario()->getFotoFilePath().c_str(), 80, 80);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "profileImageHomeButton"));
    GtkLabel* homeUsernameLabel = GTK_LABEL(gtk_builder_get_object(this->getBuilder(), "homeUsernameLabel"));
    gtk_label_set_text(homeUsernameLabel, this->getUsuario()->getNome().c_str());
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);
    
}
```

Através da biblioteca `GTK` a interface gráfica do programa é criada.
O método `showProfileImageHomeButton()` faz a manipulação de alguns widgets (componentes da GUI) de forma direta

`profileImage` → Criado para exibir a imagem de perfil do usuário usando do método auxiliar `newScaledImage` no caso em questão ele retorna uma imagem 80x80 pixels a partir do caminho da foto

`profileImageButton` → Um botão na interface que mostrará a imagem de perfil

`homeUsernameLabel` → Um rótulo na interface que exibirá o nome do usuário.
`gtk_label_set_text` → Utilizado para atualizar o texto do rótulo com o nome do usuário

`gtk_button_set_image` → Usado para definir a imagem do botão com a imagem de perfil do usuário

1. loadHomeScreen() : Carrega a tela principal

```cpp
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
```

`stack` → Obtém a referência ao widget `GtkStack` chamado "stack2" e define o widget visível atual como "home" e `gtk_stack_set_visible_child_name()` define qual desses filhos deve ser exibido.
`gtk_widget_set_name` e `gtk_entry_set_text` configuram a barra de busca,

`postText` e `gtk_entry_set_text` configuram o buffer de texto do Post.

Por fim: `showPosts` e `showFollowing` exibem as postagens do usuário logado e os usuários que ele segue respectivamente.

1. loadProfileScreen() : Carrega os perfis de usuário

```
void Interface::loadProfileScreen(std::string username){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack2"));

    showProfileImageHomeButton();

    GtkButton* followButton = GTK_BUTTON(gtk_builder_get_object(this->getBuilder(), "followButton"));
    if(username == this->getUsuario()->getNome()){
        gtk_button_set_label(followButton, "Edit");
    }
    else{
        if(this->getUsuario()->isFollowing(username)){
            gtk_button_set_label(followButton, "Unfollow");
        }
        else{
            gtk_button_set_label(followButton, "Follow");
        }
    }

    gtk_stack_set_visible_child_name(stack, "profile");   

    Usuario* user = new Usuario(username);
    GtkWidget* profileImage = newScaledImage(user->getFotoFilePath().c_str(), 120, 120);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "profileImageButton"));
    GtkLabel* profileUserNameLabel = GTK_LABEL(gtk_builder_get_object(this->getBuilder(), "profileUserNameLabel"));

    gtk_label_set_text(profileUserNameLabel, user->getNome().c_str());
    gtk_button_set_image (GTK_BUTTON (profileImageButton), profileImage);

    showPosts(user->loadSelfPosts());
}
```

Função encarregada de carregar os perfis de usuários na tela, caso seja o perfil do usuário logado, o botão de seguir é exibido como “Edit” onde o usuário pode definir ou alterar sua imagem de perfil, no caso contrário ele pode seguir ou deixar de seguir o outro usuário conforme a condição lógica definida no código.

```cpp
    Usuario* user = new Usuario(username);
    GtkWidget* profileImage = newScaledImage(user->getFotoFilePath().c_str(), 120, 120);
    GtkWidget* profileImageButton =  GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "profileImageButton"));
    GtkLabel* profileUserNameLabel = GTK_LABEL(gtk_builder_get_object(this->getBuilder(), "profileUserNameLabel"));
```

Este bloco instancia um Objeto Usuario e usa dos métodos da biblioteca Gtk para renderizar a parte da foto de usuário bem como seu nome

 `gtk_label_set_text()` → Atualiza o rótulo a fim de mostrar o nome do usuário requerido
 Explicação em detalhes: No primeiro parâmetro é passado um ponteiro para um objeto `GtkLabel` que nada mais é do que um widget de rótulo da interface gráfica, esse ponteiro é o: `profileUserNameLabel` e também é passado como segundo parâmetro um método de Usuário `user->getNome().c_str()` getNome() retorna uma string e c_str() retorna um ponteiro para um Array de caracteres, tendo o nome do usuário e o rótulo Gtk, ele atualiza em tempo de execução o nome do usuário.

`gtk_button_set_image()` → Atualiza o botão que mostra a imagem de perfil do usuário requerido

Explicação em detalhes: **GTK_BUTTON(profileImageButton)**: É um ponteiro para um objeto `GtkButton` usa-se a marco “GTK_BUTTON” para converter um objeto genérico GTK para um GtkButton e como segundo parâmetro passa-se o `profileImage` já definido acima que é a imagem relativa ao usuário em questão.

`showPosts(user->loadSelfPosts())` → Por último é chamado o método `showPosts` que mostra as postagens do usuário carregado.

1. on_textBufferPost_changed() : *verifica se o limite de caracteres e de linhas foi atingido. Caso tenha sido, bloqueia a entrada de novos caracteres*

```
void Interface::on_textBufferPost_changed(GtkTextBuffer* buffer){
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    // Obtém o texto do buffer de texto
    std::string text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    const int MAX_COLUMNS = 100;
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
```

O primeiro bloco de código estabelece iteradores sobre o buffer de texto
`gtk_text_buffer_get_start_iter(buffer, &start)` → Estabelece um iterador para o início do buffer

`gtk_text_buffer_get_end_iter(buffer, &end)` → Estabelece um iterador para o fim do buffer

`MAX_COLUMNS` e `MAX_LINES` definem os limites para o número de caracteres por linha e o número de linhas, respectivamente, são variáveis de controle.

A próxima parte do código estabelece um looping que faz a verificação da contagem de caracteres máxima permitida, onde:

O loop percorre cada caractere no texto. Se o caractere for uma nova linha (`\n`), o contador de caracteres é reiniciado e o contador de linhas é incrementado.
Se o número de caracteres em uma linha exceder `MAX_COLUMNS` ou o número de linhas exceder `MAX_LINES`, a função redefine o texto do buffer para o último estado válido (`postText`) e impede a inserção de novos caracteres com `g_signal_stop_emission_by_name`.
Caso esteja tudo certo a variável `postText` é incrementada com o Caracter em questão no looping.

1. on_buttonPost_clicked() : *adiciona um post quando o botão é apertado.*

```
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
```

1. limparGridPosts()

```
void Interface::limparGridPosts(){
    GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridPosts"));

    while(this->gridsPost.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridPosts), 1);
        this->gridsPost.erase(this->gridsPost.begin() + 0);
    }

    this->gridsPost.clear();
}
```

O método `limparGridPosts` faz o seguinte:

1. Obtém o widget `gridPosts` do builder.
2. Entra em um loop que continua enquanto `gridsPost` não estiver vazio.
    - Remove a linha 1 do grid `gridPosts`.
    - Remove o primeiro elemento do vetor `gridsPost`.
3. Após o loop, limpa o vetor `gridsPost`

 

7.  showPosts()

```cpp
void Interface::showPosts(std::vector<Post*> posts){
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

        this->gridsPost.push_back(newGrid);

        //inserindo a nova grid na grid de posts
        GtkWidget* gridPosts = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridPosts"));
        gtk_grid_insert_row (GTK_GRID(gridPosts), this->gridsPost.size());
        gtk_grid_attach (GTK_GRID(gridPosts), newGrid, 1, this->gridsPost.size(), 1, 1);
    }

    this->reset();
}
```

Resumo do método:

1. **Limpa a Grade Atual**:
    - Chama o método `limparGridPosts` para limpar qualquer conteúdo existente na grade de posts (`gridPosts`).
2. **Itera Sobre os Posts**:
    - Percorre cada objeto `Post` no vetor `posts`.
3. **Criar Widgets para Cada Post**:
    - Para cada post, cria um objeto `Usuario` correspondente ao autor do post.
    - Cria widgets GTK para exibir a foto de perfil (`profile`), o nome do usuário (`name`) e o texto do post (`text`).
4. **Formar uma Nova Grade**:
    - Cria uma nova grade (`newGrid`) para cada post.
    - Configura a nova grade para ter colunas homogêneas.
    - Insere duas linhas na nova grade.
    - Anexa os widgets de perfil, nome e texto na nova grade nas posições apropriadas.
5. **Adicionar a Nova Grade ao Vetor**:
    - Adiciona a nova grade (`newGrid`) ao vetor `gridsPost`.
6. **Inserir a Nova Grade na Grade de Posts Principal**:
    - Obtém a grade principal (`gridPosts`) da interface.
    - Insere uma nova linha na grade principal.
    - Anexa a nova grade (`newGrid`) na grade principal na nova linha.
7. **Resetar a Interface**:
    - Chama o método `reset` para possivelmente atualizar ou redesenhar a interface.

1. on_name_clicked() → captura o clique num dado botão com nome e carrega um perfil associado a este nome.

```cpp
void Interface::on_name_clicked(GtkWidget *widget){
    GtkButton* button = GTK_BUTTON(widget); 
    std::string name = gtk_button_get_label(button);
    loadProfileScreen(name);
}
```

1. showFollowing() → Mostra os usuários que está seguindo

```cpp
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

    this->reset();
}
```

Resumo: 
O método `showFollowing` é responsável por exibir uma lista de usuários que o usuário atual está seguindo. Ele limpa a grade atual de "following" e popula com novos dados baseados no vetor de usuários que o usuário atual segue.

Passos Detalhados do Método

1. **Limpa a Grade Atual de Following**:
    
    ```cpp
    limparGridFollowing();
    ```
    
    - Chama um método para limpar qualquer conteúdo existente na grade de "following".
2. **Obtém a Lista de Usuários Seguidos**:
    
    ```cpp
    std::vector<Usuario*> following = this->getUsuario()->getFollowing();
    ```
    
    - Obtém a lista de usuários que o usuário atual (usuário logado) está seguindo.
3. **Iterar Sobre Cada Usuário na Lista**:
    
    ```cpp
    for(Usuario* user: following){
    ```
    
    - Percorre cada objeto `Usuario` no vetor `following`.
4. **Criar Widgets para Cada Usuário**:
    - **Imagem de Perfil**:
        
        ```cpp
        GtkWidget* profile = newScaledImage(user->getFotoFilePath().c_str(), 80, 80);
        ```
        
        - Cria um widget para a imagem de perfil do usuário redimensionada para 80x80 pixels.
    - **Botão com o Nome do Usuário**:
        
        ```cpp
        GtkButton* name = GTK_BUTTON(gtk_button_new_with_label(user->getNome().c_str()));
        gtk_widget_set_name(GTK_WIDGET(name), "button");
        ```
        
        - Cria um botão com o nome do usuário. O nome do botão é definido como "button" para estilização ou identificação.
5. **Conecta Sinal de Clique ao Botão**:
    
    ```cpp
    g_signal_connect(name, "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_name_clicked(widget);
        }), this
    );
    ```
    
    - Conecta o sinal de clique do botão a uma função lambda (Função anônima) que chama `on_name_clicked`. Quando o botão é clicado, `on_name_clicked` é chamado com o botão como argumento.
6. **Cria uma Nova Grade para Cada Usuário**:
    - **Nova Grade**:
        
        ```cpp
        GtkWidget* newGrid = gtk_grid_new();
        gtk_grid_set_column_homogeneous(GTK_GRID(newGrid), TRUE);
        gtk_widget_set_name(newGrid, "following");
        ```
        
        - Cria uma nova grade (`GtkGrid`) para o usuário e define suas colunas como homogêneas (iguais em largura). O nome da grade é definido como "following".
    - **Insere Linha na Nova Grade**:
        
        ```cpp
        gtk_grid_insert_row(GTK_GRID(newGrid), 1);
        ```
        
    - **Adiciona Widgets à Nova Grade**:
        
        ```cpp
        gtk_grid_attach(GTK_GRID(newGrid), profile, 1, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(newGrid), GTK_WIDGET(name), 2, 1, 1, 1);
        ```
        
        - Adiciona os widgets de perfil e nome do usuário à nova grade.
7. **Adiciona a Nova Grade ao Vetor de Grades Following**:
    
    ```cpp
    this->gridsFollowing.push_back(newGrid);
    ```
    
8. **Insere a Nova Grade na Grade Principal de Following**:
    - **Obtém a Grade Principal de Following**:
        
        ```cpp
        GtkWidget* gridFollowing = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridFollowing"));
        ```
        
    - **Insere Linha na Grade Principal**:
        
        ```cpp
        gtk_grid_insert_row(GTK_GRID(gridFollowing), this->gridsFollowing.size());
        ```
        
    - **Adiciona a Nova Grade à Grade Principal**:
        
        ```cpp
        gtk_grid_attach(GTK_GRID(gridFollowing), newGrid, 1, this->gridsFollowing.size(), 1, 1);
        ```
        
9. Reseta a Interface:
    
    ```cpp
    this->reset();
    ```
    
    - Chama o método `reset` para possivelmente atualizar ou redesenhar a interface.
10. limparGridFollowing()

```
void Interface::limparGridFollowing(){
    GtkWidget* gridFollowing = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "gridFollowing"));

    while(this->gridsFollowing.size() > 0){
        gtk_grid_remove_row (GTK_GRID(gridFollowing), 1);
        this->gridsFollowing.erase(this->gridsFollowing.begin() + 0);
    }

    this->gridsFollowing.clear();
}
```

Aplica o mesmo procedimento de `limparGridPosts` porém para o grid de usuários sendo seguidos.

11. Códigos referentes a ativação alguns elementos da interface

```cpp
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
    this->reset();
}

void Interface::on_searchBar_search_changed(GtkSearchEntry* searchBar){
    gtk_widget_set_name(GTK_WIDGET(searchBar), "entryNormal");
    this->reset();
}
```

`on_homeButton_clicked` → após o clique do botão recarrega a tela home
`on_profileButton_clicked` → após o clique no botão referente a algum usuário, carrega o perfil daquele usuário
`on_logoutButton_clicked` → rastreia o clique no botão de logout e recarrega a tela de login
`on_searchBar_activate` → rastreia as ações tomadas no campo de busca de usuário a partir do envio de informações, ou seja a partir da teclagem da tecla “Enter”;
`on_searchBar_search_changed` → rastreia as ações tomadas no campo de busca a partir da mudança de texto;

12. showFileChooserDialog

```cpp
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
```

Esse método `showFileChooserDialog` cria e exibe um diálogo de seleção de arquivo usando o widget `GtkFileChooserDialog` do GTK.

13. on_followButton_clicked

```cpp
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
```

Esse método rastreia o clique no botão de seguir ou de editar e modifica a partir da tag rotulada no momento do clique;

1. on_fileChooserDialog_file_activated

```cpp
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
```

É chamado quando um arquivo é selecionado e ativado no diálogo de seleção de arquivo.

- `std::string filePath = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(fileChooserPopup));`: Esta linha obtém o caminho do arquivo selecionado no diálogo de seleção de arquivo.
- `std::string extensao = "";`: Aqui, é inicializada uma string vazia para armazenar a extensão do arquivo.
- `for(int i = filePath.size() - 1; i >= 0; i--)`: Este é um loop que percorre o caminho do arquivo de trás para frente para encontrar o ponto (.) que indica o início da extensão do arquivo.
- `if(filePath[i] == '.'){`: Quando o ponto é encontrado, o código entra neste bloco.
    - `for(int j = i+1; j < filePath.size(); j++){ extensao += filePath[j]; }`: Este loop itera sobre os caracteres após o ponto encontrado e os adiciona à string `extensao`, formando a extensão do arquivo.
- `if(extensao != "png")`: Aqui, é verificado se a extensão do arquivo não é "png". Se não for, uma mensagem de pop-up é exibida informando que a extensão do arquivo é inválida (neste caso, aceitando apenas arquivos .png), e o método retorna sem fazer mais nada.
- Se a extensão for "png", então o código continua:
    - `std::string cmd = "cp ";`: É criada uma string `cmd` que contém o comando para copiar o arquivo selecionado.
    - `cmd += filePath;`: Adiciona o caminho do arquivo selecionado à string `cmd`.
    - `cmd += " ";`: Adiciona um espaço à string `cmd`.
    - `cmd += this->getUsuario()->getFotoFilePath();`: Adiciona o caminho do arquivo de foto do usuário atual à string `cmd`.
    - `system(cmd.c_str());`: Executa o comando de cópia usando a função `system`, copiando o arquivo selecionado para o diretório de foto do usuário.
- `gtk_widget_hide(GTK_WIDGET(fileChooserPopup));`: Esconde o diálogo de seleção de arquivo após o arquivo ser selecionado e a operação de cópia ser concluída.
- `showProfileImageHomeButton();`: Provavelmente, isso exibe a imagem do perfil do usuário na interface, atualizando-a para refletir a nova imagem selecionada.

### Interface.cpp

**Constructor**

```cpp
// Construtor
Interface::Interface() {
    gtk_init(NULL, NULL);
    builder = gtk_builder_new_from_file(GLADE_FILE_PATH);
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
}
```

**Ativa o Css na interface usando os métodos do gtk**

```cpp
void Interface::activateCSS (const char* cssFile) {
	GtkCssProvider *css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider, cssFile, 0);
	gtk_style_context_add_provider_for_screen(
	gdk_screen_get_default(),
	GTK_STYLE_PROVIDER(css_provider),
		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
	);
}
```

**Display →** Tem por função exibir a interface na tela, carregando as funções principais definidas na interface.

```cpp
**
 * @brief prepara a interface para ser exibida na tela
*/
void Interface::display(){
    activateCSS(CSS_FILE_PATH);
    connectSymbols();
    loadLoginScreen();
    gtk_widget_show(mainWindow);
    gtk_main();
}
```

**Se conecta com os signals (sinais) definidos.**

```cpp
**
 * @brief conecta as funcoes da interface, ligando cada interaçao com um signal
*/
void Interface::connectSymbols(){   

    g_signal_connect(this->getMainWindow(), "destroy", G_CALLBACK(gtk_main_quit), NULL);

```

**Signals da página de login**

```cpp
g_signal_connect(gtk_builder_get_object(builder, "login"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_login_clicked();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "cadastrar"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_cadastrar_clicked();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "remember"), "toggled",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_remember_toggled();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "password"), "activate",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_password_activate();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "name"), "activate",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_name_activate();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "name"), "changed",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_name_changed();
        }), this
    );
```

**Symbols da página home**

```cpp
g_signal_connect(gtk_builder_get_object(builder, "popUpOkButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_popUpOkButton_clicked();
        }), this
    );
    
    g_signal_connect(gtk_builder_get_object(builder, "textBufferPost"), "changed",
        G_CALLBACK(+[](GtkTextBuffer *buffer, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_textBufferPost_changed(buffer);
        }), this
    );
    
    g_signal_connect(gtk_builder_get_object(builder, "homeButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_homeButton_clicked();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "logoutButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_logoutButton_clicked();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "searchBar"), "activate",
        G_CALLBACK(+[](GtkSearchEntry* searchBar, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_searchBar_activate(searchBar);
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "searchBar"), "search_changed",
        G_CALLBACK(+[](GtkSearchEntry* searchBar, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_searchBar_search_changed(searchBar);
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "profileImageHomeButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_profileImageHomeButton_clicked();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "profileButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_profileButton_clicked();
        }), this
    );

    g_signal_connect(gtk_builder_get_object(builder, "buttonPost"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_buttonPost_clicked();
        }), this
    );
```

**Signal de perfil**

```cpp
 g_signal_connect(gtk_builder_get_object(builder, "followButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_followButton_clicked();
        }), this
    );
```

**Signal de deletar perfil**

```cpp
 g_signal_connect(gtk_builder_get_object(builder, "deleteUserButton"), "clicked",
        G_CALLBACK(+[](GtkWidget* widget, void* user_data) {
            Interface* self = (Interface*) user_data;
            self->on_deleteUserButton_clicked();
        }), this
    );
```

…

### Post.cpp

Funções principais → `post` , `newPost`

**Função Post (Constructor):**

```cpp
Post::Post(int id) : id(id) {

    if(id > Post::getTotalPosts() || id < 0){
        std::cout << "ID invalido, post inexistente!\n";
        exit(EXIT_FAILURE);
    }

    std::string postFilePath = this->getPostFilePath(id);
    FILE* postFilePointer = fopen(postFilePath.c_str(), "r");
    
    char c;
    char username[100];
    fscanf(postFilePointer, "%[^\n]%*c", username);
    fscanf(postFilePointer, "%d%*c", &id);

    std::string texto = "";
    while(fscanf(postFilePointer, "%c", &c) != EOF){
        texto += c;
    }

    fclose(postFilePointer);

    this->texto = texto;
    this->username = username;
}
```

Recebe um recebe um identificador (`id`) como parâmetro

Inicialmente a função faz uma validação do ID do post a partir de duas condições, após isso o método: Constrói o caminho para um arquivo de post específico com base no `id` e abre o arquivo, após isso é feito uma leitura completa do arquivo encaminhado, em seguida faz-se o fechamento do arquivo e por fim a atribuição dos valores.

**Função newPost** 

```cpp
void Post::newPost(int id, std::string texto, std::string autor){
    if(id > Post::getTotalPosts()){ //cria um novo post na memoria
        //string com o caminho para o local que sera armazenado o novo post
        std::string newPostFilePath = Post::getPostsFolderPath();
        newPostFilePath += "post";
        newPostFilePath += std::to_string(id);
        newPostFilePath += ".txt";

        //escrevendo o novo post
        FILE* newPostFilePointer = fopen(newPostFilePath.c_str(), "w");
        fprintf(newPostFilePointer, "%s\n", autor.c_str());
        fprintf(newPostFilePointer, "%d\n", id);
        fprintf(newPostFilePointer, "%s", texto.c_str());
        fclose(newPostFilePointer);

        Post::setTotalPosts(Post::getTotalPosts() + 1);
    }
}
```

Esse método cria um novo post se o `id` fornecido for maior que o total de posts existentes. Ela constrói o caminho do arquivo para o novo post, escreve o autor, o `id` e o texto no arquivo, e atualiza o total de posts.

Getters/Setters: `getTotalPosts` `getPostsFolderPath` `getPostFilePath` `getTotalPostsFilePath` `setTotalPosts`
Funções auxiliares: `isValid()` 

```cpp
bool Post::isValid(int id){
    FILE* ptr = fopen(getPostFilePath(id).c_str(), "r");

    if(ptr == NULL){
        return false;
    }

    fclose(ptr);
    return true;
}
```

### Ususarios.cpp

A Classe usuários é uma das espinhas dorsais do projeto
Principais métodos: `publicar` `addPostToFeed` `seguir` `desseguir` `apagarUsuario` `loadFeed` `loadSelfPosts` `mkdir`
Getters: `getNome, getFollowers, getFollowing, getFeedFilePath, getFolderPath, getQuantidadeFeed, getUserFolderPath, getQuantidadePosts, getFollowersFilePath, getFollowingFilePath, getSeflPostsFilePath, getQuantidadeFeedFilePath, getQuantidadePostsFilePath`
Setters: `setQuantidadeFeed, setQuantidadePosts`
Métodos Auxiliares: `isValid`

Explicação sistematizada do método:
**Construtor e Destrutor**:

**Construtor**: Inicializa um novo objeto `Usuario` com o nome fornecido e cria os diretórios e arquivos associados, se eles não existirem. Ele também inicializa o gerenciador de notificações.

```cpp
Usuario::Usuario(std::string nome) : nome(nome), gerenciadorNotificacoes(GerenciadorNotificacoes(this)){
    mkDir(nome);
}

```

**Destrutor**: Limpa as notificações do gerenciador ao destruir o objeto.

```cpp
Usuario::~Usuario(){
    this->gerenciadorNotificacoes.clear();
}
```

1. **Criação e Validação de Diretórios e Arquivos**:
    - **Criação de Diretórios e Arquivos**: Verifica se o diretório do usuário já existe. Se não existir, cria o diretório do usuário, um diretório para o feed e vários arquivos de texto.
        
        ```cpp
        void Usuario::mkDir(std::string nome){
            if(Usuario::isValid(nome)) return;
        
            std::string mkdirCommand = "mkdir ";
            mkdirCommand += this->getUserFolderPath();
            system(mkdirCommand.c_str());
        
            mkdirCommand = "mkdir ";
            mkdirCommand += this->getFeedFolderPath();
            system(mkdirCommand.c_str());
        
            std::string cpCommand = "cp usuarios/fotoPadrao.png ";
            cpCommand += this->getFotoFilePath();
            system(cpCommand.c_str());
        
            FILE* ptr = NULL;
            ptr = fopen(this->getFollowersFilePath().c_str(), "w");
            fclose(ptr);
        
            ptr = fopen(this->getFollowingFilePath().c_str(), "w");
            fclose(ptr);
        
            ptr = fopen(this->getQuantidadePostsFilePath().c_str(), "w");
            fprintf(ptr, "0\\n");
            fclose(ptr);
        
            ptr = fopen(this->getQuantidadeFeedFilePath().c_str(), "w");
            fprintf(ptr, "0\\n");
            fclose(ptr);
        }
        
        ```
        
    - **Validação de Usuário**: Retorna verdadeiro se o arquivo "quantidadePosts.txt" do usuário existir, indicando que o usuário está registrado no sistema.
        
        ```cpp
        bool Usuario::isValid(std::string name){
            std::string path = "usuarios/cadastrados/";
            path += name;
            path += "/quantidadePosts.txt";
        
            FILE* ptr = fopen(path.c_str(), "r");
            if(ptr){
                fclose(ptr);
                return true;
            }
            return false;
        }
        
        ```
        
2. **Publicação de Post e Gerenciamento de Feed**:
    - **Publicação de Post**: Cria um novo post com um ID único, adiciona esse post ao feed do usuário e notifica todos os seguidores do novo post. Ele também atualiza a quantidade de posts do usuário.
        
        ```cpp
        void Usuario::publicar(std::string msg) {
            int id = Post::getTotalPosts() + 1;
            Post::newPost(id, msg, this->getNome());
            addPostToFeed(this->getNome(), id);
            this->setQuantidadePosts(this->getQuantidadePosts() + 1);
            gerenciadorNotificacoes.notificarTodos(id);
        }
        
        ```
        
    - **Adicionar Post ao Feed**: Adiciona um post ao arquivo de feed do usuário.
        
        ```cpp
        void Usuario::addPostToFeed(std::string user, int id){
            std::string feedFilePath = this->getFeedFilePath(user);
            FILE* feedFilePointer = fopen(feedFilePath.c_str(), "a");
            if(!feedFilePointer) feedFilePointer = fopen(feedFilePath.c_str(), "w");
            fprintf(feedFilePointer, "%d\\n", id);
            fclose(feedFilePointer);
        }
        
        ```
        
3. **Seguir e Deixar de Seguir Usuários**:
    - **Seguir Usuário**: Adiciona o usuário atual à lista de seguidores do `username` e adiciona o `username` à lista de pessoas que o usuário atual segue.
        
        ```cpp
        void Usuario::seguir(std::string username) {
            if(this->nome == username) return;
            if(!isFollowing(username)){
                Usuario usuario(username);
                std::string followersFilePath = usuario.getFollowersFilePath();
                FILE* followersFilePointer = fopen(followersFilePath.c_str(), "r");
                followersFilePointer = fopen(followersFilePath.c_str(), "a");
                fprintf(followersFilePointer, "%s\\n", nome.c_str());
                fclose(followersFilePointer);
        
                std::string followingFilePath = this->getFollowingFilePath();
                FILE* followingFilePointer = fopen(followingFilePath.c_str(), "a");
                fprintf(followingFilePointer, "%s\\n", username.c_str());
                fclose(followingFilePointer);
        
                std::string feedFilePath = this->getFeedFilePath(username);
                FILE* feedFilePointer = fopen(feedFilePath.c_str(), "w");
                fclose(feedFilePointer);
            }
        }
        ```
        
    - **Deixar de Seguir Usuário**: Remove o `usuario` da lista de pessoas que o usuário atual segue, remove o usuário atual da lista de seguidores do `usuario` e remove o `usuario` do feed do usuário atual.
        
        ```cpp
        void Usuario::desseguir(std::string usuario){
            auto following = this->getFollowing();
            FILE* followingFilePointer = fopen(this->getFollowingFilePath().c_str(), "w");
            for(auto u: following){
                if(u.getNome() == usuario) continue;
                fprintf(followingFilePointer, "%s\\n", u.getNome().c_str());
            }
            fclose(followingFilePointer);
        
            Usuario user2(usuario);
            FILE* followersFilePointer = fopen(user2.getFollowersFilePath().c_str(), "w");
            auto followers = user2.getFollowers();
            for(auto u: followers){
                if(u.getNome() == this->getNome()) continue;
                fprintf(followersFilePointer, "%s\\n", u.getNome().c_str());
            }
            fclose(followersFilePointer);
            user2.gerenciadorNotificacoes.remover(this);
        
            std::string rmFeedCommand = "rm ";
            rmFeedCommand += getFeedFilePath(usuario);
            system(rmFeedCommand.c_str());
        }
        
        ```
        
4. **Notificações e Carregamento de Dados**:
    - **Notificação de Novo Post**: Adiciona um post ao feed do usuário quando um autor que ele segue publica um novo post.
        
        ```cpp
        void Usuario::notificar(std::string autor, int postId) {
            addPostToFeed(autor, postId);
        }
        ```
        
    - **Carregar Gerenciador de Notificações**: Carrega o gerenciador de notificações com os seguidores do usuário.
        
        ```cpp
        void Usuario::loadGerenciadorNotificacoes(){
            gerenciadorNotificacoes.clear();
            for(auto x: getFollowers()){
                Usuario* u = new Usuario(x.getNome());
                this->gerenciadorNotificacoes.adicionar(u);
            }
        }
        ```
        
    - **Quantidade de Posts**: Métodos para obter e definir a quantidade de posts que o usuário fez.
        
        ```cpp
        int Usuario::getQuantidadePosts(){
            int quantidade;
            std::string quantidadePostsFilePath = this->getQuantidadePostsFilePath();
            FILE* quantidadePostsFilePointer = fopen(quantidadePostsFilePath.c_str(), "r");
            fscanf(quantidadePostsFilePointer, "%d", &quantidade);
            fclose(quantidadePostsFilePointer);
            return quantidade;
        }
        
        void Usuario::setQuantidadePosts(int quantidade){
            std::string quantidadePostsFilePath = this->getQuantidadePostsFilePath();
            FILE* quantidadePostsFilePointer = fopen(quantidadePostsFilePath.c_str(), "w");
            fprintf(quantidadePostsFilePointer, "%d\\n", quantidade);
            fclose(quantidadePostsFilePointer);
        }
        
        ```
        
    - **Carregar Feed**: Carrega os posts do feed e os posts publicados pelo próprio usuário.
        
        ```cpp
        std::vector<Post> Usuario::loadFeed(){
            std::vector<Post> posts = loadSelfPosts();
            for(auto x: this->getFollowing()){
                FILE* feedFilePointer = fopen(getFeedFilePath(x.getNome()).c_str(), "r");
                if(!feedFilePointer) continue;
                int id;
                while(fscanf(feedFilePointer, "%d", &id) != EOF) {
                    if(Post::isValid(id)){
                        Post p(id);
                        posts.push_back(p);
                    }
                }
                fclose(feedFilePointer);
            }
            sort(posts.begin(), posts.end(), [](Post p1, Post p2){ return p1.getID() > p2.getID(); });
            return posts;
        }
        
        std::vector<Post> Usuario::loadSelfPosts(){
            std::vector<Post> posts;
            posts.clear();
            std::string selfPostFilePath = this->getSelfPostsFilePath();
            FILE* selfPostFilePointer = fopen(selfPostFilePath.c_str(), "r");
            for(int i = 1; i <= getQuantidadePosts(); i++){
                int id;
                fscanf(selfPostFilePointer, "%d", &id);
                Post newPost(id);
                posts.push_back(newPost);
            }
            sort(posts.begin(), posts.end(), [](Post p1,
            ...
        ```
        
    

### loginSignals.cpp → Conexões com signals de autenticação

Vocabulário GTK de algumas funcionalidades utilizadas:

- GTK_ENTRY(...): Converte um objeto genérico para um GtkEntry.
- gtk_builder_get_object(builder, "name"): Obtém um objeto da interface a partir do arquivo de construção usando seu ID.
- gtk_entry_get_text(entry): Obtém o texto atual de um GtkEntry.
- GTK_STACK(...): Converte um objeto genérico para um GtkStack.
- gtk_stack_set_visible_child_name(stack, "login"): Define a tela visível no GtkStack pelo nome do filho.
- GTK_WIDGET(...): Converte um objeto genérico para um GtkWidget.
- gtk_widget_set_name(widget, "entryNormal"): Define o nome CSS de um widget para "entryNormal".
- gtk_entry_set_text(entry, ""): Define o texto de um GtkEntry.
- gtk_widget_set_name(widget, "entryWrong"): Define o nome CSS de um widget para "entryWrong".
- GtkBuilder: Objeto que carrega a interface a partir de um arquivo XML.
- GtkEntry: Widget de entrada de texto.
- GtkStack: Container que empilha widgets e permite a navegação entre eles.
- GtkWidget: Tipo genérico para todos os widgets GTK
1. Métodos para Obter Nome e Senha:
    - **getName**: Retorna a string digitada na Entry dedicada ao nome.
        
        ```cpp
        std::string Interface::getName(){
            GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "name"));
            return gtk_entry_get_text(entry);
        }
        
        ```
        
    - **getPassword**: Retorna a string digitada na Entry dedicada à senha.
        
        ```cpp
        std::string Interface::getPassword(){
            GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "password"));
            return gtk_entry_get_text(entry);
        }
        ```
        
2. **Carregar Tela de Login**:
    - **loadLoginScreen**: Carrega a tela de login, limpa as entradas de nome e senha se a opção "lembrar" não estiver ativada.
        
        ```cpp
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
        ```
        
3. **Ação de Login**:
    - **on_login_clicked**: Trata o evento de clique no botão de login. Verifica as credenciais e carrega a tela inicial se o login for bem-sucedido; caso contrário, destaca os campos de entrada com erro.
        
        ```cpp
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
        
        ```
        
4. **Ação de Cadastro**:
    - **on_cadastrar_clicked**: Trata o evento de clique no botão de cadastro. Tenta cadastrar um novo usuário e exibe um popup indicando o sucesso ou falha do cadastro.
        
        ```cpp
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
        
        ```
        
5. **Toggle da Checkbox "Lembrar de Mim"**:
    - **on_remember_toggled**: Alterna o estado da variável `lembrar` quando a checkbox é ativada.
        
        ```cpp
        void Interface::on_remember_toggled(){
            lembrar = !lembrar;
        }
        
        ```
        
6. **Alteração na Entry do Nome**:
    - **on_name_changed**: Reseta os campos de entrada de nome e senha para seu estado normal quando o nome é alterado.
        
        ```cpp
        void Interface::on_name_changed(){
            GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
            GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
            gtk_widget_set_name(name, "entryNormal");
            gtk_widget_set_name(password, "entryNormal");
        }
        
        ```
        
7. **Ativação das Entries**:
    - **on_name_activate**: Chama o método de login quando a tecla ENTER é pressionada na Entry de nome.
        
        ```cpp
        void Interface::on_name_activate(){
            on_login_clicked();
        }
        
        ```
        
    - **on_password_activate**: Chama o método de login quando a tecla ENTER é pressionada na Entry de senha.
        
        ```cpp
        void Interface::on_password_activate(){
            on_login_clicked();
        }
        
        ```
        
8. **Login e Cadastro**:
    - **login**: Verifica se o nome de usuário e a senha correspondem a um registro existente no sistema.
        
        ```cpp
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
        
        ```
        
    - **cadastrar**: Tenta cadastrar um novo usuário se ele não existir, verificando se o nome de usuário é válido e se a senha foi fornecida.
        
        ```cpp
        bool Interface::cadastrar(std::string userName, std::string password) {
            if (Usuario::isValid(userName)) {
                return false;
            }
            if(userName.find(" ") != userName.npos) return false;
            if(!userName.size() || !password.size()) return false;
        
            FILE* ptr = fopen(LOGIN_DATA_FILE_PATH, "a");
            if(!ptr) return false;
        
            fprintf(ptr, "%s,%s\\n", userName.c_str(), password.c_str());
            fclose(ptr);
        
            this->loadLoginScreen();
            return true;
        }
        
        ```
        

## Usuarios

Após a criação de um usuário essa pasta é automaticamente criada:
Estrutura: 

**cadastrados →** Simulação de um banco de dados básico com os dados dos usuários
**posts →** Contém todos os posts feitos.
login_data.txt → log de informações sensíveis dos usuários
totalPosts.txt → faz a contagem da quantidade de postagens feita.
fotoPadrao.png → Foto Padrão de um usuário ao ser cadastrado

---
