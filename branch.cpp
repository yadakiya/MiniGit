void log() {
string current = getBranchCommit(getHeadBranch());
while (current != "null") {
ifstream in(COMMITS_DIR + "/" + current);
string line;
cout << "Commit: " << current << endl;
while (getline(in, line)) {
if (line.rfind("msg:", 0) == 0 || line.rfind("time:", 0) == 0 || line.rfind("parent:", 0) == 0)
cout << line << endl;
}
cout << "-----------------------\n";

in.clear();
in.seekg(0);
while (getline(in, line)) {
if (line.rfind("parent:", 0) == 0) {
current = line.substr(7);
break;
}
}
}
}

void branch(const string& name) {
string current = getBranchCommit(getHeadBranch());
ofstream out(BRANCHES_FILE, ios::app);
out << name << ":" << current << endl;
cout << "Branch created: " << name << endl;
}
