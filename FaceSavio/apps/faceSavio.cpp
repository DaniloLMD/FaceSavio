#include <gtk/gtk.h>
#include <iostream>
#include "../include/Interface.hpp"
#include "../include/Usuario.hpp"
#include "../include/paths.hpp"

using namespace std;

int main(int argc, char* argv[]){

    system("./rm");

    Usuario* danilo = new Usuario("Danilo");
    Usuario* caio = new Usuario("Caio");
    Usuario* tiago = new Usuario("Tiago");

    danilo->seguir(caio->getNome());
    danilo->seguir(tiago->getNome());
    caio->seguir(danilo->getNome());

    caio->publicar("caio farias.");
    tiago->publicar("pio.");
    danilo->publicar("LMD.");

    Interface* interface = new Interface(GLADE_FILE_PATH);

    interface->activateCSS(CSS_FILE_PATH);
        
    interface->display();

    return 0;
}