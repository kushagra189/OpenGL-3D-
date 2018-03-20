#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speedX;
    double speedY;
    double speedZ;
    double accY;
    int fl=1;
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *object;
    VAO *object1;
};

#endif // BALL_H
