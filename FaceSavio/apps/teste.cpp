#include <iostream>
#include "../include/Usuario.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Usuario* danilo = new Usuario("Danilo");
    Usuario* caio = new Usuario("Caio");

    caio->seguir("Danilo");


    danilo->publicar("estou facesaviando IMPAR");
    danilo->publicar("tiago pio PAR");
    cout << "\n";


    cout << "Mostrando os posts para caio!!\n";

    caio->showPosts();

    caio->publicar("acabei de ver todos os meus posts.");
    cout << "\n";   
    
    danilo->seguir("Caio");
    cout << "Mostrando os posts para Danilo!\n";
    danilo->showPosts();
    
    return 0;
}