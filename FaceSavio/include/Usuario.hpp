#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <iostream>
#include "../include/GerenciadorNotificacoes.hpp"
#include "../include/INotificavel.hpp"

class Usuario : public INotificavel {
    public:
        //construtor
        Usuario(std::string nome);

        std::string getNome();

        void publicar(std::string msg);

        void adicionarAmigo(Usuario* usuario);

        void notificar(std::string msg, Usuario* autor) override;


    private:
        std::string nome;
        GerenciadorNotificacoes* gerenciadorNotificacoes;
};


#endif