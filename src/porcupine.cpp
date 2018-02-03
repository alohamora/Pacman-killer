#include"porcupine.h"
#include"main.h"

Porcupine::Porcupine(float x1,float x2,color_t color){
    this->position.x = (x1+x2)/2;
    this->position.y = -2.0;
    this->position.z = 0;
    this->sp = 0.01;
    this->x1 = x1;
    this->x2 = x2;
    
    const GLfloat vertex_buffer_data[] = {
        0,0,0,
        0.125,0.0,0.0,
        0.0625,0.25,0.0,

        0,0,0,
        -0.125,0,0,
        -0.0625,0.25,0
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}
void Porcupine::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Porcupine::tick(){
     this->position.x += this->sp;
    // std::cout<<this->x2<<'\n';    
    if(this->position.x > this->x2){
         this->position.x = this->x2;
         this->sp = -this->sp;
    }
    else if(this->position.x < x1){
        this->position.x = x1;
        this->sp = -sp;
    }
}