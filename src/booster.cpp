#include "booster.h"
#include "main.h"

Booster::Booster(float x, float y, float z, color_t color,float l, float b,float h,float rot) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rot;
    speed = 1;
    this->length = l;
    this->breadth = b;
    this->hieght = h;
//    int p = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[]{
        -l/2,0,b/2,
        l/2,0,b/2,
        l/2,0,-b/2,
        -l/2,0,b/2,
        -l/2,0,-b/2,
        l/2,0,-b/2,

        -l/2,0,b/2,
        0,h,0,
        l/2,0,b/2,

        -l/2,0,b/2,
        0,-h,0,
        l/2,0,b/2,

        l/2,0,-b/2,
        0,h,0,
        l/2,0,b/2,

        l/2,0,-b/2,
        0,-h,0,
        l/2,0,b/2,

        -l/2,0,-b/2,
        0,h,0,
        -l/2,0,b/2,

        -l/2,0,-b/2,
        0,-h,0,
        -l/2,0,b/2,

        l/2,0,-b/2,
        0,h,0,
        -l/2,0,-b/2,

        l/2,0,-b/2,
        0,-h,0,
        -l/2,0,-b/2,
    };

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
}

void Booster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Booster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Booster::tick() {
    this->speedX = speed*cos(45*M_PI/180)/10;
    this->speedZ = speed*sin(45*M_PI/180)/10;
    this->position.x+=this->speedX;
    this->position.z+=this->speedZ;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Booster::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z = this->position.z;
    float ht = this->hieght;
    float bt = this->breadth;
    float lt = this->length;
    bounding_box_t bbox = { x, y, z, lt,bt,ht };
    return bbox;
}
