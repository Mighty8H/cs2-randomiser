#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <memory>
#include <cmath>
#include "cs2_randomiser.hpp"

using string = std::string;

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
    return min + (int)((max+1.0) * (rand() / (RAND_MAX + 1.0)));
}

void add_players() {
    std::cout << "\n-----------------------------------\n";
    std::cin.ignore();

    string str_num_players;
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
    std::cout << "-----------------------------------\n\n";
}

void del_player() {
    std::cout << "\n-----------------------------------\n";
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

    //finding player with that name
    std::cin.getline(player_name.get(), name_length);
    auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.Name == player_name.get(); });

    //deleting player
    if(it != players.end()) {
        players.erase(it);
        std::cout << "Player deleted\n";
    } 
    else {
        std::cerr << "Player not found\n";
    }
    std::cout << "-----------------------------------\n\n";
}

void rand_weapons_separately() {
    std::cout << "\n-----------------------------------\n";
    if(players.empty()) {
        std::cerr << "no player exists\n";
        return;
    }

    std::cin.ignore();

    //randomising weapons for players
    for(size_t i = 0; i < players.size(); i++) {
        players[i].Terro_secondary = terro_secondary[get_rand_int(0, terro_secondary.size()-1)];
        players[i].Ct_secondary = ct_secondary[get_rand_int(0, ct_secondary.size()-1)];

        if(get_rand_int(0, 1999) == 69)
            players[i].Terro_primary = "Zeus x27";
        else
            players[i].Terro_primary = terro_primary[get_rand_int(0, terro_primary.size()-1)];

        if(get_rand_int(0, 1999) == 420)
            players[i].Ct_primary = "Zeus x27";
        else
            players[i].Ct_primary = ct_primary[get_rand_int(0, ct_primary.size()-1)];
    }

    //printing
    for(size_t i = 0; i < players.size(); i++) {
        std::cout << players[i].Name << ": \nt:  " << players[i].Terro_secondary << ", " << players[i].Terro_primary
                                     << "\nct: " << players[i].Ct_secondary << ", " << players[i].Ct_primary << "\n\n";
    }
    std::cout << "-----------------------------------\n\n";
}

void rand_weapons_together() {
    std::cout << "\n-----------------------------------\n";

    std::cin.ignore();

    string rand_weapon, tmp_input;
    uint8_t t_sec_num, t_prim_num, ct_sec_num, ct_prim_num;
    uint8_t iter_t_sec = 0;
    uint8_t iter_t_prim = 0;
    uint8_t iter_ct_sec = 0;
    uint8_t iter_ct_prim = 0;

    //entering the number of weapons to be randomised
    do {
        std::cout << "Enter number of terrorist secondary weapons ";
        std::cin >> tmp_input;
    }
    while(is_integer(tmp_input));
    t_sec_num = std::min<uint8_t>(std::stoi(tmp_input), terro_secondary.size());

    do {
        std::cout << "Enter number of terrorist primary weapons ";
        std::cin >> tmp_input;
    }
    while(is_integer(tmp_input));
    t_prim_num = std::min<uint8_t>(std::stoi(tmp_input), terro_primary.size());

    do {
        std::cout << "Enter number of counter-terrorist secondary weapons ";
        std::cin >> tmp_input;
    }
    while(is_integer(tmp_input));
    ct_sec_num = std::min<uint8_t>(std::stoi(tmp_input), ct_secondary.size());

    do {
        std::cout << "Enter number of counter-terrorist primary weapons ";
        std::cin >> tmp_input;
    }
    while(is_integer(tmp_input));
    ct_prim_num = std::min<uint8_t>(std::stoi(tmp_input), ct_primary.size());
    
    std::array<string, terro_secondary.size()> terro_sec_copy  = terro_secondary;
    std::array<string, terro_primary.size()>   terro_prim_copy = terro_primary;
    std::array<string, ct_secondary.size()>    ct_sec_copy     = ct_secondary;
    std::array<string, ct_primary.size()>      ct_prim_copy    = ct_primary;
    
    std::cout << "\nterrorists:\n";
    std::cout << "secondary: ";
    for(size_t i = 0; i < t_sec_num; i++) {
        rand_weapon = terro_sec_copy[get_rand_int(0, terro_sec_copy.size()-1 - iter_t_sec)];
        
        std::cout << rand_weapon;
        if(i < t_sec_num-1)
            std::cout << ", ";
        else
            std::cout << ";\n";
        
        std::remove(terro_sec_copy.begin(), terro_sec_copy.end(), rand_weapon);
        iter_t_sec++;
    }

    std::cout << "primary: ";
    for(size_t i = 0; i < t_prim_num; i++) {
        rand_weapon = terro_prim_copy[get_rand_int(0, terro_prim_copy.size()-1 - iter_t_prim)];

        std::cout << rand_weapon;
        if(i < t_prim_num-1)
            std::cout << ", ";
        else
            std::cout << ";\n";
        
        std::remove(terro_prim_copy.begin(), terro_prim_copy.end(), rand_weapon);
        iter_t_prim++;
    }

    std::cout << "\ncounter-terrorists:\n";
    std::cout << "secondary: ";
    for(size_t i = 0; i < ct_sec_num; i++) {
        rand_weapon = ct_sec_copy[get_rand_int(0, ct_sec_copy.size()-1 - iter_ct_sec)];

        std::cout << rand_weapon;
        if(i < ct_sec_num-1)
            std::cout << ", ";
        else
            std::cout << ";\n";
        
        std::remove(ct_sec_copy.begin(), ct_sec_copy.end(), rand_weapon);
        iter_ct_sec++;
    }
    
    std::cout << "primary: ";
    for(size_t i = 0; i < ct_prim_num; i++) {
        rand_weapon =  ct_prim_copy[get_rand_int(0, ct_prim_copy.size()-1 - iter_ct_prim)];

        std::cout << rand_weapon;
        if(i < ct_prim_num-1)
            std::cout << ", ";
        else
            std::cout << ";\n";
        
        std::remove(ct_prim_copy.begin(), ct_prim_copy.end(), rand_weapon);
        iter_ct_prim++;
    }

    std::cout << "-----------------------------------\n\n";
}

