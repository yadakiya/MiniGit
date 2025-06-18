/********************************************************************
 * MiniGit – ultra-tiny VCS demo (GCC 6 / C++14 compliant)
 *******************************************************************/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <ctime>
#include <string>
#include <sys/stat.h>   // POSIX  mkdir
#include <sys/types.h>
#include <cerrno>

#ifdef _WIN32
#  include <direct.h>   // _mkdir
#  define PLATFORM_MKDIR(path)  _mkdir(path)
#  define PATH_SEP              "\\"
#else
#  include <unistd.h>
#  define PLATFORM_MKDIR(path)  mkdir(path, 0755)
#  define PATH_SEP              "/"
#endif

using namespace std;

/*–––––––––––––––––––––––––––––––––  tiny helpers  –––––––––––––––––––––––––––*/
static bool ensureDir(const string& path)
{
    if (PLATFORM_MKDIR(path.c_str()) == 0 || errno == EEXIST)
        return true;
    perror(("mkdir " + path).c_str());
    return false;
}

inline string hashStr(const string& s) { return to_string(hash<string>{}(s)); }

inline string now()
{
    time_t t = time(nullptr);
    char buf[32] = {0};
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return string(buf);
}

/*––––––––––––  repo paths –––––––––––––*/
const string ROOT          = ".minigit";
const string OBJECTS_DIR   = ROOT + PATH_SEP + "objects";
const string COMMITS_DIR   = ROOT + PATH_SEP + "commits";
const string HEAD_FILE     = ROOT + PATH_SEP + "HEAD.txt";
const string INDEX_FILE    = ROOT + PATH_SEP + "index.txt";
const string BRANCHES_FILE = ROOT + PATH_SEP + "branches.txt";

/* forward decls */
void updateBranchHead(const string&, const string&);
void commit(const string&);

/*––––––––––––  getters –––––––––––––*/
string currentBranch()
{
    ifstream f(HEAD_FILE);
    string b; getline(f,b);
    return b.empty() ? "main" : b;
}

string branchHead(const string& branch)
{
    ifstream f(BRANCHES_FILE);
    string line;
    while (getline(f,line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos && line.substr(0,pos) == branch)
            return line.substr(pos+1);
    }
    return "null";
}

string findLCA(string a, string b)
{
    unordered_set<string> seen;

    auto parentOf = [](const string& h)->string
    {
        ifstream f(COMMITS_DIR + PATH_SEP + h);
        string l;
        while (getline(f,l))
            if (l.rfind("parent:",0) == 0) return l.substr(7);
        return "null";
    };

    while (a != "null") { seen.insert(a); a = parentOf(a); }
    while (b != "null") { if (seen.count(b)) return b; b = parentOf(b); }
    return "null";
}

/*––––––––––––  repo-level ops –––––––––––––*/
void init()
{
    if (access(ROOT.c_str(), F_OK) == 0) return;          // already initialised
    ensureDir(ROOT);
    ensureDir(OBJECTS_DIR);
    ensureDir(COMMITS_DIR);

    ofstream(HEAD_FILE)      << "main\n";
    ofstream(BRANCHES_FILE)  << "main:null\n";
    ofstream(INDEX_FILE);                                    // empty index
}

void updateBranchHead(const string& br, const string& hash)
{
    ifstream  in (BRANCHES_FILE);
    stringstream out;
    string line; bool found=false;

    while (getline(in,line))
    {
        size_t pos = line.find(':');
        if (pos != string::npos && line.substr(0,pos) == br) {
            out << br << ':' << hash << '\n';
            found = true;
        } else {
            out << line << '\n';
        }
    }
    if (!found) out << br << ':' << hash << '\n';

    ofstream(BRANCHES_FILE) << out.str();
}

void commit(const string& msg)
{
    ifstream idx(INDEX_FILE);
    if (!idx) return;                         // nothing staged

    stringstream body; string l;
    while (getline(idx,l)) body << l << '\n';

    string meta =
        "message:"   + msg            + '\n' +
        "timestamp:" + now()          + '\n' +
        "parent:"    + branchHead(currentBranch()) + '\n' +
        "branch:"    + currentBranch()             + '\n';

    string h = hashStr(meta + body.str());

    ofstream(COMMITS_DIR + PATH_SEP + h) << meta << body.str();
    updateBranchHead(currentBranch(), h);

    ofstream(INDEX_FILE);                       // clear staging
}

void merge(const string& target)
{
    const string selfHead   = branchHead(currentBranch());
    const string targetHead = branchHead(target);
    if (targetHead == "null") return;

    (void)findLCA(selfHead,targetHead);        // lca not used yet

    unordered_map<string,string> merged;

    auto harvest = [&](const string& hash)
    {
        ifstream f(COMMITS_DIR + PATH_SEP + hash);
        string l;
        while (getline(f,l))
        {
            if (l.find(':') != string::npos &&
                l.rfind("message:",0)   && l.rfind("timestamp:",0) &&
                l.rfind("parent:",0)    && l.rfind("branch:",0))
            {
                size_t pos = l.find(':');
                merged[l.substr(0,pos)] = l.substr(pos+1);
            }
        }
    };
    harvest(targetHead);
    harvest(selfHead);

    ofstream idx(INDEX_FILE);
    for (unordered_map<string,string>::const_iterator it = merged.begin();
         it != merged.end(); ++it)
        idx << it->first << ':' << it->second << '\n';

    commit("Merged branch " + target);
}

/*––––––––––––  main –––––––––––––*/
int main()
{
    init();
    /* Stage a file by writing "path:hash" lines into .minigit/index.txt
       then call commit("msg") or merge("branch") from here. */
    return 0;
}
