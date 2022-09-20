#ifndef __MSG_HPP__
#define __MSG_HPP__

#include "main.hpp"

class msg {
    public:
        std::string data;
        msg(std::string _data) {
            data = _data;
        }
        void send(void *socket); // TODO: this function should translate std::string to char*
};

namespace server {
    // TODO: same as above, translate to char*
    std::string recv(void *socket);
}

#endif
