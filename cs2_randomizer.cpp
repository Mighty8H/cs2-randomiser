#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <memory>
#include "cs2_randomiser.hpp"

/*
TODO: 
- 1/1000 zeus chance instead of primary
- fix function rand_weapons_separatly
- add function rand_teams
*/

using std::string;

uint16_t temp_num_players;
std::vector<Player> players;

struct Player {
    string Name;
    string Terro_secondary;
    string Ct_secondary;
    string Terro_primary;
    string Ct_primary;
    string Team;
};

bool in_array(const std::string& value, const std::vector<std::string>& array) {
    return std::find(array.begin(), array.end(), value) != array.end();
}

bool is_integer(const std::string& str) {
    try {
        temp_num_players = std::stoi(str);
        return false;
    }
    catch(const std::invalid_argument& e) {
        std::cerr << "entered string isn't a number" << "\n";
        return true;
    }
}

int get_rand_index(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void add_players() {
    string str_num_players;

    do {
        std::cout << "Enter number of players ";
        std::cin >> str_num_players;
    }
    while(is_integer(str_num_players));

    if(players.size() == 0)
        std::vector<Player> players(temp_num_players);

    else {
        for(size_t i = 0; i < temp_num_players; i++)
            players.emplace_back();
    }

    std::cin.ignore();
}

void rand_weapons_separately() {
    const uint8_t name_length = 255;
    std::unique_ptr<char[]> temp_text(new char[name_length]);
    
    //randomising weapons for players
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << "\nEnter player No." << i+1 << " name ";
        
        std::cin.getline(temp_text.get(), name_length);
        players[i].name = (temp_text.get() ? temp_text.get() : "");

        players[i].Terro_secondary = terro_secondary[get_rand_index(0, 6)];
        players[i].Ct_secondary = ct_secondary[get_rand_index(0, 7)];
        players[i].Terro_primary = terro_primary[get_rand_index(0, 16)];
        players[i].Ct_primary = ct_primary[get_rand_index(0, 17)];
    }

    std::cout << "\n";

    //printing
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << players[i].name << ": \nterro: " << players[i].terro_secondary << ", " << players[i].terro_primary
                                     << "\nct: " << players[i].ct_secondary << ", " << players[i].ct_primary << "\n\n";
    }
}

void rand_weapons_together() {
    string rand_gun;
    std::vector<string> terro(5);
    std::vector<string> ct(5);

    //randomising weapons for terro
    terro[0] = terro_secondary[get_rand_index(0, 6)];
    while(terro[1].empty()) {
        rand_gun = terro_secondary[get_rand_index(0, 6)];

        if(!in_array(rand_gun, terro)) {
            terro[1] = rand_gun;
        }
    }

    terro[2] = terro_primary[get_rand_index(0, 16)];
    while(terro[3].empty() || terro[4].empty()) {
        rand_gun = terro_primary[get_rand_index(0, 16)];

        if(terro[3].empty() && !in_array(rand_gun, terro)) {
            terro[3] = rand_gun;
        }
        else if(!in_array(rand_gun, terro)) {
            terro[4] = rand_gun;
        }
    }

    //randomising weapons for ct
    ct[0] = ct_secondary[get_rand_index(0, 7)];
    while(ct[1].empty()) {
        rand_gun = ct_secondary[get_rand_index(0, 7)];

        if(!in_array(rand_gun, ct)) {
            ct[1] = rand_gun;
        }
    }

    ct[2] = ct_primary[get_rand_index(0, 17)];
    while(ct[3].empty() || ct[4].empty()) {
        rand_gun = ct_primary[get_rand_index(0, 17)];

        if(ct[3].empty() && !in_array(rand_gun, ct)) {
            ct[3] = rand_gun;
        }
        else if(!in_array(rand_gun, ct)) {
            ct[4] = rand_gun;
        }
    }
    
    //printing
    std::cout << "terro: " << terro[0] << ", " << terro[1] << "; " << terro[2] << ", " << terro[3] << ", " << terro[4] << "\n"
              << "ct: " << ct[0] << ", " << ct[1] << "; " << ct[2] << ", " << ct[3] << ", " << ct[4] << "\n";
    
}

void rand_team() {

}

void rand_maps() {
    std::cout << maps[get_rand_index(0, 12)] << "\n";
}

int main() {
    string n;
    while(true) {
        std::cout << "Choose option(0 - exit program; 1 - add players; 2 - randomise weapons for everyone separately; 3 - randomise weapons for everyone together; 4 - randomise team; 5 - randomise map)\n";
        std::cin >> n;

        if(n.compare("0") == 0) {
            return 0;
        }
        else if(n.compare("1") == 0)
            add_players();

        else if(n.compare("2") == 0)
            rand_weapons_separately();

        else if(n.compare("3") == 0)
            rand_weapons_together();
            
        else if(n.compare("4") == 0)
            rand_team();
            
        else if(n.compare("5") == 0)
            rand_maps();

        else
            std::cerr << "invalid option\n";
    }
}