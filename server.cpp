#include "main.hpp"
#include "server.hpp"
// use cmd <<serverpile>> to compile
// also TODO: create makefile I guess

namespace b_net {
    // host a gameserver instance
    uint8_t cunny_t::host(server_socket s) {
        bool quit = false;
        // boilerplate... TODO: the fuck?
        bzero((char*) &s.s_sock, sizeof(s.s_sock)); 
        s.s_sock.sin_family = AF_INET;
        s.s_sock.sin_port = htons(BE_PORT);
        s.s_sock.sin_addr.s_addr = inet_addr(BE_IP);
        // create and bind server socket
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) return BERR_CREATE_SOCKET; // ERROR
        if (bind(s.c_sock, (struct sockaddr*)&s.s_sock, sizeof(s.s_sock)) < 0) return BERR_BIND_SOCKET; 
        listen(s.c_sock, 5);
        s.s_len = sizeof(s.t_sock);
        while (quit == false) {
            s.d_sock = accept(s.c_sock, (struct sockaddr*) &s.t_sock, &s.s_len);
            if (s.d_sock < 0) return BERR_ACCEPT_SOCKET;
            // -- we actually do stuff here
            // TODO: make this a while loop, handle stuff properly
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
            std::cout << "Error reading data";
        }
        msg.data = std::to_string(data);
        msg.id = 99999; // FIXME: use cunny's id_count and stuff
        data = write(d_sock, "ACK", 3);
        if (data < 0) {
            std::cout << "Error writing ACK to socket";
        }
        return msg;
    }

    // handles the sent/received data itself
    // FIXME: do everything
    void cunny_t::handle_data(msg_t msg) {
        if (msg.data == "BE_TEST") std::cout << "BE_TEST CALLED";
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
