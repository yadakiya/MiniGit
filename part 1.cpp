#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

const string ROOT          = ".minigit";
const string OBJECTS_DIR   = ROOT + "/objects";
const string COMMITS_DIR   = ROOT + "/commits";
const string HEAD_FILE     = ROOT + "/HEAD.txt";
const string INDEX_FILE    = ROOT + "/index.txt";
const string BRANCHES_FILE = ROOT + "/branches.txt";

void init() {
    if (fs::exists(ROOT)) {
        cout << "MiniGit already initialized.\n";
        return;
    }

    fs::create_directory(ROOT);
    fs::create_directory(OBJECTS_DIR);
    fs::create_directory(COMMITS_DIR);

    ofstream(HEAD_FILE)     << "main\n";
    ofstream(BRANCHES_FILE) << "main:null\n";
    ofstream(INDEX_FILE);  

    cout << "MiniGit repository initialized!\n";
}

int main() {
    init();
    return 0;
}
