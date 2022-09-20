#ifndef __MSG_HPP__
#define __MSG_HPP__

#include "main.hpp"

#define BERR_ACCEPT_SOCKET -3
#define BERR_CREATE_SOCKET -2
#define BERR_BIND_SOCKET -1
#define BNET_SUCCESS 0

// C++ wrapper for C sockets
// (serverside)
class b_ssocket {
    public:
        std::string tag; // nametag for our interaction
        int c_sock, d_sock;
        socklen_t s_len;
        struct sockaddr_in s_sock, t_sock;
        b_socket(std::string _tag) {
            // set some boilerplate bullshit
            tag = _tag;
            s_sock.sin_family = AF_INET;
            s_sock.sin_port = htons(BE_PORT);
            s_sock.sin_addr.s_addr = inet_addr(BE_IP);
        }
};

// (clientside)
class b_csocket {
    public:
        std::string tag;
        int c_sock;
        struct sockaddr_in s_sock;
        b_socket(std::string _tag) {
            tag = _tag;
            s_sock.sin_family = AF_INET;
            s_sock.sin_port = htons(BE_PORT);
            s_sock.sin_addr.s_addr = inet_addr(BE_IP);
        }
};
