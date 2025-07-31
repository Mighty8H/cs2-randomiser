#include <string>
#include <vector>

//data up to date as of 31.07.2025
const std::string terro_secondary[7] = { "Glock-18", "Dual Berettas", "P250", "Tec-9", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
const std::string ct_secondary[8] = { "P2000", "USP-S", "Dual Berettas", "P250", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
const std::string terro_primary[17] = { "MAC-10", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "Sawed-Off", "M249", "Negev", "Galil AR", "AK-47", "SSG 08", "SG 553", "AWP", "G3SG1" };
const std::string ct_primary[18] = { "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "MAG-7", "M249", "Negev", "FAMAS", "M4A4", "M4A1-S", "SSG 08", "AUG", "AWP", "SCAR-20" };
const std::string maps[14] = { "Dust II", "Mirage", "Vertigo", "Ancient", "Inferno", "Nuke", "Train", "Anubis", "Overpass", "Jura", "Grail", "Agency", "Office", "Italy" };

bool in_array(const std::string& value, const std::vector<std::string>& array);
bool is_integer(const std::string& str);
int get_rand_int(int min, int max);
void add_players();
void del_player();
void rand_weapons_separately();
void rand_weapons_together();
void rand_team();
void rand_maps();