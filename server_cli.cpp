#include "main.hpp"
#include "server_cli.hpp"

// use cmd <<serverpile>> to compile
// also TODO: create makefile I guess

// known bug: server will actually return 0 and quit on n-1 connections
// this WOULD suck under normal circumstances, but we've not been
// handling connection errors and stuff properly for a while now,
// so it's not a good time to be hypocritical
#define MAX_CONN 3

namespace b_net {
    
    // handles server-client interactions
    // returns false if something went wrong and we should quit
    // its design uses b_messages to handle stuff
    msg_t cunny_t::get_data(server_socket s) {
        int data;
        char buffer[NET_BUFFER_SIZE];
        msg_t msg(0, "ERROR"); // placeholder message
        bzero(buffer, NET_BUFFER_SIZE);
        b_util::debug("_a\n");
        data = read(s.d_sock, buffer, (NET_BUFFER_SIZE - 1));
        b_util::debug("_b\n");
        if (data > 0) msg.data = std::string(buffer);
        b_util::debug("_c\n");
        msg.id = 99999; // FIXME: use cunny's id_count and stuff
        data = write(s.d_sock, "ACK", 3);
        b_util::debug("_d\n");
        return msg;
    }
    
    // a c++ wrapper for socket writing/sending
    void cunny_t::send_data(server_socket s, std::string data) {
        write(s.d_sock, data.c_str(), strlen(data.c_str()));
    }

    // handles the sent/received data itself 
    bool cunny_t::handle_data(msg_t msg, player p) {
        std::string data = msg.data;
        b_util::debug("_one\n");
        // stops our stuff from running when something goes wrong
        if (data.compare(std::string("ERROR")) == 0) return false; 
        b_util::debug("_two\n");
        // FIXME: fix the fact that a client quitting crashes the server
        
        // handle codes
        if (data.find(std::string("BE_MOVE_")) != std::string::npos) on_player_move(data, p);
        else chat(data, p);
        return true;
    }

    // handles a new connection and maintains dataflow
    void cunny_t::new_conn(server_socket s, player p) {
        bool should_quit = false;
        if (p.id == 1) send_data(s, "Espere pelo outro jogador.\n");
        //else send_data(s, "Iniciando partida...\n");
        while (!should_quit) {
            b_util::debug("_conn\n");
            // quit when something goes wrong
            // not ideal but fixing it goes 
            // beyond the scope of this project
            b_util::debug("_lambda\n");
            if (!handle_data(get_data(s), p)) should_quit = true;
            b_util::debug("_radius\n");
        }
    }

    // host a gameserver instance
    short cunny_t::host(server_socket s) {
        bool quit = false; 
        /* resets our socket to its initial values
         * (actually it nullifies everything in it)*/
        bzero((char*) &s.s_sock, sizeof(s.s_sock)); 
        s.s_sock.sin_family = AF_INET;
        s.s_sock.sin_port = htons(BE_PORT);
        s.s_sock.sin_addr.s_addr = INADDR_ANY;
        // create and bind server socket
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) return BERR_CREATE_SOCKET; // ERROR
        b_util::debug("Socket created successfully\n");
        if (bind(s.c_sock, (struct sockaddr*)&s.s_sock, sizeof(s.s_sock)) < 0) return BERR_BIND_SOCKET; 
        b_util::debug("Socket binding complete\n");
        listen(s.c_sock, 5);
        b_util::debug("listen() called...\n");
        s.s_len = sizeof(s.t_sock);
        // prepare the server for a new match
        prepare();
        for (int x = 0; x < MAX_CONN; x++) {
            s.d_sock = accept(s.c_sock, (struct sockaddr*) &s.t_sock, &s.s_len);
            b_util::debug("accept() called\n");
            if (s.d_sock < 0) b_util::debug("Error on accept(): " + std::to_string(s.d_sock));
            // FIXME: this thing below is EXTREMELY cringe
            // our server shouldn't stop EVER. and it specially
            // shouldn't stop itself...! instead of returning,
            // find some solution (or recreate the server instantly
            // upon return... but it would still suck)
            if (s.d_sock < 0) return BERR_ACCEPT_SOCKET;
            // create a new player with id (current_players + 1)
            player _p((players.size() + 1)); 
            // create a new thread and add our new connection to it
            std::thread _conn(&cunny_t::new_conn, this, s, _p);
            players.emplace_back(_p);
            conn_list.emplace_back(s);
            _conn.detach();
            on_connect();
            // cleanup
            //if (players.size() >= 2) close(s.d_sock);
        }
    close(s.c_sock);
    return 0;
    }
}

int main() {
    b_net::server server;
    short z = server.cunny.host(server.cunny.serv);
    std::cout << "Exiting: " << z << std::endl;
    return 0;
}
