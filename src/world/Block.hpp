#pragma once

class Block {
public:
    // typedef
    enum class Face {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
    };

    enum class Type {
        AIR,
        STONE,
    };

    Type id;
    bool active;
};
