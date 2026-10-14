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
};
