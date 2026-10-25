#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

struct File {
  private:
    std::string name;
    std::string extention;
    uint8_t     byteSize;
    
  public:
    std::string getFullFileName() {
      return name + '.' + extention;
    }

    uint8_t getbyteSize() {
      return byteSize;
    }
};

struct Directory {
  private:
    std::string name;
    std::vector<File *> files;
    std::vector<Directory *> dirs;

    Directory* up;
  public:

    uint64_t getDirSize(){
      uint64_t size = 0;

      for(auto i = 0; i < files.size(); i++)
        size += files[i]->getbyteSize();
      for(auto i = 0; i < dirs.size(); i++)
        size += dirs[i]->getDirSize();

      return size;
    }

    bool addFile(File &f){
      for(auto i = 0; i < files.size(); i++){
        if(f.getFullFileName() == files[i]->getFullFileName()){
          return false;
        }
      } 
      files.push_back(&f);
      return true;
    }

    bool addDir(Directory &d){
      for(auto i = 0; i < dirs.size(); i++){
        if(dirs[i]->name == d.name){
          return false;
        }
      } 
      d.up = this;
      dirs.push_back(&d);
      return true;
    }
    
    void UpFunc(){
      if(up){
        std::cout << up->name << std::endl;
      } 
      else{
        std::cout << "/(root)" << std::endl;
      }
    }

    File *findFile(const std::string &name){
      for(auto i = 0; i < files.size(); i++){
        if(files[i]->getFullFileName() == name){
          return files[i];
        }
      }
      
      for(auto i = 0; i < dirs.size(); i++){
        if(const auto temp = dirs[i]->findFile(name); temp != nullptr)
          return temp;
      }

      return nullptr;
    }

    Directory *findDir(const std::string &name){
      for(auto i = 0; i < dirs.size(); i++){
        if(dirs[i]->name == name){
          return dirs[i];
        }
      }

      for(auto i = 0; i < dirs.size(); i++){
        if(const auto temp = dirs[i]->findDir(name); temp != nullptr)
          return temp;
      }

      return nullptr;
    }

    void print(){
      std::cout << this->name << std::endl;
      for(auto i = 0; i < files.size(); i++){
        std::cout  << "  "<< files[i]->getFullFileName() << std::endl;
      }

      for(auto i = 0; i < dirs.size(); i++){
        dirs[i]->print();
      }
    }
};
