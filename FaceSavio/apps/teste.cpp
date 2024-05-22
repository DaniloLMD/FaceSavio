#include <iostream>
#include "../include/Usuario.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Usuario* danilo = new Usuario("Danilo");
    Usuario* caio = new Usuario("Caio");

    caio->seguir("Danilo");


    danilo->publicar("estou facesaviando");

    danilo->publicar("tiago pio");

    cout << "mostrando os posts do caio!\n";
    caio->showPosts();

    caio->publicar("acabei de ver todos os meus posts.");
    danilo->seguir("Caio");
    danilo->showPosts();
    
    return 0;
}