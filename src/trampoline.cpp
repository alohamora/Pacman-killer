#include"trampoline.h"
#include"main.h"

Trampoline::Trampoline(float x,color_t color){
    static const GLfloat vertex_buffer_data[] = {
        3.0,-1.0,0,
        5.0,-1.0,0,
        4.0,-1.5,0,

        3.0,-1.0,0,
        3.2,-1.0,0,
        3.2,-2.0,0,

        3.0,-2.0,0,
        3.2,-2.0,0,
        3.0,-1.0,0,

        5.0,-1.0,0,
        4.8,-1.0,0,
        5.0,-2.0,0,

        5.0,-2.0,0,
        4.8,-2.0,0,
        4.8,-1.0,0,
    };
    position.x = x;
    position.y = 0;
    position.z = 0;
    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}