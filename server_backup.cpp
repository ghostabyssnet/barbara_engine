#include "main.hpp"
#include "server.hpp"
// use cmd <<serverpile>> to compile
// also TODO: create makefile I guess

namespace b_net {
    // host a gameserver instance
    uint8_t cunny_t::host(server_socket s) {
        bool quit = false; 
        /* resets our socket to its initial values
         * (actually it nullifies everything in it)*/
        bzero((char*) &s.s_sock, sizeof(s.s_sock)); 
        s.s_sock.sin_family = AF_INET;
        s.s_sock.sin_port = htons(BE_PORT);
        s.s_sock.sin_addr.s_addr = inet_addr(BE_IP);
        // create and bind server socket
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) return BERR_CREATE_SOCKET; // ERROR
        b_util::debug("Socket created successfully\n");
        if (bind(s.c_sock, (struct sockaddr*)&s.s_sock, sizeof(s.s_sock)) < 0) return BERR_BIND_SOCKET; 
        b_util::debug("Socket binding complete\n");
        listen(s.c_sock, 5);
        b_util::debug("listen() called...\n");
        s.s_len = sizeof(s.t_sock);
        while (quit == false) {
            s.d_sock = accept(s.c_sock, (struct sockaddr*) &s.t_sock, &s.s_len);
            b_util::debug("accept() called\n");
            // FIXME: this thing below is EXTREMELY cringe
            // our server shouldn't stop EVER. and it specially
            // shouldn't stop itself...! instead of returning,
            // find some solution (or recreate the server instantly
            // upon return... but it would still suck)
            if (s.d_sock < 0) return BERR_ACCEPT_SOCKET;
            // -- we actually do stuff here
            // TODO: make this a while loop (done?), handle stuff properly
            handle_data(get_data(s.d_sock));
            // END
            close(s.d_sock);
        }
    close(s.c_sock);
    }
    
    // handles server-client interactions
    // returns false if something went wrong and we should quit
    // its design uses b_messages to handle stuff
    msg_t cunny_t::get_data(int d_sock) {
        int data;
        char buffer[NET_BUFFER_SIZE];
        msg_t msg(0, "ERROR"); // placeholder message
        bzero(buffer, NET_BUFFER_SIZE);
        data = read(d_sock, buffer, (NET_BUFFER_SIZE - 1));
        if (data < 0) {
            std::cout << "Error reading data\n";
        }
        else b_util::debug("New data: " + std::string(buffer) + "\n");
        msg.data = std::string(buffer);
        msg.id = 99999; // FIXME: use cunny's id_count and stuff
        data = write(d_sock, "ACK", 3);
        if (data < 0) {
            std::cout << "Error writing ACK to socket\n";
        }
        else b_util::debug("Just wrote ACK to socket\n");
        return msg;
    }

    // handles the sent/received data itself
    // FIXME: do everything
    void cunny_t::handle_data(msg_t msg) {
        std::string data = msg.data;
        data.pop_back(); // remove last character
        if (data.compare(std::string("BE_TEST")) == 0) std::cout << "BE_TEST CALLED\n";
    }
}

int main() {
    std::vector<std::thread> threads;
    b_net::server server;
    // FIXME: placeholder, should be replaced with
    // proper checks and stuff
    bool placeholder = false; // check if a new thread should
                              // be created
    std::cout << "Running main server...";
    // MAIN THREAD - check for connections
    // TODO: main thread
    placeholder = true;
    // THREAD HANDLING - create/drop threads as connections come
    // and go
    // TODO: same as everything else. clean it up, spit it out
    if (placeholder) server.cunny.host(server.cunny.serv);
    return 0;
}
