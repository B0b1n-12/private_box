
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

double percent_to_probability(double percent) {
    return percent / 100.0;
}

double combined_probability(double a, double b) {
    return a * b;
}

std::map<std::string, std::map<std::string, std::string>> translations = {
    {"cz", {
        {"choose_lang", "Vyber jazyk: 1 - cestina, 2 - nemcina, 3 - anglictina"},
        {"enter_count", "Zadej pocet pravdepodobnosti:"},
        {"enter_probability", "Zadej pravdepodobnost v procentech:"},
        {"result", "Spojena pravdepodobnost je:"}
    }},
    {"de", {
        {"choose_lang", "Waehle die Sprache: 1 - Tschechisch, 2 - Deutsch, 3 - Englisch"},
        {"enter_count", "Gib die Anzahl der Wahrscheinlichkeiten ein:"},
        {"enter_probability", "Gib die Wahrscheinlichkeit in Prozent ein:"},
        {"result", "Die kombinierte Wahrscheinlichkeit ist:"}
    }},
    {"en", {
        {"choose_lang", "Choose language: 1 - Czech, 2 - German, 3 - English"},
        {"enter_count", "Enter the number of probabilities:"},
        {"enter_probability", "Enter the probability in percent:"},
        {"result", "The combined probability is:"}
    }}
};

int main() {
    std::string lang_code = "cz";
    int lang_choice;
    std::cout << translations["cz"]["choose_lang"] << std::endl;
    std::cin >> lang_choice;

    switch(lang_choice) {
        case 1: lang_code = "cz"; break;
        case 2: lang_code = "de"; break;
        case 3: lang_code = "en"; break;
        default: std::cout << "Invalid choice. Defaulting to Czech." << std::endl;
    }

    std::cout << translations[lang_code]["enter_count"] << std::endl;
    int count;
    std::cin >> count;

    double result = 1.0;
    for(int i = 0; i < count; ++i) {
        std::cout << translations[lang_code]["enter_probability"] << " (" << i + 1 << "/" << count << "): ";
        double percent;
        std::cin >> percent;
        result *= percent_to_probability(percent);
    }

    std::cout << translations[lang_code]["result"] << " " << result << std::endl;

    json j;
    j["result"] = result;

    std::ofstream file("result.json");
    file << j.dump(4);
    file.close();

    std::cin.ignore();
    std::cin.get(); // wait for key press
    return 0;
}
