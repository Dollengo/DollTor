#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

std::string tempDir = "../temp/";

void clearInputBuffer() {
    std::cin.ignore(32767, '\n');
}

void runCppCode(const std::string& code) {
    std::string tempFile = tempDir + "temp.cpp";
    std::ofstream file(tempFile);
    file << code;
    file.close();
    std::string command = "g++ -o " + tempDir + "temp " + tempFile + " && " + tempDir + "./temp";
    std::cout << "Running C++ code..." << std::endl;
    std::system(command.c_str());
}

void runPythonCode(const std::string& code) {
    std::string tempFile = tempDir + "temp.py";
    std::ofstream file(tempFile);
    file << code;
    file.close();
    std::string command = "python3 " + tempFile;
    std::cout << "Running Python code..." << std::endl;
    std::system(command.c_str());
}

void saveFile(const std::vector<std::string>& lines) {
    std::string filename;
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        std::cerr << "Error getting current directory" << std::endl;
        return;
    }

    std::cout << "Enter file name to save: ";
    std::getline(std::cin, filename);
    
    std::string filePath = std::string(cwd) + "/" + filename;
    
    std::ofstream file(filePath);
    for (const auto& l : lines) {
        file << l << std::endl;
    }
    
    file.close();
    std::cout << "File saved as " << filePath << std::endl;
}

void cleanupTempFiles() {
    if (fs::exists(tempDir)) {
        for (const auto& entry : fs::directory_iterator(tempDir)) {
            fs::remove(entry.path());
        }
        fs::remove(tempDir);
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> lines;
    std::string line;
    std::string filename;
    bool fileOpened = false;
    
    // Verifica se um arquivo foi passado como argumento
    if (argc > 1) {
        filename = argv[1];
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string fileLine;
            while (std::getline(file, fileLine)) {
                lines.push_back(fileLine);
            }
            file.close();
            fileOpened = true;
        } else {
            std::cout << "Unable to open file: " << filename << std::endl;
            return 1;
        }
    }
    
    std::cout << "Welcome to DollTor, your favorite text editor!" << std::endl;
    if (fileOpened) {
        std::cout << filename << std::endl;
    } else {
        std::cout << "NONE" << std::endl;
    }
    
    // Preenche o vetor de linhas com as linhas do arquivo, se houver
    int lineNumber = 1;
    for (const auto& l : lines) {
        std::cout << lineNumber << " > " << l << std::endl;
        ++lineNumber;
    }
    
    // Loop principal do editor
    while (true) {
        if (filename.empty()) {
            std::cout << lines.size() + 1 << " > ";
        } else {
            std::cout << lines.size() + 1 << " > ";
        }
        
        std::getline(std::cin, line);
        
        if (line == ":q") {
            std::string answer;
            std::cout << "Are you sure you want to quit? (y/n): ";
            std::getline(std::cin, answer);
            
            if (answer == "y" || answer == "Y") {
                break;
            } else {
                continue;
            }
        }
        else if (line == ":h") {
            std::cout << "Commands available:" << std::endl;
            std::cout << ":q        - Quit the editor" << std::endl;
            std::cout << ":w        - Save and delete this part of the code that has :w" << std::endl;
            std::cout << ":h        - Show all commands" << std::endl;
            std::cout << ":b <num>  - Go back <num> lines" << std::endl;
            std::cout << ":p        - Print all entered lines" << std::endl;
            std::cout << ":r cpp    - Run the code as C++" << std::endl;
            std::cout << ":r python - Run the code as Python" << std::endl;
            continue;
        }
        else if (line.find(":b") == 0) {
            std::istringstream iss(line);
            std::string cmd;
            int numLines = 1;
            iss >> cmd >> numLines;
            
            lines.resize(lines.size() - numLines);
            continue;
        }
        else if (line.find(":w") != std::string::npos) {
            saveFile(lines);
            lines.erase(lines.begin() + line.find(":w") / 2);
            continue;
        }
        else if (line.find(":r") == 0) {
            std::istringstream iss(line);
            std::string cmd, lang;
            iss >> cmd >> lang;
            
            std::string fullCode;
            for (const auto& l : lines) {
                fullCode += l + "\n";
            }
            
            if (lang == "cpp") {
                runCppCode(fullCode);
            } else if (lang == "python") {
                runPythonCode(fullCode);
            } else {
                std::cout << "Language not supported." << std::endl;
            }
            continue;
        }
        
        lines.push_back(line);
    }
    
    cleanupTempFiles();
    std::cout << "Exiting DollTor. Goodbye!" << std::endl;
    return 0;
}
