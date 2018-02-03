#include"main.h"
#include"pond.h"
#define PI  3.14159265358979323846

Pond::Pond(float x,color_t color){
    const int n=1000;
    float  v1,v2,dif;
    dif = 360.0/n;
    v1 = 180.0/n;
    v2 = -180.0/n;
    static GLfloat vertex_buffer_data[4500];
    for(int i=0;i<500;i++){
        for(int j=0;j<3;j++){
           vertex_buffer_data[(i*9)+j] = 0.0f;
        }
        vertex_buffer_data[(i*9)+3] = cos((v2*PI)/180);
        vertex_buffer_data[(i*9)+4] = sin((v2*PI)/180);
        vertex_buffer_data[(i*9)+5] = 0.0f;
        vertex_buffer_data[(i*9)+6] = cos((v1*PI)/180);
        vertex_buffer_data[(i*9)+7] = sin((v1*PI)/180);
        vertex_buffer_data[(i*9)+8] = 0.0f;
        v1 -= dif;
        v2 -= dif;
    }
    position.x = -1+x;
    position.y = -2.0;
    position.z = 0.0;
    this->object = create3DObject(GL_TRIANGLES, 1500, vertex_buffer_data, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}