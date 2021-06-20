#include "file_util.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string getFileContent(const std::string& file_path, bool throws) {
  std::ifstream inFile(file_path);
  if (!inFile.is_open()) {
    std::string error = "Unable to open file: " + file_path + "!";
    if (throws) {
      throw std::runtime_error(error);
    } else {
      std::cerr << error << '\n';
    }
  }

  std::ostringstream stream;
  stream << inFile.rdbuf();
  return stream.str();
}
