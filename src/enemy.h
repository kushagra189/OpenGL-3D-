#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color,float l,float b, float h, float rot);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    double speedX;
    double speedZ;
    void tick();
    double speed;
    float length,breadth,hieght;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // ENEMY_H
