#include "main.hpp"
#include "msg.hpp"

// use cmd <<serverpile>> to compile
// also TODO: create makefile I guess

// TODO: create event-to-string API here

namespace server {
    // host a gameserver instance
    int host_instance(b_ssocket s) {
        bool quit = false;
        // boilerplate... TODO: the fuck?
        bzero((char*) &s.s_sock, sizeof(s.s_sock));
        // create and bind server socket
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) return BERR_CREATE_SOCKET; // ERROR
        if (bind(s.c_sock, (struct sockaddr*)&s.s_sock), sizeof(s.s_sock)) < 0 return BERR_BIND_SOCKET; 
        listen(s.c_sock, 5);
        s.s_len = sizeof(s.t_sock);
        while (quit == false) {
            s.d_sock = accept(s.c_sock, (struct sockaddr*) &s.t_sock, &s.s_len);
            if (s.d_sock < 0) return BERR_ACCEPT_SOCKET;
            // -- we actually do stuff here
            quit == handle_data(s.d_sock);
            // END
            close(s.d_sock);
        }
    close(s.c_sock);
    }
    
    // handles server-client interactions
    // returns false if something went wrong and we should quit
    // its design uses b_messages to handle stuff
    bool handle_data(int d_sock) {
        int data;
        string s_data;
        char buffer[NET_BUFFER_SIZE];
        bzero(buffer, NET_BUFFER_SIZE);
        data = read(d_sock, buffer, (NET_BUFFER_SIZE - 1));
        if (n < 0) {
            cout << "Error reading data";
            return true;
        }
        s_data = std::to_string(data);
        process_data(s_data);
        data = write(d_sock, "ACK", 3);
        if (n < 0) {
            cout << "Error writing to socket";
            return false;
        }
        return true;
    }

    // handles the sent/received data itself
    void process_data(std::string data) {
        // TODO: process stuff
        // if/else galore
        
    }
}

int main() {
    // setup server socket
    b_ssocket s("main");
    std::vector<std::thread> threads;
    server::host(s);
    return 0;
}
