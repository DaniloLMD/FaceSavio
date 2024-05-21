#include <iostream>
#include "../include/Usuario.hpp"
#include "../include/GerenciadorNotificacoes.hpp"


// Construtor
Usuario::Usuario(std::string nome) : nome(nome) {
    gerenciadorNotificacoes = new GerenciadorNotificacoes(this);
}

std::string Usuario::getNome() {
    return nome;
}

void Usuario::publicar(std::string msg) {
    std::cout << "Eu " << nome << ", publiquei a mensagem '" << msg << "'.\n";
    gerenciadorNotificacoes->notificarTodos(msg);
}

void Usuario::adicionarAmigo(Usuario* usuario) {
    gerenciadorNotificacoes->adicionar(usuario);
}

void Usuario::notificar(std::string msg, Usuario* autor) {
    std::cout << "Sou o usuario " << nome << " e o usuario " << autor->getNome() << " publicou a mensagem: '" << msg << "'.\n";
}
