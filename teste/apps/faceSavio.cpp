#include "../include/Interface.hpp"
#include "../include/paths.hpp"

int main(int argc, char* argv[]){
    Interface* interface = new Interface(GLADE_FILE_PATH);
    interface->display();

    return 0;
}