#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void print_menu() {
    std::cout << "Waehle Sprache / Choose language / Vyber jazyk:\n";
    std::cout << "1 - Deutsch\n2 - English\n3 - Cesky\n";
    std::cout << "Deine Wahl / Your choice / Tva volba: ";
}


int main() {
    int lang;
    print_menu();
    std::cin >> lang;

    // Texty v jednotlivych jazycich
    std::string prompt_prob, prompt_count, error_input, output_message;

    if(lang == 1) {
        prompt_count = "Gib die Anzahl der Wahrscheinlichkeiten ein:";
        prompt_prob = "Gib eine Wahrscheinlichkeit in Prozent ein (0-100):";
        error_input = "Ungueltige Eingabe. Bitte eine Zahl zwischen 0 und 100 eingeben.";
        output_message = "Berechnung abgeschlossen. Ergebnis gespeichert in result.json";
    } else if(lang == 2) {
        prompt_count = "Enter the number of probabilities:";
        prompt_prob = "Enter a probability in percent (0-100):";
        error_input = "Invalid input. Please enter a number between 0 and 100.";
        output_message = "Calculation finished. Result saved in result.json";
    } else {
        prompt_count = "Zadej pocet pravdepodobnosti:";
        prompt_prob = "Zadej pravdepodobnost v procentech (0-100):";
        error_input = "Neplatny vstup. Zadej cislo mezi 0 a 100.";
        output_message = "Vypocet hotov. Vysledek ulozen v result.json";
    }

    int count;
    std::cout << prompt_count << std::endl;
    std::cin >> count;

    if(count <= 0) {
        std::cerr << error_input << std::endl;
        return 1;
    }

    std::vector<double> probabilities;
    for(int i = 0; i < count; ++i) {
        double p;
        std::cout << prompt_prob << " [" << i+1 << "]: ";
        std::cin >> p;
        if(std::cin.fail() || p < 0 || p > 100) {
            std::cerr << error_input << std::endl;
            return 1;
        }
        probabilities.push_back(p / 100.0); // Prevod na 0-1
    }

    // Vypocet pravdepodobnosti splneni vsech (pro jednoduchost soucin)
    double result = 1.0;
    for(double p : probabilities) {
        result *= p;
    }

    // Vytvoreni JSONu
    json j;
    j["probabilities_percent"] = probabilities;
    j["result_probability"] = result;

    // Ulozeni do souboru
    std::ofstream file("result.json");
    if(!file.is_open()) {
        std::cerr << "Chyba pri zapisovani do souboru." << std::endl;
        return 1;
    }
    file << j.dump(4);
    file.close();

    std::cout << output_message << std::endl;

    return 0;
}
