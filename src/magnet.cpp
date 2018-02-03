#include"main.h"
#include"magnet.h"
#define PI  3.14159265358979323846
Magnet::Magnet(color_t color){
    const int n=1000;
    float  v1,v2,dif;
    dif = 360.0/n;
    v1 = (180.0/n) + 270.0;
    v2 = (-180.0/n) + 270.0;
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
    static GLfloat vertex_buffer_data2[4500];
    static GLfloat vertex_buffer_data3[]={
        0.0 , 1.0, 0,
        0.0, 0.65 ,0,
        0.5 , 0.65, 0,

        0.0 , 1.0, 0,
        0.5, 1.0 ,0,
        0.5 , 0.65, 0,
        
        0.0 , -1.0, 0,
        0.0, -0.65 ,0,
        0.5 , -0.65, 0,
        
        0.0 , -1.0, 0,
        0.5, -1.0 ,0,
        0.5 , -0.65, 0,
    };

    for(int i=0;i<4500;i++) vertex_buffer_data2[i] = vertex_buffer_data[i]*0.65;
    this->object = create3DObject(GL_TRIANGLES, 1500, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1500, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, COLOR_TIP, GL_FILL);
}
void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    float y = 2 ,x=-3+screen_center_x;
    glm::mat4 translate = glm::translate(glm::vec3(x,y,0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}