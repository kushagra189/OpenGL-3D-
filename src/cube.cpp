#include "cube.h"
#include "main.h"

Cube::Cube(float x, float y, float z, color_t color,float l, float b,float h, float rot) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rot;
    speed = 1;
    accY = -0.03;
    length = l;
    breadth = b;
    hieght = h;
    int p = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[110];
        //top
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2,
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2;

        //bottom
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;

        //front
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2;

        //back
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;

        //left
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=-l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;

        //right
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=-h/2,
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=h/2;
        vertex_buffer_data[p++]=l/2;
        vertex_buffer_data[p++]=-b/2;
        vertex_buffer_data[p++]=-h/2;

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cube::draw(glm::mat4 VP) {
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

void Cube::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cube::tick() {
    this->position.y += this->speedY;
    if(this->fired==0){
//        printf("yes");
        if(this->position.y>1.5)
        {
            this->speedY += this->accY;
        }
        else
        {
            this->position.y=1.5;
            this->speedY = 0;
            this->fl=1;
        }
    }
    else if(this->flFire==0 && this->fired==1){
        this->speedX=sin(this->rotation*M_PI/180);
        this->speedZ=cos(this->rotation*M_PI/180);
        this->position.x-=this->speedX;
        this->position.z-=this->speedZ;
        if(this->position.y>1.5)
        {
            this->speedY += this->accY;
        }
        else
        {
            this->position.y=1.5;
            this->speedY = 0;
            this->fl=1;
        }
    }
}


bounding_box_t Cube::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z = this->position.z;
    float ht = this->hieght;
    float bt = this->breadth;
    float lt = this->length;
    bounding_box_t bbox = { x, y, z, lt,bt,ht };
    return bbox;
}
