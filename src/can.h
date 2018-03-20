#include "main.h"

#ifndef CAN_H
#define CAN_H


class Can {
public:
    Can() {}
    Can(float x, float y, float z, color_t color,float l,float b, float h, float rot);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    double speedX;
    double speedY;
    double speedZ;
    int fl=1;
    double accY;
    float length,breadth,hieght;
    bounding_box_t bounding_box();
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // CAN_H
