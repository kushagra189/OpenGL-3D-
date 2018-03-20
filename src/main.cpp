#include "main.h"
#include "timer.h"
#include "boat.h"
#include "cube.h"
#include "enemy.h"
#include "can.h"
#include "boss.h"
#include "booster.h"
#include "zelda.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int w_c=0,w_f=0;
Boss bossMons[5];
Boat ball1;
Booster treasure;
Cube flPole;
Can cannon;
Cube water;
Cube barrel[20];
Cube coin[20];
Cube gift[25];
int tower_flag=0;
int islReach = 0;
Cube obstacles[50];
Cube bomb;
Cube island;
Enemy enemies[25];
int killCount = 0;
int countBullE[5] = {0};
Booster boost[5];
Zelda Player;
char scorput[10000];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int coins = 0;
int life = 1000;
int bFlag = 0;
int bCount = 0;
int score = 0;
int view=1;
int increased = 0;
int decreased = 0;
Timer t60(1.0 / 60);

float camera_x = ball1.position.x+75*sin(ball1.rotation*M_PI/180.0f);;
float camera_y = 35;
float camera_z = ball1.position.z+75*cos(ball1.rotation*M_PI/180.0f);
float target_x = ball1.position.x;
float target_y = ball1.position.y;
float target_z = ball1.position.z;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );

    //top view
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 5, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
//    glm::vec3 up (0, 1, 0);

    //target view
//    glm::vec3 eye(ball1.position.x,ball1.position.y+10*sin(45*M_PI/180),ball1.position.z-10*cos(45*M_PI/180));
//    glm::vec3 target(ball1.position.x,ball1.position.y,ball1.position.z);
//    glm::vec3 target (0, 0, 0);
//    glm::vec3 up (0, 1, 0);

//    glm::vec3 eye (x_c, y_c, z_c);
//    glm::vec3 target (x_t, y_t, z_t);
    glm::vec3 eye (camera_x,camera_y,camera_z);
    glm::vec3 target (target_x,target_y,target_z);
    glm::vec3 up (0, 1, 0);

    //perspective
//    glm::vec3 eye (0, 10, 20);

//    glm::vec3 target (0, 10, 10);
//    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    flPole.draw(VP);
    island.draw(VP);
    
    if(Player.live!=1)
    {
        cannon.draw(VP);
        ball1.draw(VP);
        bomb.draw(VP);
    }
    if(Player.live==1){
    Player.draw(VP);
    }
//    boost.draw(VP);
    if(killCount>6){
        for(int i=0;i<5;i++){
            bossMons[i].draw(VP);
            boost[i].draw(VP);
        }
    }
//        for(int i=0;i<)
    // }
    // for(int i=0;i<5;i++){
    //         // bossMons[i].draw(VP);
    //         boost[i].draw(VP);
    //     }
    water.draw(VP);
    for(int i=0;i<20;i++)
    {
        barrel[i].draw(VP);
        coin[i].draw(VP);
    }
    for(int i=0;i<50;i++)
    {
        obstacles[i].draw(VP);
    }
    for (int i=0;i<25;i++){
        enemies[i].draw(VP);
    }
    for(int i=0;i<25;i++){
//        if(monitor[i]==1)
//        {
            gift[i].draw(VP);
//        }
    }
    treasure.draw(VP);
//    temp.draw(VP);
}

void wind()
{
    float p;
    w_c++;
    if(w_c == 2000)
    {
        p = static_cast <float> (rand());
    }
    if(w_c>=5000)
    {
      w_f = w_c = 0;
    }
    if(w_c>= 2000 && w_c<5000)
    {
      w_f = 1;
    }
    if(w_c < 2000)
    {
      w_f = 0;
    }

    if(w_f == 1)
    {
        ball1.rotation=p;
        bomb.rotation=p;
        cannon.rotation=p;
        // bomb.speedX = cannon.speedX = ball1.speedX = ball1.speed;
        // bomb.speedZ = cannon.speedZ = ball1.speedZ = ball1.speed;
        ball1.position.x+=0.1*sin((ball1.rotation)*M_PI/180.0f);
        ball1.position.z+=0.1*cos((ball1.rotation)*M_PI/180.0f);
        bomb.position.x+=0.1*sin((ball1.rotation)*M_PI/180.0f);
        bomb.position.z+=0.1*cos((ball1.rotation)*M_PI/180.0f);
        cannon.position.x+=0.1*sin((ball1.rotation)*M_PI/180.0f);
        cannon.position.z+=0.1*cos((ball1.rotation)*M_PI/180.0f);
    }
}

