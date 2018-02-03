#include "ball.h"
#include "main.h"
#define PI  3.14159265358979323846

Ball::Ball(float x, float y, float rad, color_t color) {
    this->position = glm::vec3(x, y, 0);
    radius = rad;
    speed.x = 0;
    speed.y = 0;
    acc.y = 0;
    acc.x = 0;
    collide = 0;
    flag_pond = 0;
    flag_tramp = 1;
    const int n=1000;
    float  v1,v2,dif;
    collide = 0;
    dif = 360.0/n;
    v1 = 180.0/n;
    v2 = -180.0/n;
    static GLfloat vertex_buffer_data[9*n];
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
           vertex_buffer_data[(i*9)+j] = 0.0f;
        }
        vertex_buffer_data[(i*9)+3] = radius*cos((v2*PI)/180);
        vertex_buffer_data[(i*9)+4] = radius*sin((v2*PI)/180);
        vertex_buffer_data[(i*9)+5] = 0.0f;
        vertex_buffer_data[(i*9)+6] = radius*cos((v1*PI)/180);
        vertex_buffer_data[(i*9)+7] = radius*sin((v1*PI)/180);
        vertex_buffer_data[(i*9)+8] = 0.0f;
        v1 += dif;
        v2 += dif;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    float x,y,dis;
    int t;
    flag_pond = 0;
    flag_tramp = 0;
    if(collide==0)
        this->position.x += speed.x + acc.x;
    else
        this->position.x += speed.x;    
    this->position.y += speed.y;
    speed.y += acc.y;
    // std::cout<<position.x<<" "<<k<<" ";
    if(this->position.x > 0){
        t = (int)floor(this->position.x)/12;
        x = this->position.x - (float)((t+1)*12);
        // std::cout<<x<<"\n";
    }
    else{
        x = this->position.x;
    }
    if(x >= -2.0 && x <= (0.0) && this->position.y <= -1.75){
        x+=1;
        y = this->position.y;
        if(x <= 0.75 && x>=-0.75){
            x = (0.75*0.75) - (x*x);
            y = -sqrt(x) - 2;
            if(this->position.y > y) flag_pond = 1;
            else{
                this->position.y = y;
                flag_pond = 2;
            }
        }
        else{
            if(this->position.x > 0){
                t = (int)this->position.x/12;
                x = this->position.x - ((t+1)*12);
            }
            else{
                x = this->position.x;
            }
            if(x > -1)    this->position.y = -1.75 + ((x)/1.5);
            else    this->position.y = -1.75 - ((x  + 2.0)/1.5);   
            flag_pond = 2;
        }
    }
    else{
        if((this->position.y + 1.75) <= 0){
            this->position.y = -1.75;
        }
        if(this->position.x >=3+k && this->position.x <=5+k && this->position.y <= -1 && this->position.y >= -1.25){
            flag_tramp = 1;
            this->position.y = -1;
        }
    }
    if(this->position.x <= -5.75+screen_center_x || this->position.x >= 5.75 + screen_center_x){
        if(this->position.x <= -5.75+screen_center_x)   this->position.x = -5.75+screen_center_x;
        else    this->position.x = 5.75+screen_center_x; 
    }
    if(this->position.x >= 2.75+k && this->position.x <5+k && this->position.y < -1.0) this->position.x = 2.75+k;   
    if(this->position.x > 3+k && this->position.x <=5.25+k && this->position.y < -1.0) this->position.x = 5.25+k;   
}

