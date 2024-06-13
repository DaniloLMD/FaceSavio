#ifndef __INOTIFICAVEL_HPP__
#define __INOTIFICAVEL_HPP__

class INotificavel{
    public:
        virtual void notificar(std::string autor, int postId) = 0;
};

#endif