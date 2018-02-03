#include"main.h"
#ifndef PORCUPINE_H
#define PORCUPINE_H

class Porcupine{
public:
    Porcupine(){}
    Porcupine(float x1,float x2, color_t color);
    void draw(glm::mat4 VP);
    void tick();
    float x1,x2,sp;
    glm::vec3 position;
private:
    VAO *object;
};

#endif