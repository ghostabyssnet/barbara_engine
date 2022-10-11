#include "proto_client.hpp"



namespace b_net {
    short client::new_conn(client_socket s) {
        int phld;
        char buffer[256];
        /* resets our socket to its initial values
         * (actually it nullifies everything in it)
         * FIXME: should probably remove the class constructor
         * if/when we have the time to do so, as it's being
         * set to something then set to null...*/
        bzero((char*) &s.s_sock, sizeof(s.s_sock));
        // sets our (int) socket... type? to a socket... somehow
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) b_util::debug("Error opening socket at new_conn()\n");
        s.server = gethostbyname(BE_IP);
        if (s.server == NULL) b_util::debug("Error connecting to server: no such host\n");
        s.s_sock.sin_family = AF_INET;
        // copies stuff defined in s_addr to h_addr
        // s_addr = server addr; h_addr = home addr
        bcopy((char*)s.server->h_addr, (char*)&s.s_sock.sin_addr.s_addr, s.server->h_length);
        // htons() is used to convert a unsigned short (uint16_t) to
        // the same thing, but in network byte order
        // tl;dr: some archaic stuff from back when PCs had completely
        // different architectures for a bunch of stuff
        s.s_sock.sin_port = htons(BE_PORT);
        // actually attempts to connect to the server
        if (connect(s.c_sock, (struct sockaddr*)&s.s_sock, sizeof(s.s_sock)) < 0) return BERR_CONN_SOCKET;
        b_util::debug("Successfully connected to the server at " + std::to_string(BE_PORT) + "!\n");
        std::cout << "Type your message here or something:\n";
        bzero(buffer, 256);
        // using fgets because we can't be bothered to convert it to
        // cpp strings
        fgets(buffer,255,stdin);
        phld = write(s.c_sock, buffer, strlen(buffer));
        if (phld < 0) b_util::debug("Error writing to socket\n");
        bzero(buffer, 256);
        phld = read(s.c_sock, buffer, 255);
        if (phld < 0) b_util::debug("Error reading from socket\n");
        std::cout << std::string(buffer);
        close(s.c_sock);
        return 0;
    }
}

int main() {
    b_net::client c;
    std::cout << "Starting prototype client...\n";
    short z = c.new_conn(c.c);
    std::cout << std::to_string(z) << std::endl;
    return 0;
}
