#pragma once
#include"Blocks.h"
#include <stdlib.h>
#include <vector>
#include <thread>

class Snake { //contains the logic for the snake movement and collision
public:
    std::vector<Block*> blocks; //snake is just an array of blocks

    Snake(float startX, float startZ, int blockCount);
    ~Snake();
    void draw() { //loops through block array and calls their draw functions
        for (int i = 0; i <= blocks.size() - 1; i++) {
            Block* temp = blocks.at(i);
            temp->draw();
        }
    };

    void move(Direction direction); //all snake movement handled in this and pushSnake() function below
 

    void pushSnake(); //doesn't change snake head position but advances all other blocks

    void update() { //update function called at every frame
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //improper fps-capping, will update later
        if (!isUpdated) //если движение еще не было обработано при нажатии клавиши, то обработай его сейчас
            move(currentDirection);
        isUpdated = false;
        collisionDetection();
    };

    void collisionDetection() { //checks if snake head hit fruit or it's own body
        float x = blocks.at(0)->getX();//координаты головы
        float z = blocks.at(0)->getZ();
        if (fruit->getX() == x && fruit->getZ() == z) { //если мы сьели фрукт
            score++; //increment score
            printf("Score = %i\n", score);
            bool repeat = false;
            do { //makes sure that fruit doesn't spawn underneath body
                repeat = false;
                fruit->setX(rand() % 11 - 5);
                fruit->setZ(rand() % 11 - 5);
                for (int i = 0; i <= blocks.size() - 1; i++) {
                    x = blocks.at(i)->getX();
                    z = blocks.at(i)->getZ();
                    if (fruit->getX() == x && fruit->getZ() == z)
                        repeat = true;
                }
            } while (repeat); //(bug) will crash after snake takes up whole grid
            addBlock();
        }
        for (int i = 1; i <= blocks.size() - 1; i++) 
        { //Коллизия с телом.Укусили ли мы себя
            if (blocks.at(i)->getX() == blocks.at(0)->getX() && blocks.at(i)->getZ() == blocks.at(0)->getZ()) 
            {//если таки укусили
                printf("COLLISION\n"); 
                exit(0);
                //blocks.at(i)->setColor(1, 0, 0); //... and collided block turns red.
            }
        }
        /////////////////////////////////////////
            float pred1 = -6;
            float pred2 = 6;
            if (blocks.at(0)->getX()==pred1 || blocks.at(0)->getX() ==pred2)
            {//если таки барьер слева и справа
                printf("WALL\n");
                exit(0);
            }
            else if (blocks.at(0)->getZ() == pred1 || blocks.at(0)->getZ() == pred2 )
            {//если таки барьер сверху и снизу
                printf("WALL\n");
                exit(0);
            }
    };

    void addBlock() { //adds a new block to the snake
        Block* newBlock = new Block(-100, 0, -100);
        blocks.push_back(newBlock);
    };

    Direction getDirection() { return currentDirection; };

private:
    Direction currentDirection;
    bool isUpdated;
    int score;
};
static Snake* snake = new Snake(0, 0, 3);