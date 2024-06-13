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
            delete *(notificaveis.begin() + i);
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