void followBoat(){
    float bX = ball1.position.x, bZ = ball1.position.z;
    for(int i=0;i<25;i++){
        float eX = enemies[i].position.x,eZ = enemies[i].position.z;
        float t = sqrt((bX-eX)*(bX-eX)+(bZ-eZ)*(bZ-eZ));
        enemies[i].speedX = enemies[i].speed/20*(bX-eX)/t;
        enemies[i].speedZ = enemies[i].speed/20*(bZ-eZ)/t;
        enemies[i].position.x+=enemies[i].speedX;
        enemies[i].position.z+=enemies[i].speedZ;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);

    if(one)
    {
        view = 1;
        tower_flag = 0;
        follow_cam();
    }

    if(two)
    {
        view = 2;
        tower_flag = 0;
        boat_cam();
    }

    if(three)
    {
        view = 3;
        tower_cam();
    }

    if(four)
    {
        view = 4;
        tower_flag = 0;
        top_cam();
    }

    if(five)
    {
        view = 5;
        tower_flag = 0;
    }

    if (left) {
        // Do something
        if(Player.live==1){
            Player.rotation-=1;
        }
        else{
            ball1.rotation-=1;
            bomb.rotation-=1;
            cannon.rotation-=1;
        }
//        cannon.rotation-=5;
//        ball1.speedX=0.1*ball1
    }
    if (right) {
        // Do something
        if(Player.live==1){
            Player.rotation+=1;
        }
        else{
        ball1.rotation+=1;
        bomb.rotation+=1;
        cannon.rotation+=1;
        }
//        cannon.rotation+=5;
    }
    if(up){
//        ball1.position.z+=0.1;
//        flPole.position.z+=0.1;
        ball1.speedX=ball1.speed*sin(ball1.rotation*M_PI/180);
        ball1.speedZ=ball1.speed*cos(ball1.rotation*M_PI/180);
        cannon.position.x+=ball1.speedX;
        ball1.position.x+=ball1.speedX;
        bomb.position.x+=ball1.speedX;
        cannon.position.z+=ball1.speedZ;
        ball1.position.z+=ball1.speedZ;

        bomb.position.z+=ball1.speedZ;

        if(Player.live==1){
            Player.speedX=Player.speed*sin(Player.rotation*M_PI/180);
            Player.speedZ=Player.speed*cos(Player.rotation*M_PI/180);
            Player.position.x+=Player.speedX;
            Player.position.z+=Player.speedZ;
        }
    }
    if (down){
        bomb.speedX=ball1.speedX=ball1.speed*sin(ball1.rotation*M_PI/180);
        bomb.speedZ=ball1.speedZ=ball1.speed*cos(ball1.rotation*M_PI/180);
        cannon.position.x-=ball1.speedX;
        ball1.position.x-=ball1.speedX;
        bomb.position.x-=bomb.speedX;
        cannon.position.z-=ball1.speedZ;
        ball1.position.z-=ball1.speedZ;
        bomb.position.z-=bomb.speedZ;

        if(Player.live==1){
            Player.speedX=Player.speed*sin(Player.rotation*M_PI/180);
            Player.speedZ=Player.speed*cos(Player.rotation*M_PI/180);
            Player.position.x-=Player.speedX;
            Player.position.z-=Player.speedZ;
        }
    }

    if (space){
        if(ball1.fl==1){
//            bomb.set_position(ball1.position.x,1.5,ball1.position.z);
            ball1.speedY+=0.8;
            ball1.fl=0;
            bomb.speedY+=0.8;
//            printf("%f\n",bomb.speedY);
            bomb.fl=0;
            cannon.speedY+=0.8;
            cannon.fl=0;
        }

        if(Player.fl==1 && Player.live==1){
//            bomb.set_position(Player.position.x,1.5,Player.position.z);
            Player.speedY+=0.8;
            Player.fl=0;
        }
    }

    if(fire){
//        if(bomb.fired==1){
//            bomb.set_position(0,1.5,0);
//            bomb.fired=0;
//        }
        if(bomb.fired==0){
            bomb.speedY+=0.8;
//            bomb.accY= -0.2;
            bomb.flFire=0;
            bomb.fired=1;
            bomb.fl = 0;
            bomb.rotation=cannon.rotation;
//            bomb.speedX+=0.6*sin(bomb.rotation*M_PI/180);
//            bomb.speedZ+=0.6*cos(bomb.rotation*M_PI/180);
//            bomb.position.x+=bomb.speedX;
//            bomb.position.z+=bomb.speedZ;
        }
    }
}

