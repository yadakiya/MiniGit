// code for the Commit (commit -m <message>) 
// Save a snapshot of the current file versions. 
// Store commit objects with: 
// Metadata: timestamp, message, parent commit hash 
// Pointers to file blobs 
//Update the HEAD pointer to the new commit.

void commit(const string& message) {
    ifstream indexIn(INDEX_FILE);
    stringstream files;
    string line;
    while (getline(indexIn, line)) {
        files << line << endl;
    }

    string timestamp = currentTime();
    string branch = getHeadBranch();
    string parent = getBranchCommit(branch);

    string metadata = "msg:" + message + "\n" +
                      "time:" + timestamp +
                      "parent:" + parent + "\n" +
                      "branch:" + branch + "\n";

    string commitHash = generateHash(metadata + files.str());
    ofstream commitFile(COMMITS_DIR + "/" + commitHash);
    commitFile << metadata << files.str();

    updateBranch(branch, commitHash);
    ofstream(INDEX_FILE);
    cout << "Committed. Hash: " << commitHash << endl;
}
