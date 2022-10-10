#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

class online_player {
    public:
        // TODO: b_net::connection theirconnection;
        std::string username;
        std::string password;
        uint16_t rating;
        std::vector<int> owned_skins; // their ids maybe
};

#endif
