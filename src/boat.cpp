#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->accY = -0.03;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[] = {
        //left
        -1,1,-1,
        -0.5,0.5,-0.5,
        -0.5,0.5,0.5,
        -1,1,-1,
        -1,1,1,
        -0.5,0.5,0.5,
        //right
        0.5,0.5,0.5,
        1,1,1,
        1,1,-1,
        0.5,0.5,0.5,
        0.5,0.5,-0.5,
        1,1,-1,
        //front
        -1,1,-1,
        -0.5,0.5,-0.5,
        0.5,0.5,-0.5,
        -1,1,-1,
        1,1,-1,
        0.5,0.5,-0.5,
        //back
        0.5,0.5,0.5,
        1,1,1,
        -1,1,1,
        0.5,0.5,0.5,
        -0.5,0.5,0.5,
        -1,1,1,
        //bottom
        -0.5,0.5,0.5,
        -0.5,0.5,-0.5,
        0.5,0.5,-0.5,
        -0.5,0.5,0.5,
        0.5,0.5,0.5,
        0.5,0.5,-0.5,
    };

    static GLfloat vertex_buffer_data_1[] = {
        0.0f,0.5f,0.0f,
        0.1f,0.5f,0.0f,
        0.0f,2.0f,0.0f,

        0.1f,0.5f,0.0f,
        0.0f,2.0f,0.0f,
        0.1f,2.0f,0.0f,

        0.1f, 1.0f, 0.0f,
        0.3f, 1.5f, 0.0f,
        0.1f, 2.0f, 0.0f,
    };

    for (int i=0 ;i<90;i++){
        vertex_buffer_data[i]=4*vertex_buffer_data[i];
    }
    for (int i=0;i<27;i++){
        vertex_buffer_data_1[i]=4*vertex_buffer_data_1[i];
    }
    color_t arr[]={color,COLOR_YELLOW,COLOR_LGREEN};
    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, arr, GL_FILL,24,18);
    this->object1 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_1, COLOR_BLACK, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we want to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    this->position.y += this->speedY;
    if(this->position.y>-0.5)// || (this->position.x>-2.3 && this->position.x<0.7 && this->position.y<-1.5))
    {
        this->speedY += this->accY;
//        printf("haha");
    }
    else
    {
        this->position.y=-0.5;
        this->speedY = 0;
        this->fl=1;
//        flag=0;
    }
//    if (this->position.y<-0.5){
//    this->position.y += 0.002;
//    }
//    else{
//        this->position.y -= 0.002;
//    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z = this->position.z;
//    float ht = this->hieght;
    bounding_box_t bbox = { x, y, z, 8,8,6 };
    return bbox;
}
