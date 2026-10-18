#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

struct File {
  std::string name;
  std::string extetion;
  uint64_t    byteSize;
};

std::string getFullFileName(File &f) {
  return f.name + '.' + f.extetion;
}

struct Directory {
  std::string name;
  std::vector<File *> files;
  std::vector<Directory *>dir;

  Directory* up;
};

uint64_t getDirectorySize(Directory &d) {
  uint64_t size = 0;
  for (auto i = 0; i < d.files.size(); i++) {
    size += d.files[i]->byteSize;
  }
  for (auto i = 0; i < d.dir.size(); i++) {
    size += getDirectorySize(*d.dir[i]);
  }
  return size;
}

bool addFile(Directory &d, File &f) {
  for(auto i = 0; i < d.files.size(); i++) {
    if(f.name == d.files[i]->name && f.extetion == d.files[i]->extetion) {
      return false;
    }
  }
  d.files.push_back(&f);
  return true;
}


bool addDir(Directory &d, Directory &dir) {
  for(auto i = 0; i < d.dir.size(); i++) {
    if(dir.name == d.dir[i]->name) {
      return false;
    }
  }
  d.dir.push_back(&dir);
  dir.up = &d;
  return true;
}

void UpFunc(Directory &d) {
  if(d.up) {
    std::cout << d.up->name << '\n';
  }
  else {
    std::cout << "/(root)" << '\n';
  }
}

void ls(Directory &d) {
  std::cout << d.name << '\n';
  for(auto i = 0; i < d.files.size(); i++) {
    std::cout << "  " << getFullFileName(*d.files[i]) << '\n';
  }

  for(auto i = 0; i < d.dir.size(); i++){
    ls(*d.dir[i]);
  }
}
