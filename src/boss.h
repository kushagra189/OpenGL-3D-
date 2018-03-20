#include "main.h"

#ifndef BOSS_H
#define BOSS_H


class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z, color_t color,float l,float rot);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    double speedX;
    double speedZ;
    double accY;
    double speedY;
    void tick();
    double speed;
    float length;//,breadth,hieght;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BOSS_H
