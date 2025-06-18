#include<iostream>
#include<filesystem>
#include<string>
 namespace fs=std::filesystem;
  int main(int argc,char* argv[]){
    if(argc <2 || std::string(argv[1]) !="init"){
        std::cout <<"usage : minigit <command>[args]\n";
       std::cout <<"Available command : init \n ";
        return 1;

    }
    std::string minigitDir=".minigit";

    if (fs :: exists(minigitDir)){
        std::cout<<"ERROR: .minigit ALREADY EXIT.\n";
        return 1;

    }
    try{
        fs::create_directory(minigitDir);
        fs::create_directory(minigitDir + "/objects");
        fs::create_directory(minigitDir + "/refs");
        fs::create_directory(minigitDir +"/refs/heads");
        std::cout <<"Initialized empty MiniGit Repository in "<<minigitDir <<"\n";
    }catch(const fs ::filesystem_error& e){
        std::cout<<"ERROR CREATING DIRECTORY: "<<e.what()<<"\n";
        return 1;
    }
    return 0;
  }