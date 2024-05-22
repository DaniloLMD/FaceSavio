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