void rand_weapons_individualy() {
    std::cout << "\n-----------------------------------\n";
    if(players.empty()) {
        std::cerr << "no player exists\n";
        return;
    }

    std::cin.ignore();

    std::unique_ptr<char[]> player_name = std::make_unique<char[]>(name_length);

    std::cout << "Enter the name of the player you want to roll for:\n";
    for(const auto& player : players) {
        std::cout << player.Name << "\n";
    }

    //finding player with that name
    std::cin.getline(player_name.get(), name_length);
    auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.Name == player_name.get(); });

    if(it != players.end()) {
        it->Terro_secondary = terro_secondary[get_rand_int(0, terro_secondary.size()-1)];
        it->Ct_secondary = ct_secondary[get_rand_int(0, ct_secondary.size()-1)];

        if(get_rand_int(0, 1999) == 69)
            it->Terro_primary = "Zeus x27";
        else
            it->Terro_primary = terro_primary[get_rand_int(0, terro_primary.size()-1)];

        if(get_rand_int(0, 1999) == 420)
            it->Ct_primary = "Zeus x27";
        else
            it->Ct_primary = ct_primary[get_rand_int(0, ct_primary.size()-1)];

        //printing
        std::cout << "\n" << it->Name << ": \nt:  " << it->Terro_secondary << ", " << it->Terro_primary
                                      << "\nct: " << it->Ct_secondary << ", " << it->Ct_primary << "\n";
    }
    else {
        std::cerr << "Player not found\n";
    }
    std::cout << "-----------------------------------\n\n";
}

void rand_team() {
    std::cout << "\n-----------------------------------\n";
    if(players.empty()) {
        std::cerr << "no player exists\n";
        return;
    }

    float half_of_players;

    //set all players' teams to false
    for(size_t i = 0; i < players.size(); i++)
        players[i].Team_ct = false;


    //determinate if round up or down
    if(get_rand_int(0, 1))
        half_of_players = floor((float)players.size() / 2);
    else
        half_of_players = ceil((float)players.size() / 2);

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
    std::cout << "-----------------------------------\n\n";
}

void rand_maps() {
    std::cout << "\n-----------------------------------\n";
    std::cout << maps[get_rand_int(0, maps.size()-1)] << "\n";
    std::cout << "-----------------------------------\n\n";
}

int main() {
    string n;
    srand(time(nullptr));
    while(true) {
        std::cout << "Choose option\n" 
                  << "exit - exit program\n" 
                  << "add - add players\n" 
                  << "del - delete player\n" 
                  << "1 - randomise weapons for everyone separately\n"
                  << "2 - randomise weapons for everyone together\n"
                  << "3 - randomise weapons for one person\n"
                  << "4 - randomise team\n"
                  << "5 - randomise map\n";
        std::cin >> n;

        if(n.compare("exit") == 0)      return 0;
        else if(n.compare("add") == 0)  add_players();
        else if(n.compare("del") == 0)  del_player();
        else if(n.compare("1") == 0)    rand_weapons_separately();
        else if(n.compare("2") == 0)    rand_weapons_together();
        else if(n.compare("3") == 0)    rand_weapons_individualy();
        else if(n.compare("4") == 0)    rand_team();
        else if(n.compare("5") == 0)    rand_maps();
        else                            std::cerr << "invalid option\n";
    }
}