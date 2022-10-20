#ifndef __PROTO_HPP__
#define __PROTO_HPP__

#include "main.hpp"
#include "msg.hpp"

#define CMD_QUIT 0
#define HAND_PAPER 1
#define HAND_SCISSORS 2
#define HAND_ROCK 3

namespace b_net {
    class client {
        public:
            bool should_quit = false;
            client_socket c;
            
            // -- GAME --
            
            void handle_data(std::string data);

            // -- NET --

            // creates a new connection to the server
            short new_conn(client_socket s);
            
            // creates a data output loop to the server
            void net_send(client_socket c);

            // creates an input loop that gets data from the server
            void net_recv(client_socket c);
    };
}

#endif
