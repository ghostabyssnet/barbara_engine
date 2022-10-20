#include "client_cli.hpp"

namespace b_net {
   
    void client::handle_data(std::string data) {
        if (data.compare("ACK") == 0) return; // ignore ACKs
        if (data.compare("BE_ERROR_WAIT") == 0) std::cout << "A partida ainda nao foi iniciada! Aguarde pelo outro jogador.\n";
        else if (data.compare(std::string("BE_ERROR_MOVED")) == 0) std::cout << "Voce ja moveu neste turno!\n";
        // it should be a broadcast() by now
        else std::cout << data << std::endl;
    }

    void client::net_send(client_socket c) {
        int _status;
        int hand;
        std::string buffer;
        do {
            std::cout << "Digite 1 para pedra, 2 para papel e 3 para tesoura...\nOu digite 0 para sair.\n";
            std::cin >> hand;
            if (!std::cin) std::cout << "Nao foi um numero valido, tente novamente.\n"; 
            // we would/will use should_quit for this, but we ain't
            // bothering with it on the lite version
            if (hand == 0) exit(0); 
            else {
                switch(hand) {
                    case HAND_PAPER:
                        buffer = "BE_MOVE_PAPER";
                        break;
                    case HAND_SCISSORS:
                        buffer = "BE_MOVE_SCISSORS";
                        break;
                    case HAND_ROCK:
                        buffer = "BE_MOVE_ROCK";
                        break;
                }
                // adding MSG_NOSIGNAL so it doesn't abort on failed
                // connection
                _status = send(c.c_sock, buffer.c_str(), strlen((buffer.c_str())), MSG_NOSIGNAL); 
                if (_status < 0) b_util::debug("Error writing to socket\n");
            }
            b_util::debug("Waiting 10msecs...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            b_util::debug("Done!\n");
        } while (should_quit == false);
        b_util::debug("net_send() exiting gracefully.\n");
    }

    void client::net_recv(client_socket c) {
        int _status;
        char buffer[256];
        while (should_quit == false) {
            bzero(buffer, 256);
            _status = read(c.c_sock, buffer, 255);
            if (_status < 0) b_util::debug("Error reading from socket\n");
            if (_status > 0) b_util::debug(std::string(buffer) + "\n");
            // send our received packet to be handled
            handle_data(std::string(buffer));
        }
        b_util::debug("net_recv() exiting gracefully.\n");
    }

    short client::new_conn(client_socket s) {
        /* resets our socket to its initial values
         * (actually it nullifies everything in it) */
        bzero((char*) &s.s_sock, sizeof(s.s_sock));
        // sets our (int) socket... type? to a socket... somehow
        s.c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (s.c_sock < 0) b_util::debug("Error opening socket at new_conn()\n");
        // get our ip from cfg
        std::string _ip = b_util::server_ip();
        // worked fine without converting to c_str() for some reason
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
