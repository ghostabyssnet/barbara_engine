#ifndef __PROTO_HPP__
#define __PROTO_HPP__

#include "main.hpp"
#include "msg.hpp"

/* =========================================
 * FIXME: CHANGE THESE FOR THE ACTUAL CLIENT
 * 1) socket errors should return error messages
 * instead of sending only debug messages
 * (send debug messages on success only)
 */

namespace b_net {
    class client {
        public:
            client_socket c;
            short new_conn(client_socket s);
    };
}

#endif
