#include <cstdlib>
#include <string>
#include "Game.hpp"
#include "utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char *argv[])
{
    const std::string &title = utils::getProgramName(argc, argv);
    Game game(title);
    game.run();
    return EXIT_SUCCESS;
}
