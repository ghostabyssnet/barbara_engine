#ifndef __MSG_HPP__
#define __MSG_HPP__

#include "main.hpp"

#define BERR_ACCEPT_SOCKET -3
#define BERR_CREATE_SOCKET -2
#define BERR_BIND_SOCKET -1
#define BNET_SUCCESS 0

namespace server {
    void debug(std::string f) {if(BE_DEBUG) cout << f;}
}

// C++ wrapper for C sockets
namespace b_net {
    // (serverside)
    class server_socket {
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
    class client_socket {
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

    // messages are used to transfer data between sockets,
    // and also used for remote function execution
    // they're composed of an ID-entifier and its contents
    class msg {
        public:
            uint64_t id;
            std::string data;
            msg(uint64_t _id, std::string _data) {
                id = _id;
                data = _data;
            }
    };
}

// defines functions to handle sent/received messages,
// increase their counter, etc
namespace cunny {
    // cunny is our message broker, it handles how many
    // messages were sent and received, their ID counter,
    // etc -- whatever is cute and funny to do
    class server {
        public:
            uint64_t id_count; // msg count (next ID to be used)
            b_net::server_socket s;
            server(b_net::server_socket _s) {
                id_clock = 0;
                s = _s;
            }
            
            // fired when the server sends a message
            Event on_message_sent() {
                id_count++;
            }
            
            // same when it receives anything
            Event on_message_received() {
                // TODO: this
            }
            
            uint8_t host_instance();
    };
    // msg CRUD
    b_net::msg make_msg(std::string data);

}
