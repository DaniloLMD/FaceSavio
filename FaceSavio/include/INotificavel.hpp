#ifndef __INOTIFICAVEL_HPP__
#define __INOTIFICAVEL_HPP__

#include <iostream>

class Usuario; //declaração antecipada

class INotificavel{
    public:
        virtual void notificar(std::string msg, std::string autor){};
        virtual ~INotificavel() {}

    private:
};

#endif