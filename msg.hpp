#ifndef __MSG_HPP__
#define __MSG_HPP__

#include "main.hpp"
#include "database.hpp"
#define BERR_CONN_SOCKET -16
#define BERR_ACCEPT_SOCKET -3
#define BERR_CREATE_SOCKET -2
#define BERR_BIND_SOCKET -1
#define BNET_SUCCESS 0

// C++ wrapper for C sockets
namespace b_net {
    // (serverside)
    class server_socket {
        public:
            std::string tag; // nametag for our interaction
            int c_sock, d_sock;
            socklen_t s_len;
            struct sockaddr_in s_sock, t_sock;
    };

    // (clientside)
    class client_socket {
        public:
            std::string tag;
            int c_sock;
            struct sockaddr_in s_sock;
            struct hostent *server;
    };

    // messages are used to transfer data between sockets,
    // and also used for remote function execution
    // they're composed of an ID-entifier and its contents
    class msg_t {
        public:
            uint64_t id;
            std::string data;
            msg_t(uint64_t _id, std::string _data) {
                id = _id;
                data = _data;
            }
    };
}
#endif
