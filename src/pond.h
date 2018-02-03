#include"main.h"
#ifndef POND_H
#define POND_H

class Pond {
public:
    Pond(){}
    Pond(float x,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};
#endif