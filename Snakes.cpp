#include"Snakes.h"

Snake::Snake(float startX, float startZ, int blockCount)
{
    for (float i = 0; i < blockCount; i++) {
        Block* temp = new Block(startX + i, 0, startZ);
        if (i == 0)
            temp->setColor(0, 1, 0); //snake head is set to green color
        blocks.push_back(temp);
    }
    isUpdated = false;
    currentDirection = D_LEFT;
    score = 0;
}

void Snake::move(Direction direction)
{
    Block* snakeHead = blocks.at(0);//создаём голову змеи и ложим туда первый элемент 
    if (direction == D_LEFT && currentDirection != D_RIGHT) {
        pushSnake();
        snakeHead->setX(snakeHead->getX() - 1.0f);//переставили голову
        currentDirection = direction;
        isUpdated = true;
    }
    else if (direction == D_RIGHT && currentDirection != D_LEFT) {
        pushSnake();
        snakeHead->setX(snakeHead->getX() + 1.0f);
        currentDirection = direction;
        isUpdated = true;
    }
    else if (direction == D_UP && currentDirection != D_DOWN) {
        pushSnake();
        snakeHead->setZ(snakeHead->getZ() + 1.0f);
        currentDirection = direction;
        isUpdated = true;
    }
    else if (direction == D_DOWN && currentDirection != D_UP) {
        pushSnake();
        snakeHead->setZ(snakeHead->getZ() - 1.0f);
        currentDirection = direction;
        isUpdated = true;
    }
}

void Snake::pushSnake()
{
    for (int i = blocks.size() - 1; i >= 1; i--) {
        Block* temp = blocks.at(i);//получает координаты блока который ближе к голове змеи
        Block* prevBlock = blocks.at(i - 1);
        temp->setX(prevBlock->getX());
        temp->setZ(prevBlock->getZ());
    }
}
