#include "boss.h"
#include "boat.h"
#include "main.h"

Boss::Boss(float x, float y, float z, color_t color,float l,float rot) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rot;
    speed = 1;
    speedY=0.8;
    accY = -0.03;
    this->length = l;
//    this->breadth = b;
//    this->hieght = h;
//    int p = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[]{
        l/2,0,l*sqrt(3)/2,
        l,0,0,
        (l+l/2)/2,10,l*sqrt(3)/4,

        l/2,0,-l*sqrt(3)/2,
        l,0,0,
        (l+l/2)/2,10,-l*sqrt(3)/4,

        -l/2,0,-l*sqrt(3)/2,
        l/2,0,-l*sqrt(3)/2,        
        0,10,-l*sqrt(3)/2,

        -l/2,0,-l*sqrt(3)/2,
        -l,0,0,
        -(l+l/2)/2,10,-l*sqrt(3)/4,

        -l,0,0,
        -l/2,0,l*sqrt(3)/2,
        -(l+l/2)/2,10,l*sqrt(3)/4,

        -l/2,0,l*sqrt(3)/2,
        l/2,0,l*sqrt(3)/2,
        0,10,l*sqrt(3)/2,
    };


    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
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

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {
    this->position.y+=this->speedY;
    if(this->position.y>0.5)
    {
        this->speedY += this->accY;
    }
    else
    {
//        this->position.y=0.5;
        this->speedY -= this->accY ;
//        this->fl=1;
    }
}

bounding_box_t Boss::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z = this->position.z;
    float ht = 10;//this->hieght;
    float bt = 2*this->length;
    float lt = this->length;
    bounding_box_t bbox = { x, y, z, lt,bt,ht };
    return bbox;
}
