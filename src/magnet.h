#include"main.h"
#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
    Magnet(){}
    Magnet(color_t color);
    void draw(glm::mat4 VP);
    glm::vec3 position;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
};

#endif