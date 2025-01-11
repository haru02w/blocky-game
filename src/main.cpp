#include <cstdlib>
#include <string>
#include "TickTime.hpp"
#include "Game.hpp"
#include "spdlog/spdlog.h"
#include "utils/utils.hpp"

int main(int argc, char *argv[])
{
    // spdlog: Set log level
    spdlog::set_level(spdlog::level::debug);

    const std::string &title = utils::getProgramName(argc, argv);
    auto game = Game(title);

    int i = 0;
    while (game.isRunning()) {
        TickTime &time = game.getTickTime().update();

        // Run update at fixed timestamps
        if (time.shoudUpdateGame())
            game.update();
        

        game.render();
    }

    return EXIT_SUCCESS;
}
