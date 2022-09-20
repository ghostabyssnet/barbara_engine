#include "main.hpp"
#include "msg.hpp"

// use cmd <<serverpile>> to compile
// also TODO: create makefile I guess

// TODO: create event-to-string API here

namespace server {
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
        
        }
    }
}

int main() {
    b_ssocket s("main");
    server::host(s);
    return 0;
}
