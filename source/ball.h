#include "main.h"

#ifndef BALL_H
#define BALL_H
#define GLM_ENABLE_EXPERIMENTAL 

class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, int ball_type);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(Ball);
    bool detect_collision(Ball ball);
    double speed;
private:
    VAO *object;
};

class Box_maze {
public:
    Box_maze() {}
    Box_maze(float x, float y, float z, color_t color, int is_obstacle);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool detect_collision(Ball ball);
    // bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

class PowerUp {
public:
    PowerUp() {}
    PowerUp(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool detect_collision(Ball ball);
    // bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

class Button {
public:
    Button() {}
    Button(float x, float y, float z, color_t color,int button_type);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool detect_collision(Ball ball);
    // bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

#endif 
