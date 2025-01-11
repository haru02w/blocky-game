#include <fstream>
#include <sstream>
#include <filesystem>
#include "utils.hpp"

namespace fs = std::filesystem;
namespace utils {
std::string getStrFromFile(const fs::path &filepath)
{
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

const std::string getProgramName(int argc, char *argv[])
{

    return argc > 0 ? fs::path(argv[0]).filename() : "blocky-game";
}
}
