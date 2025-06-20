
#include <iostream>
#include <sys/stat.h>
#include <filesystem>

void initializeRepo() {
    std::string path = ".minigit";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
        std::filesystem::create_directory(path + "/objects");
        std::filesystem::create_directory(path + "/branches");
        std::filesystem::create_directory(path + "/commits");
        std::ofstream headFile(".minigit/HEAD");
        headFile << "master"; // Default branch
        headFile.close();
        std::cout << "Initialized MiniGit repository!\n";
    } else {
        std::cout << "Repository already exists!\n";
    }
}

int main() {
    initializeRepo();
    return 0;
}

