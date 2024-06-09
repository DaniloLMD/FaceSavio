#include <iostream>
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/Usuario.hpp"

// Construtor
GerenciadorNotificacoes::GerenciadorNotificacoes(Usuario* usuario) : usuario(usuario) {}

void GerenciadorNotificacoes::adicionar(Usuario* notificavel) {
    notificaveis.push_back(notificavel);
}

void GerenciadorNotificacoes::remover(Usuario* notificavel){
    for(int i = 0; i < notificaveis.size(); i++){
        if(notificaveis[i]->getNome() == notificavel->getNome()){
            notificaveis.erase(notificaveis.begin() + i);
            break;
        }
    }
}

void GerenciadorNotificacoes::notificarTodos(int postId) {
    for (Usuario* notificavel : notificaveis) {
        notificavel->notificar(postId);
    }
}
