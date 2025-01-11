#pragma once

#include <string>
#include <filesystem>
namespace fs = std::filesystem;
namespace utils {
std::string getStrFromFile(const fs::path &filepath);

const std::string getProgramName(int argc, char *argv[]);
}
