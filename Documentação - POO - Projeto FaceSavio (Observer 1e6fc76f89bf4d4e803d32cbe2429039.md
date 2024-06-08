# Documentação - POO - Projeto FaceSavio (Observer)

Tópicos

## Autores

- *MARCELLO RONALD JOSÉ DA SILVA - 202302618*
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

## Diagramas

### Diagrama de Classes principal

[Diagrama do projeto.pdf](Documentac%CC%A7a%CC%83o%20-%20POO%20-%20Projeto%20FaceSavio%20(Observer%201e6fc76f89bf4d4e803d32cbe2429039/Diagrama_do_projeto.pdf)

Link do UML fonte: https://lucid.app/lucidchart/6ca70b07-e4e2-4a8a-ac44-8fed35885b5c/edit?viewport_loc=-6662%2C-4864%2C9985%2C5068%2C0_0&invitationId=inv_af87c4f1-14f2-41a2-a7f4-b35c4868136d

---

## Slides de apresentação

(Inserir arquivo fonte aqui ou fotos do mesmo ou um link do canvas exemplo de template:. [https://www.canva.com/design/DAGESsJGbjI/d0Gfdf7JDLIUZqKslzRErw/edit](https://www.canva.com/design/DAGESsJGbjI/d0Gfdf7JDLIUZqKslzRErw/edit))

---

## Regras de negócio.

- 1: O Programa deve ser executado em um Linux SO

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

![Untitled](Documentac%CC%A7a%CC%83o%20-%20POO%20-%20Projeto%20FaceSavio%20(Observer%201e6fc76f89bf4d4e803d32cbe2429039/Untitled.png)

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
- **LoginSignals.hpp**
    
    ```
    #ifndef __LOGIN_SIGNALS_HPP__
    #define __LOGIN_SIGNALS_HPP__
    
    #include "Interface.hpp"
    
    enum opcoes{
        LOGIN = 1,
        CADASTRO
    };
    
    #endif
    ```
    
    Inclui o cabeçalho da Interface e estabelce um membro do tipo enum que fornece as opções Login = 1 e Cadastro = 2;
    
- paths.hpp
    
    ```cpp
    #ifndef __PATHS_HPP__
    #define __PATHS_HPP__
    
    const char* GLADE_FILE_PATH = "glade/faceSavio.glade";
    const char* CSS_FILE_PATH = "glade/faceSavio.css";
    const char* LOGIN_DATA_FILE_PATH = "usuarios/login_data.txt";
    
    #endif
    ```
    
    Cabeçalho que define caminhos padrões na aplicação
    
- Post.hpp
    
    ```cpp
    #include <gtk/gtk.h>
    #include <string>
    
    class Post{
        public:
    
            Post(int id, std::string texto, std::string username);
    
            int getID() { return id; }
            std::string getTexto() { return texto; }
            std::string getUsername() { return username; }
    
        private:
            int id;
            std::string texto;
            std::string username;
    };
    
    GtkWidget* newScaledImage(const gchar *filePath, gint width, gint height);
    void setScaledImage(GtkImage* image, const gchar *filePath, gint width, gint height);
    
    #endif
    ```
    
    O cabeçalho Post inclui as libs: gtk e uma de string.
    
    Construtor: `Post(int id, std::string texto, std::string username);`
    Na definição de métodos/atributos públicos têm-se: 
    Get: `int getID() { return id; }` → retorna o ID do post
    
    std::string `getTexto() { return texto; }` → retorna o texto do post
    std::string `getUsername() { return username; }` → retorna o nome do usuário que fez o post.
    
    GtkWidget* newScaledImage(const gchar *filePath, gint width, gint height); → Esta função cria um novo widget de imagem GTK com a imagem especificada no caminho do arquivo e as dimensões fornecidas
    
    void setScaledImage(GtkImage* image, const gchar *filePath, gint width, gint height); → Esta função atualiza um widget de imagem GTK existente com uma nova imagem especificada no caminho do arquivo e as dimensões fornecidas.
    
- Usuario.hpp

```
#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <vector>

#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/INotificavel.hpp"
#include "Post.hpp"

class Usuario : public INotificavel {
    public:
    
        Usuario(std::string nome);

        static void mkDir(std::string name);
        static bool isValid(std::string name);

        std::string getNome();

        void publicar(std::string msg);

        void seguir(std::string usuario);
        void desseguir(std::string usuario);

        void notificar(std::string msg, std::string autor) override;

        bool isFollowing(std::string user);

        std::vector<Post*> loadAllPosts();
        std::vector<Post*> loadSelfPosts();
        std::vector<Usuario*> getFollowing();
        std::vector<Usuario*> getFollowers();

        std::string getFotoFilePath();

    private:
        std::string nome;
        // GerenciadorNotificacoes* gerenciadorNotificacoes;

        //funcoes de acesso aos arquivos
        int getTotalPosts();
        void setTotalPosts(int quantidade);
        int getQuantidadePosts();
        void setQuantidadePosts(int quantidade);  

        std::vector<Post*> posts;

        std::string getUserFolderPath();
        std::string getTotalPostsFilePath();
        std::string getFollowersFilePath();
        std::string getFollowingFilePath();
        std::string getPostsFolderPath();   
        std::string getPostFilePath(int post); 
        std::string getQuantidadePostsFilePath();
};
#endif
```

Construtor: Usuário(std::string nome); 

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
- `isfollowin` : Verifica se o usuário está seguindo outro usuário especificado.

Métodos de carregamento de dados:

- `loadAllPosts`: Carrega todos os posts feitos por este usuário e pelos usuários que ele segue.
- `loadSelfPosts`: Carrega apenas os posts feitos por este usuário.
- `getFollowing`: Retorna uma lista dos usuários que este usuário está seguindo.
- `getFollowers`: Retorna uma lista dos usuários que estão seguindo este usuário.

## SRC

### GerenciadorNotificacoes.cpp

```cpp
#include <iostream>
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/Usuario.hpp"

// Construtor
GerenciadorNotificacoes::GerenciadorNotificacoes(Usuario* usuario) : usuario(usuario) {}

void GerenciadorNotificacoes::adicionar(Usuario* notificavel) {
    notificaveis.push_back(notificavel);
}

void GerenciadorNotificacoes::notificarTodos(std::string msg) {
    for (Usuario* notificavel : notificaveis) {
        notificavel->notificar(msg, usuario->getNome());
    }
}
```

inclui três bibliotecas sendo uma a de entrada e saída padrão do c++, e outras duas que são: GerenciadorNotificacoes.hpp e Usuario.hpp
o código estabelece um Construtor → `GerenciadorNotificacoes::GerenciadorNotificacoes(Usuario* usuario) : usuario(usuario) {}` 
O primeiro “usuário” se refere ao atributo e o segundo se refere ao parâmetro do construtor.

**Métodos**

- `adicionar(Usuario* notificavel)` : esse método não retorna nenhum valor por ser do tipo void, recebe um ponteiro para um objeto Usuario definido como notificavel
notificaveis é um vetor de ponteiros para o objeto `Usuario` o método push_back(notificavel) adiciona o elemento passado como parâmetro no final desse vetor notificaveis.
- `notificarTodos(std::string msg)` : recebe uma dada mensagem do tipo string como parãmetro, não retorna nenhum valor pois é do tipo void

```cpp
for (Usuario* notificavel : notificaveis) {
        notificavel->notificar(msg, usuario->getNome());
    }
```

Esse for percorre cada elemento do vetor notificaveis onde notificavel é um ponteiro para um objeto `Usuario`, para cada objeto no vetor notificaveis o método notificar é chamado, passando-se a mensagem e o nome do usuario em questão, ao iterar sobre todo o vetor, todos os usuário são notificados.

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
        
9. **Reseta a Interface**:
    
    ```cpp
    this->reset();
    ```
    
    - Chama o método `reset` para possivelmente atualizar ou redesenhar a interface.

### Testes / Validações

Trechos que demonstrem testes ou validações específicas.

### Ex:. Teste #1

```java
...
```

## Exemplos de Uso:.

Imagens que deem exemplo da execução de execução.

```java
...
```

---

## Conclusão