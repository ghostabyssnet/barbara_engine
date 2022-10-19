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
            // FIXME: unused for now
            std::vector<std::unique_ptr<std::thread>> conn_list;
            server_socket serv;
            game_server gs;
            short host(server_socket s);
            msg_t get_data(server_socket s);
            
            void new_conn(server_socket s);
            
            // ideally, this should use uint8_t to return
            // multiple error types
            bool handle_data(msg_t msg);
            
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
