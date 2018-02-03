#ifndef PLATFORM_H
#define PLATFORM_H

class Platform  {
public:
    Platform() {}
    Platform(color_t color);
    void draw_platform(glm::mat4 VP);
private:
    VAO *object1;
    VAO *object2;    
};

#endif