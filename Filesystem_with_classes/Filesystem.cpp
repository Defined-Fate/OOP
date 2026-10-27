#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

struct File {
  private:
    std::string name;
    std::string extention;
    uint64_t     byteSize;
    
  public:
    std::string getFullFileName() {
      return name + '.' + extention;
    }

    uint64_t getbyteSize() {
      return byteSize;
    }

    void setName(const std::string &name){
      this->name = name;
    }

    void setExt(const std::string &ext){
      this->extention = ext;
    }

    void setByteSize(uint64_t n){
      this->byteSize = n;
    }
};

struct Directory {
  private:
    std::string name;
    std::vector<File *> files;
    std::vector<Directory *> dirs;

    Directory* up;
  public:
    void setName(const std::string &name){
      this->name = name;
    }

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

int main (int argc, char *argv[]) {
  File myFile, x, y, z;
  myFile.setName("x");
  myFile.setExt("txt");
  myFile.setByteSize(5345);

  x.setName("x");
  x.setExt("txt");
  x.setByteSize(535432);

  y.setName("y");
  y.setExt("jpeg");
  y.setByteSize(534324);

  z.setName("ZZZ");
  z.setExt("png");
  z.setByteSize(534534);

  Directory myDir, dir1, dir2, dir3;
  myDir.setName("home");
  dir1.setName("docs");
  dir2.setName("rand");
  dir3.setName("docs");

  myDir.addDir(dir1);
  dir1.addDir(dir2);
  myDir.addDir(dir3);

  myDir.addFile(x); 
  dir2.addFile(y); 
  myDir.addFile(myFile);
  dir1.addFile(z);

  myDir.findFile("z");
  myDir.findDir("rand");

  dir1.UpFunc();
  dir2.UpFunc();

  myDir.print();
  return 0;
}
