#include"main.h"
#include"platform.h"

Platform::Platform(color_t color){
    static const GLfloat vertex_buffer_data1[] = {
        -20.0, -2.5, 0.0,
        -20.0, -20.0 , 0.0,
        60.0, -2.5, 0.0,

        60.0, -2.5, 0.0,
        60.0 , -20.0, 0.0,
        -20.0, -20.0, 0.0,
    };
    static const GLfloat vertex_buffer_data2[] = {
        -20.0, -2.0, 0.0,
        -20.0, -2.5 , 0.0,
        60.0, -2.0, 0.0,

        60.0, -2.0, 0.0,
        60.0 , -2.5, 0.0,
        -20.0, -2.5, 0.0,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
}

void Platform::draw_platform(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(0,0,0));  
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}