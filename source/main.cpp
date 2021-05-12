#include "main.h"
#include "timer.h"
#include "ball.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#	pragma warning(disable: 4996) // Disable the fopen, strcpy, sprintf being unsafe warning
#endif

#include <math.h>
#include <unistd.h>
#define GLT_IMPLEMENTATION
#include "gltext.h" /* https://github.com/vallentin/glText */



using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
// Constants
float displacement = 0.05f, Y_max = 3.5f, Y_min = -4.0f, Z_min = 4.0f, Z_max = -3.5f;
int num_of_boxes=0,num_of_pups=0,num_of_obstacles=0,pup_taken=0,vap_taken=0,make_obstacle=0,SCORE=1000,time_remaining=2500,num_of_tasks=0,is_won=0,is_timeup=0,is_gameover=0,show_window=250;

// Objects
Ball ball1,ball2;           //ball1 is crewmate and ball2 is imposter
Box_maze maze[10000],obstacle[1000];
PowerUp pups[1000];
Button pup_button,exit_button,vaporiser;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(is_gameover || is_timeup || is_won)
    {

    }
    else
    {
        ball1.draw(VP);
        exit_button.draw(VP);
        if(vap_taken==0)
        {
            ball2.draw(VP);
            vaporiser.draw(VP);
        }
        for(int i=0;i<num_of_boxes;i++)
        {
            maze[i].draw(VP);
        }

        //show the power-ups only when u have taken the power-up enabler 
        if(pup_taken==1)
        {
            for(int i=0;i<num_of_pups;i++)
            {
                pups[i].draw(VP);
            }
        }
        else
        {
            pup_button.draw(VP);
        }
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    if (left && is_timeup ==0 && is_gameover==0 && is_won==0) 
    {
        if(ball1.position.z + 0.5f < Z_min)
        {    
            ball1.position.z += displacement;
            int flag = 0;
            for(int i=0;i<num_of_boxes;i++)
            {
                if((ball1.position.y - maze[i].position.y)*(ball1.position.y - maze[i].position.y) + (ball1.position.z - maze[i].position.z)*(ball1.position.z - maze[i].position.z) < 0.2f)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                ball1.position.z -= displacement;
            }
        }
    }
    else if(right && is_timeup ==0 && is_gameover==0 && is_won==0)
    {
        if(ball1.position.z - 0.5f > Z_max)
        {
            ball1.position.z -= displacement; 
            int flag = 0;
            for(int i=0;i<num_of_boxes;i++)
            {
                if((ball1.position.y - maze[i].position.y)*(ball1.position.y - maze[i].position.y) + (ball1.position.z - maze[i].position.z)*(ball1.position.z - maze[i].position.z) < 0.2f)
                {
                    flag=1;
                    break;
                }
            } 
            if(flag==1)
            {
                ball1.position.z += displacement; 
            }  
        }
    }
    else if(up && is_timeup ==0 && is_gameover==0 && is_won==0)
    {
        if(ball1.position.y + 0.5f < Y_max)
        {
            ball1.position.y += displacement; 
            int flag = 0;
            for(int i=0;i<num_of_boxes;i++)
            {
                if((ball1.position.y - maze[i].position.y)*(ball1.position.y - maze[i].position.y) + (ball1.position.z - maze[i].position.z)*(ball1.position.z - maze[i].position.z) < 0.2f)
                {
                    flag=1;
                    break;
                }
            } 
            if(flag==1)
            {
                ball1.position.y -= displacement; 
            }  
        }
    }
    else if(down && is_timeup ==0 && is_gameover==0 && is_won==0)
    {
        if(ball1.position.y - 0.5f > Y_min)
        {
            ball1.position.y -= displacement;
            int flag = 0;
            for(int i=0;i<num_of_boxes;i++)
            {
                if((ball1.position.y - maze[i].position.y)*(ball1.position.y - maze[i].position.y) + (ball1.position.z - maze[i].position.z)*(ball1.position.z - maze[i].position.z) < 0.2f)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                ball1.position.y += displacement;   
            }
        }
    }

    // detecting collision with the vaporiser
    if(vap_taken==0)
    {
        vap_taken = vaporiser.detect_collision(ball1);
        if(vap_taken)
        {
            num_of_tasks++;
        }
        is_gameover = ball2.detect_collision(ball1);
    }

    // detection of collision with power_up enabler button(after u have taken the power-up enabler no need to check again)
    if(pup_taken==0)
    {
        pup_taken = pup_button.detect_collision(ball1);
    }
    else 
    {
        if(make_obstacle==0)
        {
            for(int i=0;i<num_of_obstacles;i++)
            {
                maze[num_of_boxes++]=obstacle[i];
            }
            make_obstacle=1;
        }
        if(num_of_pups>0)
        {
            // detecting collision with the power-ups
            int which_pos=-1,i;
            for(i=0;i<num_of_pups;i++)
            {
                if(fabs(ball1.position.y-pups[i].position.y)<0.25f && fabs(ball1.position.z-pups[i].position.z)<0.25f)
                {
                    which_pos=i;
                    break;
                }
            }
            if(which_pos!=-1)
            {
                // power-up is taken so increase the score
                SCORE+=250;
                for(i=0;i<num_of_pups-1;i++)
                {
                    if(i>=which_pos)
                    {
                        pups[i]=pups[i+1];
                    }
                }
                num_of_pups--;
            }
        }
        else
        {
            if(num_of_tasks==1)
            {
                num_of_tasks=2;
            }
            else if(num_of_tasks==0)
            {
                num_of_tasks=1;
            }
        }

        // detection of collision with obstacle-bricks
        for(int i=0;i<num_of_obstacles;i++)
        {
            if(fabs(ball1.position.y-obstacle[i].position.y)<0.5f && fabs(ball1.position.z-obstacle[i].position.z)<0.5f)
            {
                SCORE-=5;
            }
            SCORE=max(SCORE,0);
        }

        // exiting the game if reached the exit-gate
        if(exit_button.detect_collision(ball1) && num_of_pups==0 && vap_taken==1)
        {
            is_won=1;
        }
    }
    if(time_remaining==0 || SCORE==0)
    {
        if(time_remaining==0)
        {
            is_timeup=1;
        }
        else 
        {
            is_gameover=1;
        }
    }
    if(is_won || is_timeup || is_gameover)
    {   
        // do nothing
    }
    else
    {
        time_remaining--;
    }
}

