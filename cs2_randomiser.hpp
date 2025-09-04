#include <string>
#include <vector>
#include <array>

//data up to date as of 31.07.2025
const std::array<std::string, 7> terro_secondary = { "Glock-18", "Dual Berettas", "P250", "Tec-9", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
const std::array<std::string, 8> ct_secondary = { "P2000", "USP-S", "Dual Berettas", "P250", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
const std::array<std::string, 17> terro_primary = { "MAC-10", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "Sawed-Off", "M249", "Negev", "Galil AR", "AK-47", "SSG 08", "SG 553", "AWP", "G3SG1" };
const std::array<std::string, 18> ct_primary = { "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "MAG-7", "M249", "Negev", "FAMAS", "M4A4", "M4A1-S", "SSG 08", "AUG", "AWP", "SCAR-20" };
const std::array<std::string, 14> maps = { "Dust II", "Mirage", "Vertigo", "Ancient", "Inferno", "Nuke", "Train", "Anubis", "Overpass", "Jura", "Grail", "Agency", "Office", "Italy" };

bool is_integer(const std::string& str);
int get_rand_int(int min, int max);
uint8_t get_weapon_count(const std::string& prompt, size_t max_size);
void add_players();
void del_player();
void rand_weapons_separately();
void rand_weapons_together();
void rand_weapons_individualy();
void rand_team();
void rand_maps();