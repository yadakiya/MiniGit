
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

std::string generateHash(const std::string& data) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(data));  // Simple hash
}

void addFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error: File does not exist!\n";
        return;
    }

    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    file.close();

    std::string fileHash = generateHash(contentStream.str());
    std::ofstream blob(".minigit/objects/" + fileHash + ".txt");
    blob << contentStream.str();
    blob.close();

    std::ofstream indexFile(".minigit/index.txt", std::ios::app);
    indexFile << filename << " " << fileHash << "\n";
    indexFile.close();

    std::cout << "File '" << filename << "' staged!\n";
}