void speedUP(){
    // printf("%f\n",ball1.speed);
    if(bFlag==1 && bCount<=200){
        bCount++;
        if(increased==0){
            ball1.speed=2*ball1.speed;
            increased=1;
            decreased=0;
        }
        // ball1.speedZ=20*ball1.speedZ;
    }
    if(bCount>200 && bFlag==1){
        // ball1.speedZ=ball1.speedZ/20;
        if(decreased==0){
            ball1.speed=ball1.speed/2;
            decreased=1;
            increased=0;
        }
        bCount=0;
        bFlag=0;
    }
}

void tick_elements() {
    ball1.tick();
    followBoat();
    bomb.tick();
    cannon.tick();

    if(view==1)
    {
        follow_cam();
        // view = 1;
    }

    if(view==2)
    {
        boat_cam();
        // view = 2;
    }

    if(view==3)
    {
        tower_cam();
        // view = 3;
    }

    if(view==4)
    {
        top_cam();
        // view = 4;
    }

    for(int i=0;i<20;i++){
        coin[i].rotation+=5;
    }

    for(int i=0;i<5;i++)
        bossMons[i].tick();

    if(bomb.fired==1){
//        printf("1\n");
        if(bomb.position.y<=1.5){
            bomb.set_position(ball1.position.x,1.5,ball1.position.z);
            bomb.fired=0;
            bomb.speedY=0;
            bomb.fl=1;
        }
    }

    wind();

    for(int i=0;i<20;i++){
        if(detect_collision(ball1.bounding_box(),coin[i].bounding_box())){
//               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
//               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
//               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
               coin[i].set_position(coin[i].position.x,coin[i].position.y+1000,coin[i].position.z);
               coins++;
               break;
        }
    }

    if(detect_collision(ball1.bounding_box(),island.bounding_box())){
        islReach=1;
        if(Player.live==0){
            Player.live=1;
            Player.set_position(ball1.position.x+2*sin(ball1.rotation*M_PI/180),ball1.position.y+12,ball1.position.z+2*cos(ball1.rotation*M_PI/180));
            // ball1.speed=0;
        }
        // coins++;
        // break;
    }

    for(int i=0;i<5;i++){
        if(detect_collision(ball1.bounding_box(),bossMons[i].bounding_box())){
               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
               life-=10;
               break;
        }
    }

    for(int i=0;i<5;i++){
        if(detect_collision(ball1.bounding_box(),boost[i].bounding_box())){
//               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
//               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
//               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
//               life-=10;
               boost[i].set_position(ball1.position.x,ball1.position.y+20000,ball1.position.z);
               bFlag = 1;
               break;
        }
    }

    for(int i=0;i<5;i++){
        if(detect_collision(bomb.bounding_box(),bossMons[i].bounding_box())){
               if(countBullE[i]==4){
                   int a,b;
                   if(rand()%2)a=1;
                   else a=-1;
                   if(rand()%2)b=1;
                   else b=-1;
                    score+=100;
                    countBullE[i]=0;
                    boost[i].set_position(bossMons[i].position.x,bossMons[i].position.y,bossMons[i].position.z);
                    bossMons[i].set_position(bossMons[i].position.x+100*a,bossMons[i].position.y+2,bossMons[i].position.z+100*b);
                    bomb.set_position(ball1.position.x,ball1.position.y+4,ball1.position.z);
                    break;
               }
               else
                   countBullE[i]++;
//               life-=10;
        }
    }

    for(int i=0;i<50;i++){
        if(detect_collision(ball1.bounding_box(),obstacles[i].bounding_box())){
               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
               life--;
               break;
        }
    }

    for(int i=0;i<20;i++){
        if(detect_collision(ball1.bounding_box(),barrel[i].bounding_box())){
               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
//               life--;
               break;
        }
    }

    for(int i=0;i<50;i++){
        if(detect_collision(bomb.bounding_box(),obstacles[i].bounding_box()) && bomb.flFire==0){
//               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
//               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               int a,b;
               if(rand()%2)a=1;
               else a=-1;
               if(rand()%2)b=1;
               else b=-1;
               obstacles[i].set_position(obstacles[i].position.x+100*b,obstacles[i].position.y+2,obstacles[i].position.z+100*a);
               score+=10;
               break;
        }
    }

    for(int i=0;i<25;i++){
        if(detect_collision(ball1.bounding_box(),enemies[i].bounding_box())){
               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
               life-=3;
               break;
        }
    }

    for(int i=0;i<25;i++){
        gift[i].rotation+=5;
        if(detect_collision(ball1.bounding_box(),gift[i].bounding_box())){
//               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
//               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               gift[i].set_position(ball1.position.x,ball1.position.y+20000,ball1.position.z);
//               killCount++;
               life+=3;
               break;
        }
    }

    if(detect_collision(Player.bounding_box(),treasure.bounding_box())){
        treasure.set_position(treasure.position.x,treasure.position.y+20000,treasure.position.z);
        score+=1000;
    }

    for(int i=0;i<25;i++){
        if(detect_collision(bomb.bounding_box(),enemies[i].bounding_box()) && bomb.flFire==0){
//               ball1.set_position(ball1.position.x,ball1.position.y,ball1.position.z+2);
//               cannon.set_position(ball1.position.x,ball1.position.y+3,ball1.position.z);
               int a,b;
               if(rand()%2)a=1;
               else a=-1;
               if(rand()%2)b=1;
               else b=-1;
               gift[i].set_position(enemies[i].position.x,enemies[i].position.y,enemies[i].position.z);
               enemies[i].set_position(enemies[i].position.x+100*a,enemies[i].position.y,enemies[i].position.z+100*b);
               bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
//               monitor[i]=1;
               killCount++;
               score+=20;
               break;
        }
    }

    for(int i=0;i<50;i++){
        for(int j=0;j<25;j++){
               if(detect_collision(obstacles[i].bounding_box(),enemies[j].bounding_box())){
                   enemies[j].set_position(enemies[j].position.x,enemies[j].position.y,enemies[j].position.z+2);
//                   bomb.set_position(ball1.position.x,ball1.position.y+2,ball1.position.z);
//                   break;
            }
        }
    }

    if(Player.position.x>island.position.x+52 || Player.position.x<island.position.x-52)
    {
        Player.live=0;
    }

    if(Player.position.z>island.position.z+152 || Player.position.z<island.position.z-152)
    {
        Player.live=0;
    }

//    x_c=ball1.position.x+75*sin(ball1.rotation*M_PI/180.0f);
//    y_c=35;
//    z_c=ball1.position.z+75*cos(ball1.rotation*M_PI/180.0f);

//    x_t=ball1.position.x;
//    y_t=ball1.position.y;
//    z_t=ball1.position.z;
//    camera_rotation_angle += 1;
    sprintf(scorput,"Score:  %d | Lives: %d |Coins: %d",score,life,coins);
    glfwSetWindowTitle(window,scorput);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1  = Boat(0, -0.5,0, COLOR_RED);
//    ball1.rotation = 15;
    flPole = Cube(0.2,0.5,0, COLOR_BLACK,0.08,0.08,1,90);
    island = Cube(200,0.5,350, COLOR_ISLAND,100,300,10,90);
    treasure = Booster(200,18,350,COLOR_YELLOW,7,7,10,0);
//    boost = Booster(0,5,0, COLOR_YELLOW,3,3,3,0);
    cannon = Can(0,2.5,0, COLOR_CANON,0.8,4,0.8,0);
    bomb = Cube(0,1.5,0, COLOR_CANON,1,1,1,0);
    water = Cube(0,-1,0,COLOR_BLUE,10000,10000,1,90);
    Player = Zelda(0, 5,0, COLOR_RED);
    for(int i=0;i<20;i++)
    {
        int a = 0,c = 0;
        if(rand()%2==1)
            a=1;
        else
            a=-1;
        if(rand()%2==1)
            c=1;
        else
            c=-1;
        float x = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*400*a;
        float y = 0;
        float z = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*300*c;
//        float l = rand()%10+5;

        barrel[i] = Cube(x,y,z,COLOR_CANON,12,2,12,0);
        coin[i] = Cube(x,y+8,z,COLOR_YELLOW,4,4,4,0);
    }
    for(int i=0;i<5;i++)
    {
        int a = 0,c = 0;
        if(rand()%2==1)
            a=1;
        else
            a=-1;
        if(rand()%2==1)
            c=1;
        else
            c=-1;
        float x = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*150*a;
        float y = 0.5;
        float z = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*150*c;
//        float l = rand()%10+5;
        bossMons[i] = Boss(x,y,z,COLOR_PURP,12/sqrt(3),0);
        boost[i] = Booster(x,20000,z,COLOR_LGREEN,3,3,4,0);
    }
    for(int i=0;i<50;i++)
    {
        int a = 0,c = 0;
        if(rand()%2==1)
            a=1;
        else
            a=-1;
        if(rand()%2==1)
            c=1;
        else
            c=-1;
        float x = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*500*a;
        float y = -0.5;
        float z = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*500*c;
        float l = rand()%10+5;
        float b = rand()%10+5;
        float h = rand()%10+5;
        obstacles[i] = Cube(x,y,z,COLOR_GREY,l,b,h,0);
//        printf("%f %f %f\n",obstacles[i].position.x,obstacles[i].position.y,obstacles[i].position.z);
    }

    for(int i=0;i<25;i++)
    {
        int a = 0,c = 0,d=0;
        if(rand()%2==1)
            a=1;
        else
            a=-1;
        if(rand()%2==1)
            c=1;
        else
            c=-1;
        if(rand()%2==1)
            d=1;
        else
            d=-1;
        float x = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*300*a;
        float y = -0.1;
        float z = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*300*c;
        float l = rand()%5+3;
        float b = rand()%5+3;
        float h = rand()%5+4;
        float theta = 5;
        enemies[i] = Enemy(x,y,z,COLOR_YELLOW,l,b,h,theta*d);
//        printf("%f %f %f\n",obstacles[i].position.x,obstacles[i].position.y,obstacles[i].position.z);
    }

    for(int i=0;i<25;i++)
    {
        int a = 0,c = 0,d=0;
        if(rand()%2==1)
            a=1;
        else
            a=-1;
        if(rand()%2==1)
            c=1;
        else
            c=-1;
        if(rand()%2==1)
            d=1;
        else
            d=-1;
        float x = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*300*a;
        float y = 10000;
        float z = (static_cast <float> (rand())/static_cast <float> (RAND_MAX))*300*c;
        float l = 3;
        float b = 3;
        float h = 4;
        color_t col[] = {COLOR_BLACK,COLOR_BOM,COLOR_CANON,COLOR_GREEN,COLOR_GREY,COLOR_MAR,COLOR_PURP,COLOR_ORANGE,COLOR_RED};
//        float theta = 5;
        int k = rand()%9;
        gift[i] = Cube(x,y,z,col[k],l,b,h,0);
//        printf("%f %f %f\n",obstacles[i].position.x,obstacles[i].position.y,obstacles[i].position.z);
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


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            speedUP();
            tick_elements();
            tick_input(window);
            // speed_camera();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 <= (a.length + b.length)) &&
           ((abs(a.z - b.z) * 2 <= (a.breadth + b.breadth)) &&
            (abs(a.y - b.y) * 2 <= (a.height + b.height)));
}

bool detect_collision_rock(bounding_box_t a, bounding_box_t b) {
    float dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
    if(dist<(a.length+b.length)/2)
        return 1;
    else
        return 0;
}

void reset_screen() {
//    float top    = screen_center_y + 4 / screen_zoom;
//    float bottom = screen_center_y - 4 / screen_zoom;
//    float left   = screen_center_x - 4 / screen_zoom;
//    float right  = screen_center_x + 4 / screen_zoom;
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(45.0f,1.0f,10.0f,200.0f);
}


void follow_cam()
{
    camera_x = ball1.position.x+75*sin(ball1.rotation*M_PI/180.0f);;
    camera_y = 35;
    camera_z = ball1.position.z+75*cos(ball1.rotation*M_PI/180.0f);
    target_x = ball1.position.x;
    target_y = ball1.position.y;
    target_z = ball1.position.z;

    if(Player.live==1)
    {
        camera_x = Player.position.x+75*sin(Player.rotation*M_PI/180.0f);;
        camera_y = 35;
        camera_z = Player.position.z+75*cos(Player.rotation*M_PI/180.0f);
        target_x = Player.position.x;
        target_y = Player.position.y;
        target_z = Player.position.z;   
    }
}

void boat_cam()
{
    double theta = (ball1.rotation)*(M_PI/180);

    camera_x = ball1.position.x+3*sin(theta);
    camera_y = ball1.position.y+10;
    camera_z = ball1.position.z+3*cos(theta);

    target_x = ball1.position.x+10*sin(theta);
    target_y = ball1.position.y+10;
    target_z = ball1.position.z+10*cos(theta);

    if(Player.live==1)
    {
        theta = (Player.rotation)*(M_PI/180);
        camera_x = Player.position.x+3*sin(theta);
        camera_y = Player.position.y+10;
        camera_z = Player.position.z+3*cos(theta);

        target_x = Player.position.x+10*sin(theta);
        target_y = Player.position.y+10;
        target_z = Player.position.z+10*cos(theta);
    }
}

void tower_cam()
{
    if(tower_flag==0)
    {
        camera_y = 50;
        // camera_z = ball1.position.z;
        // camera_x = ball1.position.x;
        //        camera_z+=5;
        //        target_y = 30;
        target_x = ball1.position.x;
        target_y = ball1.position.y;
        target_z = ball1.position.z;
    }
    // tower_flag=1;

    if(Player.live==1)
    {
        if(tower_flag==0)
        {
            camera_y = 50;
            // camera_z = ball1.position.z;
            // camera_x = ball1.position.x;
            //        camera_z+=5;
            //        target_y = 30;
            target_x = Player.position.x;
            target_y = Player.position.y;
            target_z = Player.position.z;
        }
    }
    tower_flag=1;
}

void top_cam()
{
    camera_x = ball1.position.x;
    camera_y = 100;
    camera_z = ball1.position.z;
    target_x = ball1.position.x+1;
    target_y = ball1.position.y;
    target_z = ball1.position.z;

    if(Player.live==1)
    {
        camera_x = Player.position.x;
        camera_y = 100;
        camera_z = Player.position.z;
        target_x = Player.position.x+1;
        target_y = Player.position.y;
        target_z = Player.position.z;
    }
}

void move_cannon(float x, float z) {
    if (view != 5) {
        cannon.rotation= ball1.rotation-((3*x/5) - 100);
    }
    else
    {
        camera_x = ball1.position.x;
        camera_y = 100;
        camera_z = ball1.position.z+50;
        target_x = ball1.position.x + (x-300)/300 * 50;
        target_y = ball1.position.y;
        target_z = ball1.position.z + (z-300)/300 * 50;

        if(Player.live==1)
        {
            camera_x = Player.position.x;
            camera_y = 100;
            camera_z = Player.position.z+50;
            target_x = Player.position.x + (x-300)/300 * 50;
            target_y = Player.position.y;
            target_z = Player.position.z + (z-300)/300 * 50;
        }
    }
}