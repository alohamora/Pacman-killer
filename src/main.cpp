#include "main.h"
#include "timer.h"
#include "ball.h"
#include"platform.h"
#include"enemy.h"
#include"pond.h"
#include"trampoline.h"
#include"magnet.h"
#include"porcupine.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
Pond pond1,pond2,pond3,pond4;
Trampoline tr1,tr2,tr3,tr4;
Porcupine p1,p2,p3,p4,p5,p6,p7,p8;
/**************************
* Customizable functions *
**************************/

Ball player;
Platform base;
Enemy enemies[15];
Magnet magnet;
int frame_count,level,score;
char title[500];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
int k = 0;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    frame_count++;
    base.draw_platform(VP);
    pond1.draw(VP);
    pond2.draw(VP);
    pond3.draw(VP);
    pond4.draw(VP);
    tr1.draw(VP);
    tr2.draw(VP);
    tr4.draw(VP);
    tr3.draw(VP);
    if((frame_count/240)%2==1 && level==3){  
        magnet.draw(VP);
        player.acc.x = -.02;
    }
    else{
        player.acc.x = 0.0;
    }
    if(level >= 2){
        p1.draw(VP);
        p2.draw(VP);
        p3.draw(VP);
        p4.draw(VP);
        p5.draw(VP);
        p6.draw(VP);
        p7.draw(VP);
        p8.draw(VP);
    }
    player.draw(VP);
    for(int i=0;i<15;i++){
        enemies[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    float temp;
    int t;
    if(player.position.x > 0){
        t = (int)floor(player.position.x)/12;
        temp =  player.position.x-((t+1)*12);
    }
    else    temp = player.position.x;
    if (left && player.collide == 0) {
        player.speed.x = -.08;
    }
    else if (right && player.collide==0){
        player.speed.x = .08;
        if(player.position.x > screen_center_x){
             screen_center_x += player.speed.x;
             reset_screen();
        }
    }
    else if(up && player.collide==0) {
        if(player.position.y ==-1.75 || player.flag_pond == 2){
            player.speed.y = .08;
            player.acc.y = -.002;
        }
    }
    else{
        if(player.collide==0)
            player.speed.x = 0.0;
    }
    player.acc.y = -0.002;
    player.collide = 0;
    if(player.flag_tramp == 1) player.speed.y = 0.15;
    if(player.flag_pond == 1){
        if(player.speed.y<=0){
            player.acc.y = 0.0;
            player.speed.y = -.02;
        }
        else    player.acc.y = -.004;
        if(player.speed.x!=0){
            if(player.speed.x > 0)  player.speed.x -= .02;
            else    player.speed.x += .02;
        }
    }
    else if(player.flag_pond==2){
        if(player.speed.y<=0){
            player.acc.y = 0.0;
            player.speed.y = -.02;
        }
        else    player.acc.y = -.004;
        if(player.speed.x==0){

            if(temp < -1) player.speed.x = .01;
            else if(temp > -1)  player.speed.x = -.01;
        }
        else{
            if(player.speed.x > 0)  player.speed.x -= .04;
            else    player.speed.x += .04;
        }        
    }
}

void detect_collision(){
    float distance,d2,y,r,x1,x2;
    int i;
    for(i=0;i<15;i++){
        distance = (float)(player.position.x - enemies[i].position.x)*(player.position.x - enemies[i].position.x);
        distance += (float)(player.position.y - enemies[i].position.y)*(player.position.y - enemies[i].position.y);
        d2 = (float)(player.radius + enemies[i].radius)*(player.radius + enemies[i].radius);
        if(distance <= d2 && player.position.y > enemies[i].position.y){
            if(enemies[i].plank==0){
                player.speed.y = 0.08;
                player.speed.x = 0;
            }
            else{
                player.speed.y = 1.2*(player.speed.x*sin(2*(90.0 + enemies[i].angle)*M_PI/180.0) - player.speed.y*cos(2*(90.0 + enemies[i].angle)*M_PI/180.0));
                player.speed.x = 1.2*(-player.speed.x*cos(2*(90.0 + enemies[i].angle)*M_PI/180.0) - player.speed.y*sin(2*(90.0 + enemies[i].angle)*M_PI/180.0));
            }
            y = rand()%(41)-7;
            y = y/10;
            r = enemies[i].radius;
            enemies[i].set_position(-6-r,y);
            player.collide = 1;
            score += enemies[i].score;
            if(score >= 100)   level = 2;
            if(score >= 500)   level = 3;
            break;
        }
        if(i==15)   player.collide = 0;
    }
}
void detect_porcupine(){
    if(player.position.x >= (p1.position.x-0.125) && player.position.x <= (p1.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p1.position.x = -10;
        p1.x1 = -15;
        p1.sp = 0;
        score -= 100;
    }
    else if(player.position.x >= (p2.position.x-0.125) && player.position.x <= (p2.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p2.position.x = -10;
        p2.x1 = -15;
        p2.sp = 0;
        score -= 100;
    }
        else if(player.position.x >= (p3.position.x-0.125) && player.position.x <= (p3.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p3.position.x = -10;
        p3.x1 = -15;
        p3.sp = 0;
        score -= 100;
    }
        else if(player.position.x >= (p4.position.x-0.125) && player.position.x <= (p4.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p4.position.x = -10;
        p4.x1 = -15;
        p4.sp = 0;
        score -= 100;
    }
            else if(player.position.x >= (p5.position.x-0.125) && player.position.x <= (p5.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p5.position.x = -10;
        p5.x1 = -15;
        p5.sp = 0;
        score -= 100;
    }
            else if(player.position.x >= (p6.position.x-0.125) && player.position.x <= (p6.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p6.position.x = -10;
        p6.x1 = -15;
        p6.sp = 0;
        score -= 100;
    }
            else if(player.position.x >= (p7.position.x-0.125) && player.position.x <= (p7.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p7.position.x = -10;
        p7.x1 = -15;
        p7.sp = 0;
        score -= 100;
    }
            else if(player.position.x >= (p8.position.x-0.125) && player.position.x <= (p8.position.x+0.125) && player.position.y <= -1.5){
        player.speed.y = .08;
        player.acc.y = -0.002;
        p8.position.x = -10;
        p8.x1 = -15;
        p8.sp = 0;
        score -= 100;
    }
    if(score < 0) score = 0;
}
void tick_elements() {
    detect_collision();
    if(level>=2)
        detect_porcupine();
    player.tick();
    if(level >= 2){
        p1.tick();
        p2.tick();
        p3.tick();
        p4.tick();        p8.tick();
        p6.tick();        p5.tick();
        p7.tick();
    }
    for(int i=0;i<15;i++){
        enemies[i].tick();
    }
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    float radius,x,y,sp;
    player       = Ball(-0.75, -1.75, 0.25, COLOR_RED);
    base        = Platform(COLOR_GROUND);
    pond1 = Pond(0.0,COLOR_BLUE);
    pond2 = Pond(12,COLOR_BLUE);
    pond3 = Pond(24,COLOR_BLUE);
    pond4 = Pond(36,COLOR_BLUE);
    tr1 = Trampoline(0,COLOR_TRAMP);
    tr2 = Trampoline(12,COLOR_TRAMP);
    tr3 = Trampoline(24,COLOR_TRAMP);
    tr4 = Trampoline(36,COLOR_TRAMP);
    magnet = Magnet(COLOR_MAGNET);
    p1 = Porcupine(-5.875,-2.125,COLOR_PORC);
    p2 = Porcupine(0.125,2.875,COLOR_PORC);
        p3 = Porcupine(-5.875+12,-2.125+12,COLOR_PORC);
    p4 = Porcupine(0.125+12,2.875+12,COLOR_PORC);
        p5 = Porcupine(-5.875+24,-2.125+24,COLOR_PORC);
    p6 = Porcupine(0.125+24,2.875+24,COLOR_PORC);
        p7 = Porcupine(-5.875+36,-2.125+36,COLOR_PORC);
    p8 = Porcupine(0.125+36,2.875+36,COLOR_PORC);
    for(int i=0;i<15;i++){
        radius = rand()%11 + 20;
        radius = (float)radius/100;
        y = rand()%41;
        y = (float)y/10;
        x = rand()%81 + 40;
        x = (float)x/10;
        x = -x;
        sp = rand()%21 + 40;
        sp = (float)sp/1000;
        if(i%3==2){
            enemies[i] = Enemy(x,y,radius,COLOR_BALL3);
            enemies[i].score = 10;
        }
        else if(i%3==1){
            enemies[i] = Enemy(x,y,radius,COLOR_BALL2);
            enemies[i].score = 20;
        }
        else{
            enemies[i] = Enemy(x,y,radius,COLOR_BALL1);
            enemies[i].score = 30;
        }
        enemies[i].speed.x = sp;
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


void set_title(){
    int temp = score,t=0,a=1;
    title[25] = level + 48;
    while(temp > 0){
        t++;
        temp = temp/10;
    }
    if(t==0){
        title[33] = 48;
        title[34] = 0;
    }
    else{
        temp = score;
        title[33+t] = 0;
        while(temp>0){
            title[32+t] = 48 + (temp%10);
            t--;
            temp = temp/10;
        }
    }
}
void drag(GLFWwindow* window, double xpos, double ypos){
    float x,y;
    x = 6*((float)xpos-500)/500.0;
    y = (400-(float)ypos)/100.0;
    x += screen_center_x;
    y += screen_center_y;
    // cout<<x<<" "<<y<<"\n";        
    if(x >= (player.position.x - 0.5) && x <= (player.position.x + 0.5) && y >= (player.position.y - 0.5) && y <= (player.position.y + 0.5) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ){
        player.position.x = (float)x + 0.1;
    }
}
void calc_k(){
    k = (int)screen_center_x;
     k -= k%12;
}
int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 800;
    frame_count = 0;
    score = 0;
    level = 1;
    k=0;
    window = initGLFW(width, height);

    initGL (window, width, height);
    strcat(title,"**PACMAN-KILLER**  LEVEL-1 SCORE-0");
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            set_title();
            glfwSetWindowTitle(window,title);
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
             calc_k();
            tick_elements();
            tick_input(window);
            glfwSetCursorPosCallback(window, drag);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 6 / screen_zoom;
    float right  = screen_center_x + 6 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
