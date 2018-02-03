#include"ball.h"
#include"main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Ball   {
public:
    int plank,score;
    float angle;
    glm::vec3 plank_position;
    Enemy() {}
    Enemy(float x, float y, float rad, color_t color);
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object2;
};

#endif