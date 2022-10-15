#include "client_cli.hpp"

namespace b_net {
    void client::net_send(client_socket c) {
        int _status;
        char buffer[256];
        do {
            std::cout << "Type your message here or something:\n";
            bzero(buffer, 256);
            // using fgets because we can't be bothered to convert it to
            // cpp strings
            b_util::debug("a\n");
            fgets(buffer,255,stdin);
            b_util::debug("b\n");
            if(std::string(buffer).compare("BE_QUIT") == 0) { 
                b_util::debug("c\n");
                should_quit = true; 
            }
            else {
                b_util::debug("d\n");
                // adding MSG_NOSIGNAL so it doesn't abort on failed
                // connection
                _status = send(c.c_sock, buffer, strlen(buffer), MSG_NOSIGNAL);
                b_util::debug("e\n");
                if (_status < 0) b_util::debug("Error writing to socket\n");
            }
            b_util::debug("Waiting 10msecs...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            b_util::debug("Done!\n");
        } while(should_quit == false);
        b_util::debug("net_send() exiting gracefully.\n");
    }
    void client::net_recv(client_socket c) {
        int _status;
        char buffer[256];
        while (should_quit == false) {
            bzero(buffer, 256);
            _status = read(c.c_sock, buffer, 255);
            if (_status < 0) b_util::debug("Error reading from socket\n");
            if (_status > 0) b_util::debug("DEBUG: " + std::string(buffer) + "\n");
        }
        b_util::debug("net_recv() exiting gracefully.\n");
    }
    short client::new_conn(client_socket s) {
        /* resets our socket to its initial values
         * (actually it nullifies everything in it)*/
        bzero((char*) &s.s_sock, sizeof(s.s_sock));
        // sets our (int) socket... type? to a socket... somehow
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) b_util::debug("Error opening socket at new_conn()\n");
        // get our ip from cfg
        std::string _ip = b_util::server_ip();
        // FIXME: worked without converting to c_str() for some reason.
        // test properly later
        s.server = gethostbyname(_ip.c_str());
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
        b_util::debug("Successfully connected to the server at " + _ip + ":" + std::to_string(BE_PORT) + "!\n");
        // create send and recv threads
        std::thread send_t(&client::net_send, this, s);
        std::thread recv_t(&client::net_recv, this, s);
        recv_t.join();
        send_t.join();
        //while (should_quit == false) std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // close socket when we're done
        b_util::debug("Closing socket...\n");
        close(s.c_sock);
        return 0;
    }
}

int main() {
    b_net::client c;
    std::cout << "Starting prototype client...\n";
    short z = c.new_conn(c.c);
    std::cout << std::to_string(z) << std::endl;
    std::cout << "Exiting gracefully.\n";
    return 0;
}
