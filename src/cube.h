#include "main.h"

#ifndef CUBE_H
#define CUBE_H


class Cube {
public:
    Cube() {}
    Cube(float x, float y, float z, color_t color,float l,float b, float h, float rot);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    double speedX;
    double speedY;
    double speedZ;
    int fl=1;
    int flFire=1;
    int fired=0;
    double accY;
    float length,breadth,hieght;
    bounding_box_t bounding_box();
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // CUBE_H
