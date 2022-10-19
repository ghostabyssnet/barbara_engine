#ifndef __PROTO_HPP__
#define __PROTO_HPP__

#include "main.hpp"
#include "msg.hpp"

/* =========================================
 * FIXME: CHANGE THESE FOR THE ACTUAL CLIENT
 * 1) socket errors should return error messages
 * instead of sending only debug messages
 * (send debug messages on success only)
 */

namespace b_net {
    class client {
        public:
            bool should_quit = false;
            client_socket c;
            
            // creates a new connection to the server
            short new_conn(client_socket s);
            
            // creates a data output loop to the server
            void net_send(client_socket c);

            // creates an input loop that gets data from the server
            void net_recv(client_socket c);

    };
}

#endif
