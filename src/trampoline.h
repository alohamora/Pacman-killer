#include"main.h"
#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

class Trampoline {
public:
    Trampoline(){}
    Trampoline(float x,color_t color);
    void draw(glm::mat4 VP);
    glm::vec3 position;
private:
    VAO *object;
};
#endif