#include "main.h"

#ifndef BOOSTER_H
#define BOOSTER_H


class Booster {
public:
    Booster() {}
    Booster(float x, float y, float z, color_t color,float l,float b, float h, float rot);
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
};

#endif // BOOSTER_H
