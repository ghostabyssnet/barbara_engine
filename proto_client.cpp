#include "proto_client.hpp"

namespace b_net {
    short client::new_conn(client_socket s) {
        int phld;
        char buffer[256];
        bzero((char*) &s.s_sock, sizeof(s.s_sock));
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        s.server = gethostbyname(BE_IP);
        std::cout << "a";
        s.s_sock.sin_family = AF_INET;
        bcopy((char*)s.server->h_addr, (char*)&s.s_sock.sin_addr.s_addr, s.server->h_length);
        std::cout << "a";
        s.s_sock.sin_port = htons(BE_PORT);
        if (connect(s.c_sock, (struct sockaddr*)&s.s_sock, sizeof(s.s_sock)) < 0) return BERR_CONN_SOCKET;
        std::cout << "msg:\n";
        bzero(buffer, 256);
        phld = write(s.c_sock, buffer, strlen(buffer));
        bzero(buffer, 256);
        phld = read(s.c_sock, buffer, 255);
        std::cout << std::string(buffer);
        close(s.c_sock);
        return 0;
    }
}

int main() {
    std::cout << "a";
    b_net::client c;
    short z = c.new_conn(c.c);
    std::cout << std::to_string(z) << std::endl;
    std::cout << "a";
    return 0;
}
