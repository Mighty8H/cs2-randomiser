#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <ctime>

/*
TODO: 
- 1/1000 zeus chance instead of primary
- make header file
- fix function los_bronii_oddzielnie
- add function los_druzyn
*/

using std::string;

uint16_t ilosc_graczy = 0;
uint16_t temp_ilosc_graczy;
const uint8_t dlugosc_nazwy = 255;
char* temp_text = new char[dlugosc_nazwy];
std::vector<Gracz> gracze;
string str_ilosc_graczy;
string n;

//dane aktualne na dzien 30.07.2025
const string terro_pistolety[7] = { "Glock-18", "Dual Berettas", "P250", "Tec-9", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
const string ct_pistolety[8] = { "P2000", "USP-S", "Dual Berettas", "P250", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
const string terro_bronie_glowne[17] = { "MAC-10", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "Sawed-Off", "M249", "Negev", "Galil AR", "AK-47", "SSG 08", "SG 553", "AWP", "G3SG1" };
const string ct_bronie_glowne[18] = { "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "MAG-7", "M249", "Negev", "FAMAS", "M4A4", "M4A1-S", "SSG 08", "AUG", "AWP", "SCAR-20" };
const string mapy[13] = { "Dust II", "Mirage", "Vertigo", "Ancient", "Inferno", "Nuke", "Anubis", "Overpass", "Jura", "Grail", "Agency", "Office", "Italy" };

struct Gracz {
    string nazwa;
    string terro_pistolet;
    string ct_pistolet;
    string terro_bron_glowna;
    string ct_bron_glowna;
    string druzyna;
};

bool in_array(const std::string& value, const std::vector<std::string>& array) {
    return std::find(array.begin(), array.end(), value) != array.end();
}

bool is_integer(const std::string& str) {
    try {
        temp_ilosc_graczy = std::stoi(str);
        return false;
    }
    catch(const std::invalid_argument& e) {
        std::cerr << "podany napis nie jest liczba" << "\n";
        return true;
    }
}

void dodaj_graczy() {
    do {
        std::cout << "Podaj ilosc graczy ";
        std::cin >> str_ilosc_graczy;
    }
    while(is_integer(str_ilosc_graczy));

    if(gracze.size() == 0)
        std::vector<Gracz> gracze(temp_ilosc_graczy);

    else {
        for(size_t i = 0; i < temp_ilosc_graczy; i++)
            gracze.emplace_back();
    }

    ilosc_graczy += temp_ilosc_graczy;
    std::cin.ignore();
}

void los_bronii_oddzielnie() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_terro_pistolety(0, 6);
    std::uniform_int_distribution<> dist_ct_pistolety(0, 7);
    std::uniform_int_distribution<> dist_terro_bronie_glowne(0, 16);
    std::uniform_int_distribution<> dist_ct_bronie_glowne(0, 17);

    do {
        std::cout << "podaj ilosc graczy ";
        std::cin >> str_ilosc_graczy;
    }
    while(is_integer(str_ilosc_graczy));
	
    //losowanie broni dla graczy
    for(size_t i = 0; i < ilosc_graczy; i++) {
        std::cout << "\npodaj nazwe gracza ";
        
        std::cin.getline(temp_text, dlugosc_nazwy);
        gracze[i].nazwa = (temp_text ? temp_text : "");

        gracze[i].terro_pistolet = terro_pistolety[dist_terro_pistolety(gen)];
        gracze[i].ct_pistolet = ct_pistolety[dist_ct_pistolety(gen)];
        gracze[i].terro_bron_glowna = terro_bronie_glowne[dist_terro_bronie_glowne(gen)];
        gracze[i].ct_bron_glowna = ct_bronie_glowne[dist_ct_bronie_glowne(gen)];
    }

    std::cout << "\n";

    //wypisywanie
    for(size_t i = 0; i < ilosc_graczy; i++) {
        std::cout << gracze[i].nazwa << ": \nterro: " << gracze[i].terro_pistolet << ", " << gracze[i].terro_bron_glowna
                                     << "\nct: " << gracze[i].ct_pistolet << ", " << gracze[i].ct_bron_glowna << "\n\n";
    }
}

void los_bronii_razem() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_terro_pistolety(0, 6);
    std::uniform_int_distribution<> dist_ct_pistolety(0, 7);
    std::uniform_int_distribution<> dist_terro_bronie_glowne(0, 16);
    std::uniform_int_distribution<> dist_ct_bronie_glowne(0, 17);
    
    string los;
    std::vector<string> terro(5);
    std::vector<string> ct(5);

    //losowanie broni dla terro
    terro[0] = terro_pistolety[dist_terro_pistolety(gen)];
    while(terro[1].empty()) {
        los = terro_pistolety[dist_terro_pistolety(gen)];

        if(!in_array(los, terro)) {
            terro[1] = los;
        }
    }

    terro[2] = terro_bronie_glowne[dist_terro_bronie_glowne(gen)];
    while(terro[3].empty() || terro[4].empty()) {
        los = terro_bronie_glowne[dist_terro_bronie_glowne(gen)];

        if(terro[3].empty() && !in_array(los, terro)) {
            terro[3] = los;
        }
        else if(!in_array(los, terro)) {
            terro[4] = los;
        }
    }

    //losowanie broni dla ct
    ct[0] = ct_pistolety[dist_ct_pistolety(gen)];
    while(ct[1].empty()) {
        los = ct_pistolety[dist_ct_pistolety(gen)];

        if(!in_array(los, ct)) {
            ct[1] = los;
        }
    }

    ct[2] = ct_bronie_glowne[dist_ct_bronie_glowne(gen)];
    while(ct[3].empty() || ct[4].empty()) {
        los = ct_bronie_glowne[dist_ct_bronie_glowne(gen)];

        if(ct[3].empty() && !in_array(los, ct)) {
            ct[3] = los;
        }
        else if(!in_array(los, ct)) {
            ct[4] = los;
        }
    }
    
    //wypisywanie
    std::cout << "terro: " << terro[0] << ", " << terro[1] << "; " << terro[2] << ", " << terro[3] << ", " << terro[4]
              << "\nct: " << ct[0] << ", " << ct[1] << "; " << ct[2] << ", " << ct[3] << ", " << ct[4] << "\n";
    
}

void los_druzyn() {

}

void los_mapy() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_mapy(0, 12);
    std::cout << mapy[dist_mapy(gen)] << "\n";
}

int main() {
    while(true) {
        std::cout << "Wybierz opcje(0 - wylacz program; 1 - dodaj graczy; 2 - losowanie bronii dla kazdego oddzielnie; 3 - losowanie bronii dla wszystkich razem; 4 - losowanie druzyn; 5 - losowanie mapy)\n";
        std::cin >> n;

        if(n.compare("0") == 0) {
            delete[] temp_text;
            temp_text = nullptr;
            return 0;
        }
        else if(n.compare("1") == 0)
            dodaj_graczy();

        else if(n.compare("2") == 0)
            los_bronii_oddzielnie();

        else if(n.compare("3") == 0)
            los_bronii_razem();
            
        else if(n.compare("4") == 0)
            los_druzyn();
            
        else if(n.compare("5") == 0)
            los_mapy();

        else
            std::cerr << "nieprawidlowa opcja\n";
    }
}