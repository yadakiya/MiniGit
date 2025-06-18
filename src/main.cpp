#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>
namespace fs=std::filesystem;
 size_t simpleHash(const std::string& content){ // hash function
    size_t hash=0;
    for(char c: content){
        hash +=static_cast<size_t>(c);
    }
    return hash;
 }
  int main(int argc,char* argv[]){
    if(argc <2){
        std::cout<<"usage: minigit <command>[args]\n";
       std::cout <<"Available command : init, add\n ";
        return 1;

    }

    std :: string command=argv[1];
    if(command =="init"){
        std :: string minigitDir=".minigit";

    if (fs :: exists(minigitDir)){
        std::cout<<"ERROR: .minigit already exists.\n";
        return 1;
    }

    try  {
        fs::create_directory(minigitDir);
        fs::create_directory(minigitDir + "/objects");
        fs::create_directory(minigitDir + "/refs");
        fs::create_directory(minigitDir +"/refs/heads");
        std::cout <<"Initialized empty MiniGit Repository in "<< minigitDir <<"\n";
    }catch(const fs ::filesystem_error& e){
        std::cout<<"ERROR CREATING DIRECTORY: "<<e.what()<<"\n";
        return 1;
    }
} 
else if(command =="add"){
    if(argc < 3){
        std::cout <<"usage: minigit add <filename>\n";
        return 1;
    }
    std::string filename =argv[2];
    std ::string minigitDir=".minigit";

    if(!fs::exists(minigitDir)){
    std::cout <<"error : .minigit does not exist. run 'minigit init' first. \n";
    return 1;
}
   if (!fs::exists(filename)){
    std::cout<<"error: file' "<< filename<<"' does not exist.\n ";
    return 1;
}
std::ifstream file(filename);
if(!file.is_open()){
    std::cout <<"error : could not open the file ' "<<filename <<" '\n";
    return 1;
}
std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
file.close();


size_t hash=simpleHash(content);
std::string blobPath=minigitDir +"/objects/" + std::to_string(hash);
std::ofstream blobFile(blobPath);
if(!blobFile.is_open()){
   std::cout<< " error : could not creat blob file ' " << blobPath<<"' \n";
   return 1;
}else {

 blobFile<< content ;
 blobFile.close();
  std::cout<< "Added file ' "<<filename<<" ' with hash "<<hash << "\n";
}
} else {
    std::cout<< "error: unknown command ' "<< command<<" '\n";
    std::cout<<"available command: init , add \n";
    return 1;
}
   return 0;
}