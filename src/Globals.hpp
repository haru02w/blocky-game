#pragma once
#include "State.hpp"
#include "events/EventManager.hpp"
#include <filesystem>

namespace fs = std::filesystem;

extern fs::path SHADER_PATH;
extern fs::path TEX_PATH;

struct Globals {
    EventManager eventManager;
    State state;
};
extern Globals globals;
