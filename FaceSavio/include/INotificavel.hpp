#ifndef __INOTIFICAVEL_HPP__
#define __INOTIFICAVEL_HPP__

#include <iostream>
// #include "../include/Usuario.hpp"    

class Usuario; //declaração antecipada

class INotificavel{
    public:
        virtual void notificar(std::string msg, Usuario* autor) = 0;
        virtual ~INotificavel() {}

    private:
};

#endif