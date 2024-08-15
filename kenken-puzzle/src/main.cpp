/*
 * Copyright (c) 2024 Xephyanth (Egor M.)
 * All rights reserved
 */

#include "Board.h"
#include "FieldGenerator.h"

int main() {
    int size = 6;
    int diff = 2;

    FieldGenerator generator(diff);

    Board board = generator.generateField(size);

    board.displayBoard();

    return 0;
}