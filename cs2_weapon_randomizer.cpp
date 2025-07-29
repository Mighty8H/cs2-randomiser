#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>

using std::string;

unsigned short int ilosc_graczy;
unsigned short int dlugosc_nazwy = 256;
char* temp_text = new char[dlugosc_nazwy];
string str_ilosc_graczy, n;
string terro_pistolety[7] = { "Glock-18", "Dual Berettas", "P250", "Tec-9", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
string ct_pistolety[8] = { "P2000", "USP-S", "Dual Berettas", "P250", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
string terro_bronie_glowne[17] = { "MAC-10", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "Sawed-Off", "M249", "Negev", "Galil AR", "AK-47", "SSG 08", "SG 553", "AWP", "G3SG1" };
string ct_bronie_glowne[18] = { "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon", "Nova", "XM1014", "MAG-7", "M249", "Negev", "FAMAS", "M4A4", "M4A1-S", "SSG 08", "AUG", "AWP", "SCAR-20" };
string mapy[13] = { "Dust II", "Mirage", "Vertigo", "Ancient", "Inferno", "Nuke", "Anubis", "Overpass", "Jura", "Grail", "Agency", "Office", "Italy" };

struct Gracz {
    string nazwa;
    string terro_pistolet;
    string ct_pistolet;
    string terro_bron_glowna;
    string ct_bron_glowna;
};

bool in_array(const std::string& value, const std::vector<std::string>& array) {
    return std::find(array.begin(), array.end(), value) != array.end();
}

bool is_integer(const std::string& str) {
    try {
        ilosc_graczy = std::stoi(str);
        return false;
    }
    catch(const std::invalid_argument& e) {
        std::cerr << "podany napis nie jest liczba" << "\n";
        return true;
    }
}

void oddzielnie() {
    srand(time(nullptr));
    do {
        std::cout << "podaj ilosc graczy ";
        std::cin >> str_ilosc_graczy;
    }
    while(is_integer(str_ilosc_graczy));

    std::vector<Gracz> gracze(ilosc_graczy);
	std::cin.ignore();
	
    //losowanie broni dla graczy
    for(int i = 0; i < ilosc_graczy; i++) {
        std::cout << "\npodaj nazwe gracza ";
        
        std::cin.getline(temp_text, dlugosc_nazwy);
        gracze[i].nazwa = (temp_text ? temp_text : "");

        gracze[i].terro_pistolet = terro_pistolety[rand() % 7];
        gracze[i].ct_pistolet = ct_pistolety[rand() % 8];
        gracze[i].terro_bron_glowna = terro_bronie_glowne[rand() % 17];
        gracze[i].ct_bron_glowna = ct_bronie_glowne[rand() % 18];
    }

    std::cout << "\n";

    //wypisywanie
    for(int i = 0; i < ilosc_graczy; i++) {
        std::cout << gracze[i].nazwa << ": \nterro: " << gracze[i].terro_pistolet << ", " << gracze[i].terro_bron_glowna
                                     << "\nct: " << gracze[i].ct_pistolet << ", " << gracze[i].ct_bron_glowna << "\n\n";
    }
    std::cout << mapy[rand() % 12] << "\n";

    std::cout << "Kliknij dowolny klawisz by kontynuowac\n";
    std::cin::ignore();
    std::cin.get();
}

void razem() {
    srand(time(nullptr));
    string los;
    std::vector<string> terro(5);
    std::vector<string> ct(5);

    //losowanie broni dla terro
    terro[0] = terro_pistolety[rand() % 7];
    while(terro[1].empty()) {
        los = terro_pistolety[rand() % 7];
        if(!in_array(los, terro)) {
            terro[1] = los;
        }
    }
    terro[2] = terro_bronie_glowne[rand() % 17];
    while(terro[3].empty() || terro[4].empty()) {
        los = terro_bronie_glowne[rand() % 17];
        if(terro[3].empty() && !in_array(los, terro)) {
            terro[3] = los;
        }
        else if(!in_array(los, terro)) {
            terro[4] = los;
        }
    }

    //losowanie broni dla ct
    ct[0] = ct_pistolety[rand() % 8];
    while(ct[1].empty()) {
        los = ct_pistolety[rand() % 8];
        if(!in_array(los, ct)) {
            ct[1] = los;
        }
    }
    ct[2] = ct_bronie_glowne[rand() % 18];
    while(ct[3].empty() || ct[4].empty()) {
        los = ct_bronie_glowne[rand() % 18];
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
    std::cout << mapy[rand() % 12] << "\n";

    std::cout << "Kliknij dowolny klawisz by kontynuowac\n";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    while(true) {
        std::cout << "wybierz opcje(1 - dla kazdego oddzielnie; 2 - dla wszystkich razem)\n";
        std::cin >> n;

        if(n.compare("1") == 0) {
            oddzielnie();
            return 0;
        }
        else if(n.compare("2") == 0) {
            razem();
            return 0;
        }
        else {
            std::cerr << "nieprawidlowa opcja\n";
        }
    }
}