#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Snake.h"

class dieukhien {
public:
    void HandleInput(bool& running, Snake& snake) const;

private:
    void ChangeDirection(Snake& snake, Snake::Direction input,
        Snake::Direction opposite) const;
};

#endif
