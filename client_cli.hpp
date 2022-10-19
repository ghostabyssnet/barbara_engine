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
            bool my_turn = false;
            client_socket c;
            
            // -- GAME --
            
            // attempts to move hand
            // fails if it's not our turn
            bool new_attempt(uint8_t hand) {
                if (!my_turn) return false;
                return true;
            }
            
            // probably should be a bool for error handling
            // but it shouldn't matter in a small project
            void send_attempt(uint8_t hand);

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
