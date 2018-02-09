#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float rad, color_t color);
    glm::vec3 position;
    float radius;
    float rotation;
    int flag_pond,flag_tramp,collide;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void detect_object(float temp);
    glm::vec2 speed;
    glm::vec2 acc;
protected:
    VAO *object;
};

#endif // BALL_H
