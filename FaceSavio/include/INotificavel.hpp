#ifndef __INOTIFICAVEL_HPP__
#define __INOTIFICAVEL_HPP__

#include <iostream>

class Usuario; //declaração antecipada

class INotificavel{
    public:
        virtual void notificar(int postId) = 0;
};

#endif