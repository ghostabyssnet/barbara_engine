#ifndef __PROTO_HPP__
#define __PROTO_HPP__

#include "main.hpp"
#include "msg.hpp"

namespace b_net {
    class client {
        public:
            client_socket c;
            short new_conn(client_socket s);
    };
}

#endif
