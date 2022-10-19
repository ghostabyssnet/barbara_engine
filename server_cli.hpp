#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "msg.hpp"
#include "sql.hpp"

#define STATE_WAIT 0
#define STATE_MATCH 1
#define STATE_END 2 // FIXME: check if we're going to use this

#define MOVE_NONE 0
#define MOVE_PAPER 1
#define MOVE_SCISSORS 2
#define MOVE_ROCK 3

namespace b_net { 

    class player {
        public:
            uint8_t id;
            uint8_t score = 0;
            uint8_t move = MOVE_NONE;
            player(uint8_t _id) {
                id = _id;
            }
    };

    // cunny is our message broker and game server, it handles how many
    // messages were sent and received, their ID counter,
    // etc -- whatever is cute and funny to do
    class cunny_t {
        public:
            uint64_t id_count = 1; // msg count (next ID to be used)
            // connected users
            std::vector<server_socket> conn_list;
            server_socket serv;
            short host(server_socket s);
            msg_t get_data(server_socket s);
            void send_data(server_socket s, std::string data);
            void new_conn(server_socket s, player p);
            
            uint8_t game_state = STATE_WAIT;
            uint8_t turn = 0;
            std::vector<player> players;

            void prepare() {
                game_state = STATE_WAIT;
            }

            void start_match() {
                game_state = STATE_MATCH;
                turn = 0;
            }

            void player_move(uint8_t move, player p) {
                p.move = move;
                if (turn == 0) turn = 1;
                else turn = 0;
            }

            void on_player_move(std::string data, player p) {
                if (data.compare(std::string("BE_MOVE_PAPER")) == 0) player_move(MOVE_PAPER, p); 
                else if (data.compare(std::string("BE_MOVE_SCISSORS")) == 0) player_move(MOVE_SCISSORS, p);
                else if (data.compare(std::string("BE_MOVE_ROCK")) == 0) player_move(MOVE_ROCK, p);
                
                // resolve the players' turns if both of them already
                // made their move
                if (players[0].move != MOVE_NONE && players[1].move != MOVE_NONE) resolve();
            }

            uint8_t check_winner(uint8_t move, uint8_t _move) {
                if (move == _move) return 0; // no winner
                if (move == MOVE_ROCK && _move == MOVE_SCISSORS) return 1;
                if (move == MOVE_PAPER && _move == MOVE_ROCK) return 1;
                if (move == MOVE_SCISSORS && _move = MOVE_PAPER) return 1;
                if (_move == MOVE_ROCK && move == MOVE_SCISSORS) return 2;
                if (_move == MOVE_PAPER && move == MOVE_ROCK) return 2;
                if (_move == MOVE_SCISSORS && move = MOVE_PAPER) return 2;
                return 0; // something went wrong
            }
            
            // reset player moves
            // will also reset their score if the end flag is set
            void reset_players(bool end = false) {
                players[0].move = MOVE_NONE;
                players[1].move = MOVE_NONE;
                if (end) {
                    players[0].score = 0;
                    players[1].score = 0;
                }
            }
            
            bool check_match_end() {
                if (players[0].score >= 5) {
                    end_match(0);
                    return true;
                }
                else if (players[1].score >= 5) {
                    end_match(1);
                    return true;
                }
                return false;
            }

            void resolve() {
                int winner = check_winner(players[0].move, players[1].move);
                if (winner == 1) players[0].score++;
                else if (winner == 2) players[1].score++;
                else broadcast("BE_TURN_TIE");
                bool _r = check_match_end();
                // will reset scores as well if the match has ended
                reset_players(_r);
            }

            void end_match() {
                start_match();
            }

            // ideally, this should use uint8_t to return
            // multiple error types
            bool handle_data(msg_t msg);
            
    };
    
    class database_t {
        // TODO: this
    };

    class server {
        public:
            cunny_t cunny;
            database_t db;            
    };
}
#endif
