#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip> // pro std::setprecision
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::map<std::string, std::map<std::string, std::string>> translations = {
        {"en", {{"choose_language", "Choose language: 1 - Czech, 2 - German, 3 - English"},
                {"enter_count", "Enter number of probabilities:"},
                {"enter_prob", "Enter probability #%d (in %%):"},
                {"result", "The probability of all events happening together is:"},
                {"json_saved", "Result saved to result.json"},
                {"invalid_choice", "Invalid choice, defaulting to Czech."}}},
        {"de", {{"choose_language", "Sprache wählen: 1 - Tschechisch, 2 - Deutsch, 3 - Englisch"},
                {"enter_count", "Geben Sie die Anzahl der Wahrscheinlichkeiten ein:"},
                {"enter_prob", "Geben Sie die Wahrscheinlichkeit #%d (in %%):"},
                {"result", "Die Wahrscheinlichkeit, dass alle Ereignisse zusammen eintreten, beträgt:"},
                {"json_saved", "Ergebnis in result.json gespeichert"},
                {"invalid_choice", "Ungültige Auswahl, Standard ist Tschechisch."}}},
        {"cz", {{"choose_language", "Vyber jazyk: 1 - čeština, 2 - němčina, 3 - angličtina"},
                {"enter_count", "Zadej počet pravděpodobností:"},
                {"enter_prob", "Zadej pravděpodobnost č. %d (v %%):"},
                {"result", "Pravděpodobnost, že všechny události nastanou společně, je:"},
                {"json_saved", "Výsledek uložen do result.json"},
                {"invalid_choice", "Neplatná volba, použita čeština."}}}
    };

    std::string lang_code = "cz";
    int lang_choice;
    std::cout << translations["cz"]["choose_language"] << std::endl;
    std::cin >> lang_choice;
    switch(lang_choice) {
        case 1: lang_code = "cz"; break;
        case 2: lang_code = "de"; break;
        case 3: lang_code = "en"; break;
        default:
            std::cout << translations["cz"]["invalid_choice"] << std::endl;
            lang_code = "cz";
            break;
    }

    std::cout << translations[lang_code]["enter_count"] << std::endl;
    int n;
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Invalid number of probabilities." << std::endl;
        return 1;
    }

    std::vector<double> probabilities(n);
    for (int i = 0; i < n; i++) {
        printf((translations[lang_code]["enter_prob"] + "\n").c_str(), i + 1);
        double p;
        std::cin >> p;
        if (p < 0 || p > 100) {
            std::cout << "Probability must be between 0 and 100." << std::endl;
            return 1;
        }
        probabilities[i] = p / 100.0; // převod na desetinné číslo
    }

    double result = 1.0;
    for (auto& p : probabilities) {
        result *= p;
    }

    std::cout << translations[lang_code]["result"] << " " << std::fixed << std::setprecision(6) << (result * 100) << " %" << std::endl;

    json j;
    j["probability_percent"] = result * 100;

    std::ofstream file("result.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        std::cout << translations[lang_code]["json_saved"] << std::endl;
    } else {
        std::cout << "Failed to open result.json for writing." << std::endl;
    }

    return 0;
}
