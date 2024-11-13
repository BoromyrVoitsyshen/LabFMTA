#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::string filename = "";
    std::cout << "Enter path to input file\n";
    std::cin >> filename;

    std::ifstream inputFile(filename); 
        if (!inputFile.is_open()) {
        std::cerr << "Error, file can't be opened" << std::endl;
        return 1;
    }

    std::cout << "Enter path to output file\n";
    std::cin >> filename;
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error, file can't be opened" << std::endl;
        return 1;
    }

    std::regex pattern(R"(\s*(-?\d+\.\d{2})\s*[\;:\?]\s*(-?\d+\.\d{2})\s*[\;:\?]\s*(\d+)\s*[\;:\?]\s*(\d+)\s*[\;:\?]\s*(-?\d+\.\d{2})\s*[\;:\?]\s*(\d+)\s*[\;:\?]\s*(\d+\.\d)\s*[\;:\?]\s*(\d+\.\d)\s*[\;:\?]\s*(\d{4})\s*[\;:\?]\s*([A-Za-z0-9]{5,11})\s*)");

    std::string line;
    while (std::getline(inputFile, line)) {
        std::smatch match;
        
        if (std::regex_match(line, match, pattern)) {
            int precipitation = std::stoi(match[6].str());
            if (precipitation != 0) {
                outputFile << match[1].str() << " ; " << match[2].str() << " ; "
                           << match[3].str() << " ; " << match[4].str() << " ; "
                           << match[5].str() << " ; " << match[6].str() << " ; "
                           << match[7].str() << " ; " << match[8].str() << " ; "
                           << match[9].str() << " ; " << match[10].str() << "\n";
            }
        }
    }

    inputFile.close(); 
    outputFile.close();

    std::cout << "File " << filename << " was successfully created" << std::endl;    
    return 0;
}
