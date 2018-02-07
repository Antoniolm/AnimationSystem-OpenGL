#include <iostream>
#include <glew.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include "shader.h"
#include "texture.h"
#include <stdio.h>
#include <string>
#include "camera.h"
#include "camera2.h"
#include "shadowtexture.h"
#include "lightcamera.h"
// GLM Mathemtics
#include "./lib/glm/glm/glm.hpp"
#include "./lib/glm/glm/gtc/matrix_transform.hpp"
#include "./lib/glm/glm/gtc/type_ptr.hpp"
#include "./lib/glm/glm/ext.hpp"

using namespace std;
// Global variables
GLuint woodTexture;
GLuint planeVAO;
// Camera
Camera cameraMI(vec3f(0.0f, 6.0f, 12.0f),vec3f(0.0,0.0,0.0),vec3f(0.0,1.0,0.0));

GLuint loadTexture(string path);
void RenderScene(Shader &shader);
void RenderCube();

int main( int argc, char *argv[] )
{
    bool salida=true;
    SDL_Window * window;
    SDL_Event event;
    // Properties
    const GLuint SCR_WIDTH = 800, SCR_HEIGHT = 600;


    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Error: %s\n", SDL_GetError());
		salida=false;
	}
	else {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

        window = SDL_CreateWindow("Prueba", 20, 30, SCR_WIDTH,SCR_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			printf("SDL_Error: %s\n", SDL_GetError());
			salida=false;
		}
		else {
            //Initialize SDL_mixer
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 512 ) == -1 ){
                    cout<< "SDL_mixer could not initialize!"<<endl;
                    salida = false;
            }
			SDL_GLContext context = SDL_GL_CreateContext(window);
		}
	}

    /////////////////////////////////////////////////////////////

    glewInit();

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    Mix_AllocateChannels(16);

    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////


    // Define the viewport dimensions
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    // Setup and compile our shaders
    Shader shader("./shader/shadow_mapping.vs", "./shader/shadow_mapping.frag");
    Shader simpleDepthShader("./shader/shadow_mapping_depth.vs", "./shader/shadow_mapping_depth.frag");

    // Set texture samples
    glUseProgram(shader.getProgram()); //We use the program now
    glUniform1i(glGetUniformLocation(shader.getProgram(), "diffuseTexture"), 0);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "shadowMap"), 1);

    GLfloat planeVertices[] = {
        // Positions          // Normals         // Texture Coords
        10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
        -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
        -10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
        10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f,
        - 10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f
    };
    // Setup plane VAO
    GLuint planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glBindVertexArray(0);

    // Light source
    vec3f lightPosMI(-3.0f, 4.0f, -1.0f);
    // Load textures
    LightCamera cameraLightMI;
    woodTexture= loadTexture("./texture/wood.png");

    // Configure depth map FBO
    ShadowTexture * depthTexture=new ShadowTexture();

    bool isClosing=false;
    while (!isClosing)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isClosing = true;
            }
        }
        const Uint8* currentKeyStates=SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_w)]){
            lightPosMI.y+=0.01;
        }
        if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)]){
            lightPosMI.y-=0.01;
        }
        if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)]){
            lightPosMI.x-=0.01;
        }
        if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_d)]){
            lightPosMI.x+=0.01;
        }
        if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_w)]){
            lightPosMI.z+=0.01;
        }
        if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)]){
            lightPosMI.z-=0.01;
        }

        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /////////////////////////////////////////////////////////////////

         // 1. Render depth of scene to texture (from ligth's perspective)
        // - Get light projection/view matrix.
        GLfloat near_plane = -1.0f, far_plane = 10.0f;
        Matrix4f lightSpaceMatrix=cameraLightMI.createCamera(lightPosMI,vec3f(0.0,0.0,0.0),vec3f(0.0,1.0,0.0));
        lightSpaceMatrix.product(cameraLightMI.createOrtho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane).getMatrix());

        // - now render scene from light's point of view
        glUseProgram(simpleDepthShader.getProgram()); //We use the program now
        glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpaceMatrix.getMatrix());


        depthTexture->setShadowBuffer(true);
        RenderScene(simpleDepthShader);
        depthTexture->setShadowBuffer(false);

        // 2. Render scene as normal
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.getProgram()); //We use the program now

        cameraMI.setPerspectiveProjection(35.0f,(float)(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        cameraMI.activateCamera(shader.getProgram());
        cameraMI.activatePerspecProjection(shader.getProgram());
        // Set light uniforms
        glUniform3f(glGetUniformLocation(shader.getProgram(), "lightPos"),lightPosMI.x,lightPosMI.y,lightPosMI.z);
        glUniform3f(glGetUniformLocation(shader.getProgram(), "viewPos"),cameraMI.getPosition().x,cameraMI.getPosition().y,cameraMI.getPosition().z);
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpaceMatrix.getMatrix());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, woodTexture);
        glActiveTexture(GL_TEXTURE1);
        depthTexture->bindTexture();
        RenderScene(shader);

        cameraMI.update(SDL_GetKeyboardState(NULL),shader.getProgram());

        /////////////////////////////////////////////////////////////////
        SDL_GL_SwapWindow(window);
    }

    return 0;
}



void RenderScene(Shader &shader)
{
    // Floor
    glm::mat4 model;
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    // Cubes
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
    model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
    model = glm::scale(model, glm::vec3(0.5));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(0.0f, 1.3f, -4.0));
    model = glm::scale(model, glm::vec3(8.0,4.0,1.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(4.0f, 1.3f, 0.0));
    model = glm::scale(model, glm::vec3(1.0,4.0,8.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(-4.0f, 1.3f, 0.0));
    model = glm::scale(model, glm::vec3(1.0,4.0,8.0));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    RenderCube();
}

// RenderCube() Renders a 1x1 3D cube in NDC.
GLuint cubeVAO = 0;
GLuint cubeVBO = 0;
void RenderCube()
{
    // Initialize (if necessary)
    if (cubeVAO == 0)
    {
        GLfloat vertices[] = {
            // Back face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
            // Left face
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
            // Right face
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
            // Top face
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // Fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // Link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // Render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

// This function loads a texture from file. Note: texture loading functions like these are usually
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio).
// For learning purposes we'll just define it as a utility function.
GLuint loadTexture(string path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height, numComponents;
    unsigned char* data = stbi_load((path).c_str(), &width, &height, &numComponents, 4);

    if(data == NULL)
		std::cout << "Unable to load texture: " << path << std::endl;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    return textureID;
}




