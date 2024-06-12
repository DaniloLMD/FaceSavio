#include "../include/Interface.hpp"
#include <pthread.h>

void func(){
    Interface* interface = new Interface();
    interface->display();
}

int main(int argc, char* argv[]){
    Interface i;
    i.display();

    return 0;
}