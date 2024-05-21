#include <iostream>
#include "../include/Usuario.hpp"

using namespace std;

int main(int argc, char* argv[]){

    Usuario* danilo = new Usuario("Danilo");
    Usuario* caio = new Usuario("Caio");
    Usuario* tiago = new Usuario("Tiago");

    danilo->adicionarAmigo(caio);
    danilo->adicionarAmigo(tiago);

    danilo->publicar("estou facesaviando");

    return 0;
}