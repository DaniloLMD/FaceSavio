#ifndef __INOTIFICAVEL_HPP__
#define __INOTIFICAVEL_HPP__

//classe abstrata
class INotificavel{
    public:
        virtual void notificar(int postId) = 0;
};

#endif