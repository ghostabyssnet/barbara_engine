#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "msg.hpp"
#include "sql.hpp"

namespace b_net { 
    
    class match {
        public:
            int placeholder;
    };

    class game_server {
        public:
            std::vector<match> matches;
    };

    // cunny is our message broker, it handles how many
    // messages were sent and received, their ID counter,
    // etc -- whatever is cute and funny to do
    class cunny_t {
        public:
            uint64_t id_count = 1; // msg count (next ID to be used)
            server_socket serv;
            game_server gs;
            uint8_t host(server_socket s);
            msg_t get_data(int d_sock);
            void handle_data(msg_t msg); // FIXME: should be uint8_t for errors (but I didn't think of any yet)
            // fired when a player connects to the server
            Event on_connect() {
                // TODO: this
            }

            // fired when a player disconnects from the server
            Event on_disconnect() {
                // TODO: this
            }

            // fired when the server sends a message
            Event on_message_sent() {
                id_count++;
                // TODO: expand this maybe? idk what to write
            }
            
            // same when it receives anything
            Event on_message_received() {
                // TODO: this
            } 
            
    };
    
    class database_t {
        // TODO: this
    };

    class server {
        public:
            cunny_t cunny;
            database_t db;            
    };
}
#endif
