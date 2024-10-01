#ifndef BALL_H
#define BALL_H

#include "Color.h"
#include <vector>
#include "helpers.h"
#include <SDL2/SDL.h>
#include <iostream>
#define GRAVITY 1500

struct VelocityVector
{
    float x;
    float y;
};

class Ball
{
protected:
    Color color;
    std::vector<SDL_FPoint> circleBody;
    double time;

public:
    float x;
    float y;
    VelocityVector velvec;
    int size;
    bool isFree;
    bool onGround;
    double radius;
    double centerX;
    double centerY;

    Ball(int size, float x, float y, int r, int g, int b) : size(size)
    {
        this->x = x;
        this->y = y;
        this->onGround = false;
        isFree = false;

        Color color = {r, g, b};
        VelocityVector velocityVector = {0, 0};
        velvec = velocityVector;

        this->color = color;

        createCircle();
    };

    void present(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawPointsF(renderer, circleBody.data(), circleBody.size());
    }

    std::vector<SDL_FPoint> getCircleBody()
    {
        return circleBody;
    }

    void setY(float y)
    {
        this->y = y;
        createCircle();
    }
    void setX(float x)
    {
        this->x = x;
        createCircle();
    }

    void moveRight(int distance)
    {
        double deltaDistance = distance * helpers::delta;
        for (int i = 0; i < circleBody.size(); i++)
        {
            circleBody[i].x += deltaDistance;
        }
        x += deltaDistance;
    }

    void moveLeft(int distance)
    {
        double deltaDistance = distance * helpers::delta;
        for (int i = 0; i < circleBody.size(); i++)
        {
            circleBody[i].x -= deltaDistance;
        }
        x -= deltaDistance;
    }

    void drop()
    {
        isFree = true;
        onGround = false;
    }

    void addVec(VelocityVector vec)
    {
        velvec.x = vec.x + velvec.x;
        velvec.y = vec.y + velvec.y;
    }
    void applyGravity()
    {
        VelocityVector gravityVec;
        gravityVec.x = 0;
        gravityVec.y = GRAVITY * helpers::delta;
        addVec(gravityVec);
    }
    void move()
    {
        if (!onGround)
        {
            applyGravity();
        }
        for (int i = 0; i < circleBody.size(); i++)
        {
            circleBody[i].x += velvec.x * helpers::delta;
            circleBody[i].y += velvec.y * helpers::delta;
        }
        x += velvec.x * helpers::delta;
        y += velvec.y * helpers::delta;
        centerX += velvec.x * helpers::delta;
        centerY += velvec.y * helpers::delta;
    }

    void createCircle()
    {
        radius = size / 2;
        centerX = x + radius;
        centerY = y + radius;
        std::vector<SDL_FPoint> points;

        int prev = 0;
        // for (int i = 0; i < radius; i++)
        // {
        // float innerRadius = (size / 2.0) - i;
        for (float j = 0; j < 360; j += 0.1)
        {
            SDL_FPoint point;
            point.x = centerX + (radius * helpers::cosDegree(j));
            point.y = centerY + (radius * helpers::sinDegree(j));
            points.push_back(point);
        }
        // }
        circleBody = points;
    }
};

#endif