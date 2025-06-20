
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const string COMMITS_DIR = "commits"; // Define the directory where commit files are stored
const string BRANCHES_FILE = "branches.txt"; // Define the file where branch information is stored

// Dummy implementation for getBranchCommit
string getBranchCommit(const string& branchName) {
	// TODO: Replace with actual logic to retrieve commit hash for a branch
	return "dummy_commit_hash";
}

// Dummy implementation for getHeadBranch
string getHeadBranch() {
	// TODO: Replace with actual logic to retrieve the current branch name
	return "main";
}

void log() { // log function is used to display the commit history 
string current = getBranchCommit(getHeadBranch());// to find out commit hash where current branch is pointing
while (current != "null") {//Keep looping until there's no parent commit left
ifstream in(COMMITS_DIR + "/" + current);Open the commit file for the current commit hash//Open the commit file for the current commit hash
string line;
cout << "Commit: " << current << endl;
while (getline(in, line)) {
if (line.rfind("msg:", 0) == 0 || line.rfind("time:", 0) == 0 || line.rfind("parent:", 0) == 0)
cout << line << endl;
}//Read each line of the commit file and display the message, timestamp, or parent commit, if found.
cout << "-----------------------\n";//Print a divider between commits for clarity.

in.clear();//the two lines of code are used to Clear any read errors and rewind the file pointer to the start of the commit file.
in.seekg(0);
while (getline(in, line)) {
if (line.rfind("parent:", 0) == 0) {
current = line.substr(7);
break;
}
}
}
}

void branch(const string& name) {//This function makes a new branch with a given name.
string current = getBranchCommit(getHeadBranch());//Figure out where the current branch is pointing
ofstream out(BRANCHES_FILE, ios::app);//Open the file that tracks branches, and set it to add to the end without deleting existing data.
out << name << ":" << current << endl;//Save the new branch name and what commit it's pointing to
cout << "Branch created: " << name << endl;//Confirm to the user that the new branch has been made
}