#include "ball.h"
#include "main.h"

#define GLM_ENABLE_EXPERIMENTAL 

Ball::Ball(float x, float y, float z, int ball_type) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    
    static const GLfloat vertex_buffer_data[] = {
        // head
        0.0f,0.4f,0.0f,
        0.0f,0.475f,-0.125f,
        0.0f,0.4f,-0.25f,

        0.0f,0.475f,-0.325f,
        0.0f,0.475f,-0.125f,
        0.0f,0.4f,-0.25f,

        0.0f,0.475f,-0.325f,
        0.0f,0.4f,-0.5f,
        0.0f,0.4f,-0.25f,

        // left leg
        0.0f,0.1f,0.0f, 
        0.0f,0.1f, -0.2f,
        0.0f, 0.2f, 0.0f,

        0.0f,0.2f,-0.2f, 
        0.0f,0.1f, -0.2f,
        0.0f, 0.2f, 0.0f,

        // right leg
        0.0f,0.1f,-0.3f,
        0.0f,0.1f,-0.5f,
        0.0f,0.2f,-0.3f,

        0.0f,0.2f,-0.5f,
        0.0f,0.1f,-0.5f,
        0.0f,0.2f,-0.3f,
       
        // middle body
        0.0f,0.2f,0.0f,
        0.0f,0.4f,0.0f,
        0.0f,0.2f,-0.5f,

        0.0f,0.4f,-0.5f,
        0.0f,0.4f,0.0f,
        0.0f,0.2f,-0.5f,

        // helmet
        0.0f,0.3f,-0.3f,
        0.0f,0.4f,-0.3f,
        0.0f,0.3f,-0.5f,

        0.0f,0.4f,-0.5f,
        0.0f,0.4f,-0.3f,
        0.0f,0.3f,-0.5f,
    };

    if(ball_type == 0)
    {
        static const GLfloat color_buffer_data[] = {
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f, 

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f, 

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,
            0.0f,1.0f,1.0f,

            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,

            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,
        };

        this->object = create3DObject(GL_TRIANGLES, 11*3, vertex_buffer_data, color_buffer_data, GL_FILL);
    }
    else
    {
        static const GLfloat color_buffer_data[] = {
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,
            1.0f,0.0f,0.0f,

            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,

            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,
            0.8f,0.8f,0.77f,
        };

        this->object = create3DObject(GL_TRIANGLES, 11*3, vertex_buffer_data, color_buffer_data, GL_FILL);   
    }
}

void Ball::draw(glm::mat4 VP) {
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

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick(Ball crewmate) {
    int move_y=0,move_z=-1;
    float displacement = 0.025f;
    if(crewmate.position.y> this->position.y)
    {
        move_y = 1;
    }
    else if(crewmate.position.y< this->position.y)
    {
        move_y = -1;
    }

    if(crewmate.position.z> this->position.z)
    {
        move_z = 1;
    }
    else if(crewmate.position.z< this->position.z)
    {
        move_z = -1;
    }

    this->position.y += displacement*move_y;
    this->position.z += displacement*move_z;
}

bool Ball::detect_collision(Ball ball){
   if(fabs(ball.position.y-this->position.y)<0.1f && fabs(ball.position.z-this->position.z)<0.1f)
   {
       return 1;
   }
   else
   {
       return 0;
   }
}



// Maze block
Box_maze::Box_maze(float x, float y, float z, color_t color, int is_obstacle) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    
    if(is_obstacle==0)
    {
        GLfloat vertex_buffer_data[] ={ 
        0.0f,0.0f,0.0f, 
        0.0f,0.5f, 0.0f,
        0.0f, 0.0f, -0.5f,

        0.0f,0.5f,-0.5f, 
        0.0f,0.5f, 0.0f,
        0.0f, 0.0f, -0.5f
        }; 
        this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    }
    else
    {
        GLfloat vertex_buffer_data[] ={
            0.0f, 0.0f, -0.25f,
            0.0f, 0.125f, -0.5f,
            0.0f, 0.25f, -0.25f,

            0.0f, 0.0f, -0.25f,
            0.0f, 0.125f, 0.0f,
            0.0f, 0.25f, -0.25f,

            0.0f, 0.25f, -0.25f,
            0.0f, 0.375f, -0.5f,
            0.0f, 0.5f, -0.25f,

            0.0f, 0.25f, -0.25f,
            0.0f, 0.375f, 0.0f,
            0.0f, 0.5f, -0.25f 
        };
        static const GLfloat color_buffer_data[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,

            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,

            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,

            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
        };
        this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color_buffer_data, GL_FILL);
    }
}