void tick_elements() {
    ball2.tick(ball1);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, Y_min+0.5f, Z_min-0.5f,0);
    // ball2 = Ball(0, Y_max-0.5f, Z_min-0.5f,1);
    exit_button = Button(0,Y_max-0.5f,Z_max+0.5f,COLOR_SILVER,-1);

    // creating the maze
    for(float j=Z_max; j<=Z_min; j+=0.5f)
    {
        maze[num_of_boxes++] = Box_maze(0, Y_min, j, COLOR_BLACK,0);
        maze[num_of_boxes++] = Box_maze(0, Y_max, j, COLOR_BLACK,0);   
    }

    for(float i=Y_min+0.5f ; i<=Y_max-0.5f; i+=0.5f)
    {
        maze[num_of_boxes++] = Box_maze(0, i, Z_max, COLOR_BLACK,0);
        maze[num_of_boxes++] = Box_maze(0, i, Z_min, COLOR_BLACK,0);
    }

    // creating maze-boxes inside
    int k=50,f;
    float pos_y,pos_z;
    while(k)
    {
        while(1)
        {
            f=0;
            pos_y = -3.5f + 0.5f*(rand()%15);
            pos_z = -3.0f + 0.5f*(rand()%14);

            f=0;
            for(int i=0;i<num_of_boxes;i++)
            {
                if(maze[i].position.y==pos_y && maze[i].position.z==pos_z)
                {
                    f=1;
                    break;
                }
            }
            for(int i=0;i<num_of_obstacles;i++)
            {
                if(obstacle[i].position.y==pos_y && obstacle[i].position.z==pos_z)
                {
                    f=1;
                    break;
                }
            }
            if(f==0 && pos_y!=ball1.position.y && pos_z!=ball1.position.z && pos_y!=exit_button.position.y && pos_z!=exit_button.position.z)
            {
                if(pos_y>= Y_max -1.5f && pos_z>= Z_min-1.5f)
                {
                    // text rendering is happening at this position
                }
                else
                {
                    break;
                }
            }
        }
        if(rand()%5 == 0)
        {
            obstacle[num_of_obstacles++] = Box_maze(0,pos_y,pos_z,COLOR_MAROON,1);
        }
        else
        {
            maze[num_of_boxes++] = Box_maze(0,pos_y,pos_z,COLOR_BLACK, 0);
        }
        k--;
    }

    // creating power-ups
    k=10;
    while(k)
    {
        while(1)
        {
            pos_y = -4.0f + 0.5f*(rand()%16);
            pos_z = -3.5f + 0.5f*(rand()%16);
            f=0;
            for(int i=0;i<num_of_boxes;i++)
            {
                if(maze[i].position.y==pos_y && maze[i].position.z==pos_z)
                {
                    f=1;
                    break;
                }
            }
            for(int i=0;i<num_of_obstacles;i++)
            {
                if(obstacle[i].position.y==pos_y && obstacle[i].position.z==pos_z)
                {
                    f=1;
                    break;
                }
            }
            for(int i=0;i<num_of_pups;i++)
            {
                if(pups[i].position.y==pos_y && pups[i].position.z==pos_z)
                {
                    f=1;
                    break;
                }
            }
            if(f==0 && pos_y!=ball1.position.y && pos_z!=ball1.position.z && pos_y!=exit_button.position.y && pos_z!=exit_button.position.z)
            {
                if(pos_y>= Y_max -1.5f && pos_z>= Z_min-1.5f)
                {
                    // text rendering is happening at this position
                }
                else
                {
                    break;
                }
            }
        }
        int which_color = rand()%3;
        if(which_color==0)
        {
            pups[num_of_pups++] = PowerUp(0,pos_y,pos_z,COLOR_BLUE);
        }
        else if(which_color==1)
        {
            pups[num_of_pups++] = PowerUp(0,pos_y,pos_z,COLOR_GREEN);
        }
        else
        {
            pups[num_of_pups++] = PowerUp(0,pos_y,pos_z,COLOR_YELLOW);
        }
        k--;
    }

    // creating power-up enabler button
    while(1)
    {
        pos_y = -4.0f + 0.5f*(rand()%16);
        pos_z = -3.5f + 0.5f*(rand()%16);
        f=0;
        for(int i=0;i<num_of_boxes;i++)
        {
            if(maze[i].position.y==pos_y && maze[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        for(int i=0;i<num_of_obstacles;i++)
        {
            if(obstacle[i].position.y==pos_y && obstacle[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        for(int i=0;i<num_of_pups;i++)
        {
            if(pups[i].position.y==pos_y && pups[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        if(f==0 && pos_y!=ball1.position.y && pos_z!=ball1.position.z && pos_y!=exit_button.position.y && pos_z!=exit_button.position.z)
        {
           if(pos_y>= Y_max -1.5f && pos_z>= Z_min-1.5f)
            {
                // text rendering is happening at this position
            }
            else
            {
                break;
            }
        }
    }
    pup_button = Button(0,pos_y,pos_z,COLOR_GOLD,1);


    // creating vaporiser button
    while(1)
    {
        pos_y = -4.0f + 0.5f*(rand()%16);
        pos_z = -3.5f + 0.5f*(rand()%16);
        f=0;
        for(int i=0;i<num_of_boxes;i++)
        {
            if(maze[i].position.y==pos_y && maze[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        for(int i=0;i<num_of_obstacles;i++)
        {
            if(obstacle[i].position.y==pos_y && obstacle[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        for(int i=0;i<num_of_pups;i++)
        {
            if(pups[i].position.y==pos_y && pups[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        if(f==0 && pos_y!=ball1.position.y && pos_z!=ball1.position.z && pos_y!=exit_button.position.y && pos_z!=exit_button.position.z && pos_y!=pup_button.position.y && pos_z!=pup_button.position.z)
        {
            if(pos_y>= Y_max -1.5f && pos_z>= Z_min-1.5f)
            {
                // text rendering is happening at this position
            }
            else
            {
                break;
            }
        }
    }
    vaporiser = Button(0,pos_y,pos_z,COLOR_PINK,0);

    // randomly creating position for imposter
    while(1)
    {
        pos_y = -4.0f + 0.5f*(rand()%16);
        pos_z = -3.5f + 0.5f*(rand()%16);
        f=0;
        for(int i=0;i<num_of_boxes;i++)
        {
            if(maze[i].position.y==pos_y && maze[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        for(int i=0;i<num_of_obstacles;i++)
        {
            if(obstacle[i].position.y==pos_y && obstacle[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        for(int i=0;i<num_of_pups;i++)
        {
            if(pups[i].position.y==pos_y && pups[i].position.z==pos_z)
            {
                f=1;
                break;
            }
        }
        if(f==0 && pos_y!=ball1.position.y && pos_z!=ball1.position.z && pos_y!=exit_button.position.y && pos_z!=exit_button.position.z && pos_y!=pup_button.position.y && pos_z!=pup_button.position.z && pos_y!=vaporiser.position.y && pos_z!=vaporiser.position.z)
        {
            break;
        }
    }
    ball2 = Ball(0, pos_y, pos_z,1);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    
    if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return EXIT_FAILURE;
	}

    window = initGLFW(width, height);

    initGL (window, width, height);

    if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	int viewportWidth, viewportHeight,i=0;
	double time;
    GLTtext *text = gltCreateText();
    while (!glfwWindowShouldClose(window) && show_window) {
        if (t60.processTick()) {
            // Process timers
            time = glfwGetTime();

            // 60 fps
            // OpenGL Draw commands
            draw();

            std::string  title = "Health:" + std::to_string(SCORE) + "\nTasks:" + std::to_string(num_of_tasks) + "/2\nTime:" + std::to_string(time_remaining) + "\nLighting: On";
            const char *this_text = title.c_str();
            gltSetText(text, this_text);

            glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
            glViewport(0, 0, viewportWidth, viewportHeight);
            
            gltBeginDraw();

            gltColor(
            cosf((float)time) * 0.5f + 0.5f,
            sinf((float)time) * 0.5f + 0.5f,
            1.0f,
            1.0f);

            gltDrawText2DAligned(text,
            (GLfloat)(viewportWidth / 6.9),
                (GLfloat)(viewportHeight / 8.4),
                1.0f,
                GLT_CENTER, GLT_CENTER);

            if(is_gameover || is_timeup || is_won)
            {
                show_window--;
                if(is_timeup)
                {
                    gltSetText(text, "TimeUp :-0");   
                }
                else if(is_gameover)
                {
                    gltSetText(text, "GameOver :-(");
                }
                else
                {
                    gltSetText(text, "YouWon!!!");
                }
                gltColor(
                cosf((float)time) * 0.5f + 0.5f,
                sinf((float)time) * 0.5f + 0.5f,
                1.0f,
                1.0f);

                // 2.15,8.4
                gltDrawText2DAligned(text,
                (GLfloat)(viewportWidth / 2),
                    (GLfloat)(viewportHeight / 2),
                    4.0f,
                    GLT_CENTER, GLT_CENTER);
            }

            gltEndDraw();

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        if( i%100000 == 0){
			glfwSetWindowTitle(window,"\"Among Us\"");
					
		}
        i++;
    }
    gltDeleteText(text); 
    gltTerminate();
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
