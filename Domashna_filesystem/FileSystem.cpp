#include <cstdint>
#include <string>
#include <vector>
struct File {
  std::string name;
  std::string extetion;
  uint64_t    byteSize;
};

std::string getFullFileName (File &f) {
  return f.name + '.' + f.extetion;
}

struct Directory {
  std::string name;
  std::vector<File *> files;
  std::vector<Directory *>dir;

  Directory* up;
};

uint64_t getDirectorySize(Directory &d){
  uint64_t size = 0;
  for(int i = 0; i < d.files.size(); i++){
    size += d.files[i]->byteSize;
  }
  for(int i = 0; i < d.dir.size(); i++){
    size += getDirectorySize(*d.dir[i]);
  }
  return size;
}
