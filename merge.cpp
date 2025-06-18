void mergeBranch(const string& target) {
    string currentCommit = getCommitFromBranch(getCurrentBranch());
    string targetCommit = getCommitFromBranch(target);

    string baseCommit = findLCA(currentCommit, targetCommit);
    if (baseCommit == "null") {
        cout << "No common ancestor found for merge.\n";
        return;
    }

    ifstream baseFile(COMMITS + "/" + baseCommit);
    ifstream currentFile(COMMITS + "/" + currentCommit);
    ifstream targetFile(COMMITS + "/" + targetCommit);

    unordered_map<string, string> baseMap, currentMap, targetMap;
    string line;

    while (getline(baseFile, line))
        if (line.find(":") != string::npos && !line.starts_with("msg:") && !line.starts_with("time:") && !line.starts_with("parent:"))
            baseMap[line.substr(0, line.find(":"))] = line.substr(line.find(":") + 1);

    while (getline(currentFile, line))
        if (line.find(":") != string::npos && !line.starts_with("msg:") && !line.starts_with("time:") && !line.starts_with("parent:"))
            currentMap[line.substr(0, line.find(":"))] = line.substr(line.find(":") + 1);

    while (getline(targetFile, line))
        if (line.find(":") != string::npos && !line.starts_with("msg:") && !line.starts_with("time:") && !line.starts_with("parent:"))
            targetMap[line.substr(0, line.find(":"))] = line.substr(line.find(":") + 1);

    unordered_map<string, string> result;
    unordered_set<string> allFiles;
    for (auto& [k, _] : baseMap) allFiles.insert(k);
    for (auto& [k, _] : currentMap) allFiles.insert(k);
    for (auto& [k, _] : targetMap) allFiles.insert(k);

    for (const auto& file : allFiles) {
        string base = baseMap[file];
        string cur = currentMap[file];
        string tgt = targetMap[file];

        if (cur == tgt) result[file] = cur;
        else if (base == cur) result[file] = tgt;
        else if (base == tgt) result[file] = cur;
        else {
            cout << "CONFLICT: both modified " << file << endl;
            result[file] = cur;
        }
    }

    ofstream indexOut(INDEX);
    for (auto& pair : result)
        indexOut << pair.first << ":" << pair.second << endl;

    saveCommit("Merged branch " + target);
}