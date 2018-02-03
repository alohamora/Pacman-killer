#include"enemy.h"
#include"main.h"
#define PI  3.14159265358979323846

Enemy::Enemy(float x, float y, float rad, color_t color) : Ball(x,y,rad,color){
    if(rand()%2==0) plank = 1;
    else    plank=0;
    if(plank==1){
        score += 10;
        angle = rand()%61 + 60;
        GLfloat plank_buffer_data[] = {
            -2*rad,0,0,
            -2*rad,0.1,0,
            2*rad,0,0,

            -2*rad,0.1,0,
            2*rad,0,0,
            2*rad,0.1,0
        };
        this->object2 = create3DObject(GL_TRIANGLES, 6, plank_buffer_data, COLOR_GROUND, GL_FILL);
    }
}

void Enemy::draw(glm::mat4 VP){
    float z=1,f;
    f = (angle+90)*PI/180.0;
    glm::vec3 axis(0,0,z);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(plank==1){
        plank_position.x = position.x + (radius)*cos(angle*PI/180);
        plank_position.y = position.y + (radius)*sin(angle*PI/180);
        plank_position.z = 0;
        glm::mat4 rotate = glm::rotate(f,axis);
        glm::mat4 translate = glm::translate(plank_position);
        Matrices.model = translate*rotate;
        MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object2);
    }
}
void Enemy::tick(){
    this->position.x += speed.x;
    if(this->position.x >= 6 + radius+screen_center_x){
        this->position.x = -6 - radius + screen_center_x;
    }
}