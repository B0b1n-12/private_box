
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void print_menu() {
    std::cout << "Vyber jazyk / Sprache waehlen / Choose language:\n";
    std::cout << "1 - Cesky\n2 - Deutsch\n3 - English\n";
    std::cout << "Tva volba / Deine Wahl / Your choice: ";
}

int main() {
    int lang = 0;
    print_menu();
    std::cin >> lang;

    std::string prompt_count, prompt_prob, error_input, output_message;

    switch (lang) {
        case 1:
            prompt_count = "Zadej pocet pravdepodobnosti:";
            prompt_prob = "Zadej pravdepodobnost v procentech (0-100):";
            error_input = "Neplatny vstup. Zadej cislo mezi 0 a 100.";
            output_message = "Vysledek ulozen do result.json";
            break;
        case 2:
            prompt_count = "Gib die Anzahl der Wahrscheinlichkeiten ein:";
            prompt_prob = "Gib eine Wahrscheinlichkeit in Prozent ein (0-100):";
            error_input = "Ungueltige Eingabe. Bitte eine Zahl zwischen 0 und 100 eingeben.";
            output_message = "Ergebnis in result.json gespeichert.";
            break;
        case 3:
            prompt_count = "Enter the number of probabilities:";
            prompt_prob = "Enter a probability in percent (0-100):";
            error_input = "Invalid input. Please enter a number between 0 and 100.";
            output_message = "Result saved in result.json";
            break;
        default:
            std::cerr << "Neplatna volba jazyka. Program bude ukoncen." << std::endl;
            return 1;
    }

    int count;
    std::cout << prompt_count << std::endl;
    std::cin >> count;

    if (count <= 0) {
        std::cerr << error_input << std::endl;
        return 1;
    }

    std::vector<double> probabilities;
    for (int i = 0; i < count; ++i) {
        double p;
        std::cout << prompt_prob << std::endl;
        std::cin >> p;
        if (p < 0 || p > 100) {
            std::cerr << error_input << std::endl;
            return 1;
        }
        probabilities.push_back(p / 100.0);
    }

    double combined = 1.0;
    for (double p : probabilities) {
        combined *= p;
    }

    json result;
    result["combined_probability"] = combined;

    std::ofstream file("result.json");
    if (!file) {
        std::cerr << "Chyba pri otevirani souboru result.json" << std::endl;
        return 1;
    }
    file << result.dump(4);
    file.close();

    std::cout << output_message << std::endl;
    return 0;
}