void Box_maze::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Box_maze::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}





// PowerUp
PowerUp::PowerUp(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    
    GLfloat vertex_buffer_data[10000];
    GLfloat color_buffer_data[10000];
    float angle = (15 *3.14159)/180,curr_angle=0.0,radius=0.25;
    for(int i=0;i<24;i++)
    {
        curr_angle=(i+1)*angle;
        vertex_buffer_data[9*i]=0.0f;
        vertex_buffer_data[9*i+1]=0.0f + 0.25f;
        vertex_buffer_data[9*i+2]=0.0f - 0.25f;

        vertex_buffer_data[9*i+3]=0.0f;
        vertex_buffer_data[9*i+4]=  radius*sin(curr_angle) + 0.25f;
        vertex_buffer_data[9*i+5]= -radius*cos(curr_angle) - 0.25f;

        vertex_buffer_data[9*i+6]=0.0f;
        vertex_buffer_data[9*i+7]=  radius*sin(curr_angle-angle) + 0.25f;
        vertex_buffer_data[9*i+8]= -radius*cos(curr_angle-angle) - 0.25f;

        color_buffer_data[9*i]=0.0f;
        color_buffer_data[9*i+1]=0.0f;
        color_buffer_data[9*i+2]=1.0f;

        color_buffer_data[9*i+3]=1.0f;
        color_buffer_data[9*i+4]=0.0;
        color_buffer_data[9*i+5]=0.0f;

        color_buffer_data[9*i+6]=0.0f;
        color_buffer_data[9*i+7]=1.0;
        color_buffer_data[9*i+8]=0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, 3*24, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void PowerUp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void PowerUp::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}


// Creting Power-Up enabler button and Vaporise imposter button
Button::Button(float x, float y, float z, color_t color, int button_type) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    // power-up button
    if(button_type==1)
    {
        GLfloat vertex_buffer_data[] ={ 
        0.0f,0.25f,0.0f,
        0.0f,0.0f,-0.25f,
        0.0f,0.5f,-0.25f,

        0.0f,0.25f,-0.5f,
        0.0f,0.0f,-0.25f,
        0.0f,0.5f,-0.25f,
        }; 
        this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    }
    else if(button_type==-1)            //exit button
    {
        GLfloat vertex_buffer_data[] ={ 
        0.0f,0.0f,0.0f,
        0.0f,0.0f,-0.5f,
        0.0f,0.25f,-0.25f,

        0.0f,0.5f,0.0f,
        0.0f,0.5f,-0.5f,
        0.0f,0.25f,-0.25f,
        }; 
        this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    }
    else if(button_type==0)            //vaporiser button
    {
        GLfloat vertex_buffer_data[10000];
        float angle = (15 *3.14159)/180,curr_angle=0.0,radius=0.25;
        for(int i=0;i<24;i++)
        {
            curr_angle=(i+1)*angle;
            vertex_buffer_data[9*i]=0.0f;
            vertex_buffer_data[9*i+1]=0.0f + 0.25f;
            vertex_buffer_data[9*i+2]=0.0f - 0.25f;

            vertex_buffer_data[9*i+3]=0.0f;
            vertex_buffer_data[9*i+4]=  radius*sin(curr_angle) + 0.25f;
            vertex_buffer_data[9*i+5]= -radius*cos(curr_angle) - 0.25f;

            vertex_buffer_data[9*i+6]=0.0f;
            vertex_buffer_data[9*i+7]=  radius*sin(curr_angle-angle) + 0.25f;
            vertex_buffer_data[9*i+8]= -radius*cos(curr_angle-angle) - 0.25f;
        }
        this->object = create3DObject(GL_TRIANGLES, 3*24, vertex_buffer_data, color, GL_FILL);
    }             
}

void Button::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Button::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bool Button::detect_collision(Ball ball){
    if(fabs(ball.position.y-this->position.y)<0.25f && fabs(ball.position.z-this->position.z)<0.25f){
        return 1;
    }
    else{
        return 0;
    }  
}