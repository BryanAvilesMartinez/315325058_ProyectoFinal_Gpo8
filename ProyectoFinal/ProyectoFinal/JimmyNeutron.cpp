// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0;
bool anim = false;
bool anim2= true;

//Animacion Cohete
float CoheteX = 0;
float CoheteY = 0;
float CoheteZ = 0;
float CoheteRotZ = 0;
float CoheteRotY = 0;
bool bool_cohete = false;
bool Cdesplazamiento1 = true;
bool Cdesplazamiento2 = false;
bool Cdesplazamiento3 = false;
bool Cdesplazamiento4 = false;
bool Cdesplazamiento5 = false;
bool Cdesplazamiento6 = false;
bool Cdesplazamiento7 = false;
bool Cdesplazamiento8 = false;
bool Cdesplazamiento9 = false;
bool Cdesplazamiento10 = false;


//Animaciones Silla
float rotSilla = 0;
float SillaZ = 0;
bool bool_sillaZ = false;
bool bool_sillaRot = false;

//Animacion Planetario
bool bool_Planet = false;
float PlanetRot = 0;
bool Pdesplazamiento1 = true;
bool Pdesplazamiento2 = false;


//Animacion Alien
bool bool_Alien = false;
float AlienX = 0;
float AlienRotY = 0;
bool Adesplazamiento1 = true;
bool Adesplazamiento2 = false;
bool Adesplazamiento3 = false;
bool Adesplazamiento4 = false;


int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
   // glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    //glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
   // glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    //glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Casa Jimmy Neutron", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");

    // Load models
    Model escritorio((char*)"Models/Pokeball2/escritorio.obj");
    Model silla((char*)"Models/Pokeball2/silla.obj");
    Model compu((char*)"Models/computadora/computadora.obj");
    Model cohete((char*)"Models/cohete/cohete.obj");
    Model extraterrestre1((char*)"Models/extraterrestre/bag.obj");
    Model carrusel((char*)"Models/planetario/carrusel.obj");
    Model cama((char*)"Models/Cama/cama.obj");  //la cama es la casa
    Model piso((char*)"Models/Casa/piso.obj");
    Model cama1((char*)"Models/Casa/cama.obj");
    Model arbol((char*)"Models/arbol/Hazelnut.obj");
    Model Librero((char*)"Models/librero/librero.obj");
    Model Libro((char*)"Models/librero/libro.obj");
    Model Pizarra((char*)"Models/pizarron/pizarra.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        model = glm::translate(model,glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        model = glm::translate(model, glm::vec3(-1.0f, 0.3f, -3.0f));
        //model = glm:: rotate(model,glm::radians(rot),glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
       
        escritorio.Draw(shader);
        
        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(90.0f + rotSilla), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(2.0f, 0.5f, -4.9f + SillaZ));
        model = glm::scale(model, glm::vec3(3.0f, 3.5f, 3.0f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(shader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(3.0f, 5.0f, 2.0f));
        model = glm::scale(model, glm::vec3(1.5f, 1.5f,1.5f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        compu.Draw(shader);


        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(CoheteRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
        model = glm::rotate(model, glm::radians(-90.0f + CoheteRotY), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-1.5f, 1.42f + CoheteY, 0.5f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cohete.Draw(shader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(180.0f + AlienRotY), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(9.0f + AlienX, 3.2f, 5.5f));
        model = glm::scale(model, glm::vec3(2.5f, 4.0f, 2.5f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        extraterrestre1.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        model = glm::rotate(model, glm::radians(-90.0f + PlanetRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 4.6f, 5.0f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        carrusel.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
       // model = glm::rotate(model, glm::radians(-90.0f + PlanetRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-7.0f, -0.5f, 2.2f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        piso.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        // model = glm::rotate(model, glm::radians(-90.0f + PlanetRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 2.2f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cama.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        model = glm::translate(model, glm::vec3(-5.5f, 0.0f, -2.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cama1.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
        model = glm::translate(model, glm::vec3(-1.0f, 0.1f, -4.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Librero.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(4.0f, 2.2f, 0.8f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Libro.Draw(shader);

        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 4.2f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Pizarra.Draw(shader);
        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (anim && anim2)
    {
        if (rot < 46.0f) {
            rot += 0.3f;
            if (rot >= 45.0f)
                anim2 = false;
        }
    }

    if (anim ==true && anim2 ==false)
    {
       
            rot -= 0.3f;
        if (rot <= -45.0f)
            anim2 = true;
    }

    //Animacion Cohete
    if (bool_cohete == true) {

        if (Cdesplazamiento1 == true) {
            CoheteY += 0.009f;
            CoheteRotY += 1.1f;
            CoheteRotZ += 0.12f;

            if (CoheteY > 2.5) {
                Cdesplazamiento1 = false;
            }
        }
     
        
    }

    //Animacion Silla Traslación
    if (bool_sillaZ == true) {
        if (SillaZ > -2.5f){
            SillaZ -= 0.05f;
        }
    }

    //Animacion Silla Rotacion
    if (bool_sillaRot == true) {

        if (rotSilla > 10.0f) {
            bool_sillaRot == false;
        }
        else {
            rotSilla += 0.2f;
        }
    }

    //Animacion Planetario
    if(bool_Planet == true){

        if (Pdesplazamiento1 == true) {
            PlanetRot += 0.2f;

            if (PlanetRot > 35) {
                Pdesplazamiento2 = true;
                Pdesplazamiento1 = false;
            }
        }

        if (Pdesplazamiento2 == true) {
            PlanetRot -= 0.2f;

            if (PlanetRot < -15) {
                Pdesplazamiento1 = true;
                Pdesplazamiento2 = false;
            }
        }
    }

    //Animacion Alien
    if (bool_Alien == true) {

        if (Adesplazamiento1 == true) {
            AlienX += 0.05f;

            if (AlienX > 3) {
                Adesplazamiento2 = true;
                Adesplazamiento1 = false;
            }
        }

        if (Adesplazamiento2 == true) {
            AlienRotY -= 0.8f;

            if (AlienRotY < -45) {
                Adesplazamiento2 = false;
                Adesplazamiento3 = true;
            }
        }

        if (Adesplazamiento3 == true) {
            AlienRotY += 0.8f;

            if (AlienRotY > 0) {
                Adesplazamiento3 = false;
                Adesplazamiento2 = true;
            }
        }
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_O])
        anim = true;

    //Activar Anim Cohete
    if (keys[GLFW_KEY_L])
        bool_cohete = !bool_cohete;

    //Activar Anim Silla Rotacion
    if (keys[GLFW_KEY_K])
        bool_sillaRot = true;

    //Activar Anim Silla Traslacion
    if (keys[GLFW_KEY_J])
        bool_sillaZ = true;

    //Activar Anim Planetas
    if (keys[GLFW_KEY_H])
        bool_Planet = true;

    //Activar Anim Alien
    if (keys[GLFW_KEY_G])
        bool_Alien = true;
 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

