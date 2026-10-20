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

  for(auto i = 0; i < d.dir.size(); i++) {
    ls(*d.dir[i]);
  }
}

File *findFile(Directory &d, const std::string &name) {
  for(auto i = 0; i < d.files.size(); i++) {
    if(getFullFileName(*d.files[i]) == name) {
      return d.files[i];
    }
  }

  for(auto i = 0; i < d.dir.size(); i++) {
    if(const auto temp = findFile(*d.dir[i], name); temp != nullptr) {
      return temp;
    }
  }
  
  return nullptr;
}

Directory *findDir(Directory &d, const std::string &name) {
  for(auto i = 0; i < d.dir.size(); i++) {
    if(d.dir[i]->name == name) {
      return d.dir[i];
    }
  }

  for(auto i = 0; i < d.dir.size(); i++) {
    if(const auto temp = findDir(*d.dir[i], name); temp != nullptr) {
      return temp;
    }
  }
  
  return nullptr;
}

int main (int argc, char *argv[]) {
  Directory myDir, Documents, Audio, Configs, Configs2;
  myDir.name     = "home";
  Documents.name = "docs";
  Audio.name     = "music";
  Configs.name   = "nvim";
  Configs2.name  = "nvim";

  addDir(myDir, Documents); // ke se dodade vo home.
  addDir(myDir, Audio); 
  addDir(myDir, Configs);
  addDir(myDir, Configs2); // nema da se dodade.

  findDir(myDir, "nvim");

  File x, x1, y, z, nv;
  x.name     = "X";
  x.extetion = "txt";
  x.byteSize = 24;

  x1.name     = "x";
  x1.extetion = "txt";
  x1.byteSize = 24;

  y.name     = "Y";
  y.extetion = "mpv";
  y.byteSize = 1024;

  z.name     = "z";
  z.extetion = "png";
  z.byteSize = 31023;
  
  nv.name     = "nv";
  nv.extetion = "lua";
  nv.byteSize = 1231453;

  addFile(Documents, x);
  addFile(Documents, x1);
  addFile(Audio, y);
  addFile(Configs, z);
  addFile(Configs, nv);

  findFile(Configs, "nv");

  UpFunc(Audio);

  ls(myDir);

  getDirectorySize(myDir);
  return 0;
}
