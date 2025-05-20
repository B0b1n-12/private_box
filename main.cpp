#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>  // JSON knihovna

using json = nlohmann::json;

int main() {
    // Vytvoření JSON objektu
    json j;

    // Nějaká matematika - třeba spočítáme součet, rozdíl, součin a podíl dvou čísel
    double a = 10.0;
    double b = 3.0;

    double sum = a + b;
    double diff = a - b;
    double prod = a * b;
    double quot = 0.0;
    if (b != 0)
        quot = a / b;
    else
        std::cerr << "Division by zero!" << std::endl;

    // Naplnění JSON objektu výsledky
    j["input"]["a"] = a;
    j["input"]["b"] = b;
    j["results"]["sum"] = sum;
    j["results"]["difference"] = diff;
    j["results"]["product"] = prod;
    j["results"]["quotient"] = quot;

    // Uložení JSON do souboru
    std::ofstream file("results.json");
    if (file.is_open()) {
        file << j.dump(4);  // 4 = odsazení pro lepší čitelnost
        file.close();
        std::cout << "Results saved to results.json\n";
    } else {
        std::cerr << "Could not open file for writing.\n";
    }

    // Vypíšeme JSON na konzoli i pro kontrolu
    std::cout << "JSON output:\n" << j.dump(4) << std::endl;

    // Čekáme na stisk klávesy, aby se okno nezavřelo hned
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
