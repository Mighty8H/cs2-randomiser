#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <memory>
#include <cmath>
#include "cs2_randomiser.hpp"

using std::string;

const uint8_t name_length = 255;
uint16_t temp_num_players;

struct Player {
    string Name;
    string Terro_secondary;
    string Ct_secondary;
    string Terro_primary;
    string Ct_primary;
    bool Team_ct = false;
};

std::vector<Player> players;

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

int get_rand_int(int min, int max) {
    return min + (int) ((max+1.0) * (rand() / (RAND_MAX + 1.0)));
}

void add_players() {
    string str_num_players;

    std::cout << "\n";
    std::cin.ignore();
    do {
        std::cout << "Enter number of players ";
        std::cin >> str_num_players;
    }
    while(is_integer(str_num_players));

    std::cin.ignore();

    for(size_t i = 0; i < temp_num_players; i++) {
        Player p;
        std::unique_ptr<char[]> temp_text(new char[name_length]);

        //get name from console
        std::cout << "\nEnter player No." << i+1 << " name ";
        std::cin.getline(temp_text.get(), name_length);

        //check if a player with that name already exists
        auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.Name == temp_text.get(); });
        if(it != players.end()) {
            std::cerr << "a player already exists with this name\n";
            i--;
            continue;
        }

        //if not, put it in vector
        p.Name = (temp_text.get() ? temp_text.get() : "");
        players.emplace_back(p);
    }
    std::cout << "\n";
}

void del_player() {
    std::cout << "\n";
    if(players.empty()) {
        std::cerr << "no player exists\n";
        return;
    }

    std::cin.ignore();

    std::unique_ptr<char[]> player_name(new char[name_length]);

    std::cout << "Enter name of a player you want to delete\n";
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << players[i].Name << "\n";
    }

    std::cin.getline(player_name.get(), name_length);
    auto it = std::find_if(players.begin(), players.end(),
    [&](const Player& p) { return p.Name == player_name.get(); });

    if(it != players.end()) {
        players.erase(it);
        std::cout << "Player deleted\n";
    } 
    else {
        std::cerr << "Player not found\n";
    }
    std::cout << "\n";
}

void rand_weapons_separately() {
    std::cout << "\n";
    if(players.empty()) {
        std::cerr << "no player exists\n";
        return;
    }

    //randomising weapons for players
    for(size_t i = 0; i < players.size(); i++) {
        players[i].Terro_secondary = terro_secondary[get_rand_int(0, 6)];
        players[i].Ct_secondary = ct_secondary[get_rand_int(0, 7)];

        if(get_rand_int(0, 1999) == 69)
            players[i].Terro_primary = "Zeus x27";
        else
            players[i].Terro_primary = terro_primary[get_rand_int(0, 16)];

        if(get_rand_int(0, 1999) == 420)
            players[i].Ct_primary = "Zeus x27";
        else
            players[i].Ct_primary = ct_primary[get_rand_int(0, 17)];
            
    }

    //printing
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << players[i].Name << ": \nt: " << players[i].Terro_secondary << ", " << players[i].Terro_primary
                                     << "\nct: " << players[i].Ct_secondary << ", " << players[i].Ct_primary << "\n\n";
    }
    std::cout << "\n";
}

void rand_weapons_together() {
    std::cout << "\n";

    std::cin.ignore();

    string rand_gun;
    std::vector<string> t_arr(5);   //terrorist
    std::vector<string> ct_arr(5);  //counter-terrorists

    //randomising weapons for t
    t_arr[0] = terro_secondary[get_rand_int(0, 6)];
    while(t_arr[1].empty()) {
        rand_gun = terro_secondary[get_rand_int(0, 6)];

        if(!in_array(rand_gun, t_arr)) {
            t_arr[1] = rand_gun;
        }
    }

    t_arr[2] = terro_primary[get_rand_int(0, 16)];
    while(t_arr[3].empty() || t_arr[4].empty()) {
        rand_gun = terro_primary[get_rand_int(0, 16)];

        if(t_arr[3].empty() && !in_array(rand_gun, t_arr)) {
            t_arr[3] = rand_gun;
        }
        else if(!in_array(rand_gun, t_arr)) {
            t_arr[4] = rand_gun;
        }
    }

    //randomising weapons for ct_arr
    ct_arr[0] = ct_secondary[get_rand_int(0, 7)];
    while(ct_arr[1].empty()) {
        rand_gun = ct_secondary[get_rand_int(0, 7)];

        if(!in_array(rand_gun, ct_arr)) {
            ct_arr[1] = rand_gun;
        }
    }

    ct_arr[2] = ct_primary[get_rand_int(0, 17)];
    while(ct_arr[3].empty() || ct_arr[4].empty()) {
        rand_gun = ct_primary[get_rand_int(0, 17)];

        if(ct_arr[3].empty() && !in_array(rand_gun, ct_arr)) {
            ct_arr[3] = rand_gun;
        }
        else if(!in_array(rand_gun, ct_arr)) {
            ct_arr[4] = rand_gun;
        }
    }
    
    //printing
    std::cout << "t: " << t_arr[0] << ", " << t_arr[1] << "; " << t_arr[2] << ", " << t_arr[3] << ", " << t_arr[4] << "\n"
              << "ct: " << ct_arr[0] << ", " << ct_arr[1] << "; " << ct_arr[2] << ", " << ct_arr[3] << ", " << ct_arr[4] << "\n";
    
    std::cout << "\n";
}

void rand_team() {
    std::cout << "\n";
    if(players.empty()) {
        std::cerr << "no player exists\n";
        return;
    }

    float half_of_players;
    for(size_t i = 0; i < players.size(); i++)
        players[i].Team_ct = false;


    //determinate if round up or down
    if(get_rand_int(0, 1))
        half_of_players = floor((float)players.size()/2);
    else
        half_of_players = ceil((float)players.size()/2);

    //set first player to team ct
    int rand_player = get_rand_int(0, players.size()-1);
    players[rand_player].Team_ct = true;

    //set rest of the players to team ct
    for(size_t i = 0; i < half_of_players-1; i++) {
        rand_player = get_rand_int(0, players.size()-1);
        if(players[rand_player].Team_ct) {
            half_of_players++;
            continue;
        }
        players[rand_player].Team_ct = true;
    }


    //printing ct players
    std::cout << "ct players:\n";
    for(size_t i = 0; i < players.size(); i++) {
        if(players[i].Team_ct)
            std::cout << players[i].Name << "\n";
    }

    //printing t players
    std::cout << "t players:\n";
    for(size_t i = 0; i < players.size(); i++) {
        if(!players[i].Team_ct)
            std::cout << players[i].Name << "\n";
    }
    std::cout << "\n";
}

void rand_maps() {
    std::cout << "\n";
    std::cout << maps[get_rand_int(0, 13)] << "\n";
    std::cout << "\n";
}

int main() {
    string n;
    srand(time(nullptr));
    while(true) {
        std::cout << "Choose option(exit - exit program; add - add players; del - delete player; 1 - randomise weapons for everyone separately; 2 - randomise weapons for everyone together; 3 - randomise team; 4 - randomise map)\n";
        std::cin >> n;

        if(n.compare("exit") == 0)      return 0;
        else if(n.compare("add") == 0)  add_players();
        else if(n.compare("del") == 0)  del_player();
        else if(n.compare("1") == 0)    rand_weapons_separately();
        else if(n.compare("2") == 0)    rand_weapons_together();
        else if(n.compare("3") == 0)    rand_team();
        else if(n.compare("4") == 0)    rand_maps();
        else                            std::cerr << "invalid option\n";
    }
}