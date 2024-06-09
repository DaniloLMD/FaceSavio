#include "../include/Interface.hpp"

int main(int argc, char* argv[]){
    Interface* interface = new Interface();
    interface->display();

    std::cout << "retornando\n";
    return 0;
}