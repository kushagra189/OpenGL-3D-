#include "zelda.h"
#include "main.h"

Zelda::Zelda(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->accY = -0.03;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[] = {
       -1.0f,-1.0f,-1.0f, // triangle 1 : begin
       -1.0f,-1.0f, 1.0f,
       -1.0f, 1.0f, 1.0f, // triangle 1 : end
       1.0f, 1.0f,-1.0f, // triangle 2 : begin
       -1.0f,-1.0f,-1.0f,
       -1.0f, 1.0f,-1.0f, // triangle 2 : end
       1.0f,-1.0f, 1.0f, //2
       -1.0f,-1.0f,-1.0f,
       1.0f,-1.0f,-1.0f,
       1.0f, 1.0f,-1.0f,
       1.0f,-1.0f,-1.0f,
       -1.0f,-1.0f,-1.0f,//2end
       -1.0f,-1.0f,-1.0f,//3
       -1.0f, 1.0f, 1.0f,
       -1.0f, 1.0f,-1.0f,
       1.0f,-1.0f, 1.0f,
       -1.0f,-1.0f, 1.0f,
       -1.0f,-1.0f,-1.0f,//3end
       -1.0f, 1.0f, 1.0f,//4
       -1.0f,-1.0f, 1.0f,
       1.0f,-1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       1.0f,-1.0f,-1.0f,
       1.0f, 1.0f,-1.0f,//4end
       1.0f,-1.0f,-1.0f,//5
       1.0f, 1.0f, 1.0f,
       1.0f,-1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f,-1.0f,
       -1.0f, 1.0f,-1.0f,//5end
       1.0f, 1.0f, 1.0f,//6
       -1.0f, 1.0f,-1.0f,
       -1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       -1.0f, 1.0f, 1.0f,
       1.0f,-1.0f, 1.0f//6end
   };

   static GLfloat vertex_buffer_data_1[] = {
    -1,-1,-0,
    -0.8,-1,0,
    -0.8,-3,0,
    -1,-1,0,
    -1,-3,0,
    -0.8,-3,0,
    
    0.8,-1,0,
    1,-1,-0,
    1,-3,0,
    0.8,-1,0,
    0.8,-3,-0,
    1,-3,0,
   };

   for(int i=0;i<108;i++)
   {
    vertex_buffer_data[i]=2*vertex_buffer_data[i];
   }

   for(int i=0;i<36;i++)
   {
    vertex_buffer_data_1[i]=2*vertex_buffer_data_1[i];
   }

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_1, COLOR_BLACK, GL_FILL);
}

void Zelda::draw(glm::mat4 VP) {
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

void Zelda::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Zelda::tick() {
    this->position.y += this->speedY;
    if(this->position.y>5)// || (this->position.x>-2.3 && this->position.x<0.7 && this->position.y<-1.5))
    {
        this->speedY += this->accY;
//        printf("haha");
    }
    else
    {
        this->position.y=5;
        this->speedY = 0;
        this->fl=1;
//        flag=0;
    }
}

bounding_box_t Zelda::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float z = this->position.z;
//    float ht = this->hieght;
    bounding_box_t bbox = { x, y, z, 8,8,6 };
    return bbox;
}
