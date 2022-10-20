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
#include <fstream>

// b_util constants and other stuff

// defines if we're in debug mode or not
#define BE_DEBUG true

// b_network constants
#define NET_BUFFER_SIZE (int)256
#define CFG_PATH "config.babs"
#define BE_PORT (int)8080

namespace b_util {
    
    void debug(std::string f) { if (BE_DEBUG) std::cout << "[DEBUG] " << f; } 
    
    bool file_exists(std::string name) {
        std::ifstream f(name.c_str());
        return f.good();
    }
    
    std::string server_ip() {
        bool flag = false;
        std::string r;
        if (!file_exists(CFG_PATH)) flag = true;
        if (flag) {
            std::ofstream f(CFG_PATH); 
            f << "127.0.0.1"; // insert base IP to file if it doesn't exist
            f.close();
        }
        std::ifstream _f(CFG_PATH);
        std::getline(_f, r);
        return r;
    }
}

#endif
