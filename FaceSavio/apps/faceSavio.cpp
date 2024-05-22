#include <gtk/gtk.h>
#include <iostream>
#include "../include/Interface.hpp"
#include "../include/Usuario.hpp"
#include "../include/paths.hpp"

using namespace std;

int main(int argc, char* argv[]){

    interface = new Interface(GLADE_FILE_PATH);

    interface->activateCSS(CSS_FILE_PATH);
        
    interface->display();

    return 0;
}