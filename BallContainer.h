#ifndef BALLCONTAINER_H
#define BALLCONTAINER_H
#include <vector>
#include "Ball.h"
#include "Screen.h"
#include <iostream>
#include <cmath>

struct Line
{
    float x1;
    float y1;
    float x2;
    float y2;
};

class BallContainer
{
private:
    std::vector<Ball> allBalls;
    std::vector<Line> lines;

public:
    BallContainer()
    {
        allBalls.push_back(createRandomBall());
    };

    Ball createRandomBall()
    {
        int size = rand() % 100 + 50;
        int r = (rand() % 2) * 200;
        int g = (rand() % 2) * 200;
        int b = (rand() % 2) * 200;
        Ball ball(size, 500 - size / 2.0, 0, r, g, b);
        return ball;
    }
    void present(SDL_Renderer *renderer)
    {
        for (int i = 0; i < allBalls.size(); i++)
        {
            Ball &curBall = allBalls[i];
            if (curBall.isFree)
            {
                curBall.move();
            }
            else
            {
                continue;
            }
            if (curBall.y + curBall.size >= 600)
            {
                // check hit floor
                curBall.setY(600 - curBall.size);
                if (curBall.velvec.y < 50)
                {
                    curBall.onGround = true;
                    curBall.velvec.y = 0;
                }
                VelocityVector vec;
                vec.x = 0;
                vec.y = (-curBall.velvec.y * 0.5);
                curBall.velvec.y = 0;
                curBall.addVec(vec);
            }
            if (curBall.x + curBall.size >= 1000)
            {
                // check hit floor
                curBall.setX(1000 - curBall.size);
                VelocityVector vec;
                vec.y = 0;
                vec.x = -abs(curBall.velvec.x * 0.5);
                curBall.velvec.x = 0;
                curBall.addVec(vec);
            }
            if (curBall.x <= 0)
            {
                // check hit floor
                curBall.setX(0);
                VelocityVector vec;
                vec.y = 0;
                vec.x = -(curBall.velvec.x * 0.5);
                curBall.velvec.x = 0;
                curBall.addVec(vec);
            }
            if (curBall.y <= 0)
            {
                // check hit floor
                curBall.setY(0);
                VelocityVector vec;
                vec.y = -(curBall.velvec.y);
                vec.x = 0;
                curBall.velvec.y = 0;
                curBall.addVec(vec);
            }
            for (int j = i + 1; j < allBalls.size(); j++)
            {
                // check collisions // needs fixed
                Ball &otherBall = allBalls[j];
                double minDistanceRequired = curBall.radius + otherBall.radius;
                double distance = sqrt(pow((curBall.centerX - otherBall.centerX), 2) + pow((curBall.centerY - otherBall.centerY), 2));
                if (distance <= minDistanceRequired)
                {
                    float collisionWidth = (curBall.centerX - otherBall.centerX);
                    float collisionHeight = (curBall.centerY - otherBall.centerY);
                    float totalMomentum = abs(curBall.velvec.x) + abs(curBall.velvec.y) + abs(otherBall.velvec.x) + abs(otherBall.velvec.y);
                    float ratio = totalMomentum / minDistanceRequired * 0.5;
                    VelocityVector collisionVector = {collisionWidth * ratio, collisionHeight * ratio};
                    VelocityVector otherCollisionVector = {-collisionWidth * ratio, -collisionHeight * ratio};
                    if (curBall.onGround)
                    {
                        collisionVector.y = 0;
                        otherBall.velvec.y = 0;
                    }
                    if (otherBall.onGround)
                    {
                        otherCollisionVector.y = 0;
                        curBall.velvec.y = 0;
                    }
                    curBall.addVec(collisionVector);
                    otherBall.addVec(otherCollisionVector);
                }
            }
        }
        for (int i = 0; i < allBalls.size(); i++)
        {
            allBalls[i].present(renderer);
        }
        for (int i = 0; i < lines.size(); i++)
        {
            Line line = lines[i];
            SDL_RenderDrawLineF(renderer, line.x1, line.y1, line.x2, line.y2);
        }
    }

    std::vector<Ball>
    getAllBalls()
    {
        return allBalls;
    }

    void reset()
    {
        allBalls.clear();
        allBalls.push_back(createRandomBall());
    }

    void mainBallMoveLeft()
    {
        allBalls[0].moveLeft(700);
    }
    void mainBallMoveRight()
    {
        allBalls[0].moveRight(700);
    }
    void mainBallDrop()
    {
        allBalls[0].drop();
        allBalls.insert(allBalls.begin(), createRandomBall());
    }
    int getSize()
    {
        return allBalls.size();
    }
};

#endif