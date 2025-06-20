#include <string>//for string manupulation
#include <fstream>//to read and write files
#include <iostream>//for input and also the output operations
#include <sstream>//to work with this string stream

#ifdef _WIN32/*these 5 lines are used to define correct path separators*/
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif
using namespace std;

const string OBJECTS_DIR = "objects"; // Define the directory for storing blobs
const string INDEX_FILE = "index.txt"; // Define the index file name

// Simple hash function for demonstration purposes
string hashStr(const std::string& input) {//it uses std::hash to convert the string to a hash value then converts to hexadecimal string so its readable and filename same and friendly
    hash<std::string> hasher;
    size_t hashValue = hasher(input);
    ostringstream oss;
    oss << std::hex << hashValue;
    return oss.str();
}

void addFile(const std::string& filename)
{
    ifstream file(filename);//trying to open the file if it exists
    if (!file)
    {
        std::cout << "Error: File does not exist!\n";
        return;
    }
//used to read the file content 
    ostringstream contentStream;// creates an output string to store file content
    contentStream << file.rdbuf();//streams the entire file into contentStream
    file.close();//this line of code used to close the file when reading is done
// to generate unique hash
    string fileHash = hashStr(contentStream.str());//hashes the content to generate unique ID
//used to store the content as a blob
    ofstream blob(OBJECTS_DIR + PATH_SEP + fileHash + ".txt");//creates a new file in the objects directory with the hash as the filename
    blob << contentStream.str();//to write the file content into the blob file
    blob.close();
//to update the index file with the new blob
    ofstream indexFile(INDEX_FILE, ios::app);//opens the index file in append mode and appends the file's name and its content hash
    indexFile << filename << ":" << fileHash << "\n";
    indexFile.close();

    cout << "File '" << filename << "' staged!\n";
}
