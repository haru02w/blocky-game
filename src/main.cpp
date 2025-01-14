#include "Game.hpp"
#include <cstdlib>
#include <string>
#include <spdlog/spdlog.h>
#include "TickTime.hpp"
#include "utils/utils.hpp"

int main(int argc, char *argv[])
{
    // spdlog: Set log level
    spdlog::set_level(spdlog::level::debug);

    const std::string &title = utils::getProgramName(argc, argv);
    auto game = Game(title);

    TickTime &time = game.getTickTime().update();
    double lastSecond = time.now();
    for (int i = 0; game.isRunning(); i++) {
        time.update();

        // Run update at fixed timestamps
        if (time.shoudUpdateGame())
            game.update();

        game.render();
        double now = time.now();
        if (now - lastSecond >= 1) {
            spdlog::info("FPS: {}", i);
            i = 0;
            lastSecond = now;
        }
    }

    return EXIT_SUCCESS;
}
