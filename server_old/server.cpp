#include "main.hpp"
#include "msg.hpp"

// use cmd <<serverpile>> to compile
// also TODO: create makefile I guess

// TODO: create event-to-string API here

void msg::send(void *socket) {
    const char* z_str = data.c_str();
    zmq_send(socket, strdup(z_str), strlen(z_str), 0);
}

namespace server {
    std::string recv(void *socket) {
        std::string r;
        char buffer[MSG_BUFFER_SIZE];
        uint8_t msg_size = zmq_recv(socket, buffer, MSG_BUFFER_SIZE, 0);
        if (msg_size == -1) r = "NULL"; // proper NULL gives us undefined behavior when casting to std::string (ask the c++ devs why idk)
        // avoid buffer overflow
        if (msg_size > MSG_BUFFER_SIZE) msg_size = MSG_BUFFER_SIZE;
        r = std::string(buffer);
        return r;
    }
}

int main() {
    // init context
    void *ctx = zmq_ctx_new();
    return 0;
}
