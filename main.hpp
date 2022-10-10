#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
// TODO: check for windows and, if it's the case,
// use winsock instead of socket.h
#include <sys/types.h>
#include <sys/socket.h>
#include <bits/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
// defines if we're in debug mode or not
#define BE_DEBUG false

// b_network constants
#define NET_BUFFER_SIZE (uint16_t)4096
#define BE_IP "127.0.0.1" // TODO: change to config file
#define BE_PORT (int)8080

class Event {
    public:
        // f = event_name
        Event(std::string f) {
            if (BE_DEBUG) std::cout << f;
            delete(this);
        }
};

#endif
