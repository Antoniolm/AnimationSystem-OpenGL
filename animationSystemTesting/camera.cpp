// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "camera.h"

Camera::Camera(){
    viewMode=false;
    currentTime=SDL_GetTicks();
    viewDelay=currentTime;
}

//**********************************************************************//

Camera::Camera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    target=aTarget;
    up=aUp;
    viewMode=false;

    createCamera();
    currentTime=SDL_GetTicks();
    viewDelay=currentTime;
}

//**********************************************************************//

Camera::~Camera()
{
    //dtor
}

//**********************************************************************//

void Camera::setCamera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    target=aTarget;
    up=aUp;

}

//**********************************************************************//

void Camera::setPerspectiveProjection(float fov, float aspect, float nearPro, float farPro){
    float f=(float) 1/tan((fov * 3.1416) / 360.0);

    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=f/(aspect);  projec[1]=0;        projec[2]=0;                          projec[3]=0;
	projec[4]=0;                projec[5]=f;   projec[6]=0;                          projec[7]=0;
	projec[8]=0;                projec[9]=0;   projec[10]=(farPro+nearPro)/(nearPro-farPro);    projec[11]=-1.0f;
	projec[12]=0;               projec[13]=0;  projec[14]=(2.0f*farPro*nearPro)/(nearPro-farPro); projec[15]=0;

    perspecProjection.setMatrix(projec);
}

//**********************************************************************//

void Camera::setOrthographicProjection(float left,float right,float bottom,float top,float nearPro,float farPro){

    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=2.0f/(right-left);        projec[1]=0;                        projec[2]=0;                 projec[3]=((right+left)/(right-left));
	projec[4]=0;                        projec[5]=2.0f/(top-bottom);        projec[6]=0;                 projec[7]=((top+bottom)/(top-bottom));
	projec[8]=0;                        projec[9]=0;                        projec[10]=-2.0f/(farPro-nearPro); projec[11]=-(farPro+nearPro)/(farPro-nearPro);
	projec[12]=0;                       projec[13]=0;                       projec[14]=0;                projec[15]=1;

	orthoProjection.setMatrix(projec);
}

//**********************************************************************//

void Camera::createCamera(){
    vec3f zCamera;
    vec3f yCamera;
    vec3f xCamera;

    //Calculate the z-Axis
    zCamera=position-target;
    zCamera.normalize();

    //Calculate the x-Axis
    xCamera=up.cross(zCamera);
    xCamera.normalize();

    //Calculate the y-Axis
    yCamera=zCamera.cross(xCamera);

    //Create the camera
    GLfloat * matrix=new GLfloat[16];
    matrix[0]=xCamera.x;  matrix[1]=yCamera.x;  matrix[2]=zCamera.x;  matrix[3]=0;
	matrix[4]=xCamera.y;  matrix[5]=yCamera.y;  matrix[6]=zCamera.y;  matrix[7]=0;
	matrix[8]=xCamera.z;  matrix[9]=yCamera.z;  matrix[10]=zCamera.z; matrix[11]=0;
	matrix[12]=-(xCamera.dot(position)); matrix[13]=-(yCamera.dot(position)); matrix[14]=-(zCamera.dot(position)); matrix[15]=1;

	camera.setMatrix(matrix);
}

//**********************************************************************//

void Camera::activateCamera(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,camera.getMatrix());
}

//**********************************************************************//

void Camera::activateOrthoProjection(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projection"),1,GL_FALSE,orthoProjection.getMatrix());
}

//**********************************************************************//

void Camera::activatePerspecProjection(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projection"),1,GL_FALSE,perspecProjection.getMatrix());
}

//**********************************************************************//

void Camera::update(const Uint8* currentKeyStates,GLuint shaderID){

    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_w)]){
        position.y+=0.01; target.y+=0.01;
    }
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)]){
        position.y-=0.01; target.y-=0.01;
    }
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)]){
        position.x-=0.01; target.x-=0.01;
    }
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_d)]){
        position.x+=0.01; target.x+=0.01;
    }
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_q)]){
        position.z+=0.01; target.z+=0.01;
    }
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_e)]){
        position.z-=0.01; target.z-=0.01;
    }


    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_i)])
        target.y+=0.03;
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_k)])
        target.y-=0.03;
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_j)])
        target.x-=0.03;
    if (currentKeyStates[SDL_GetScancodeFromKey(SDLK_l)])
        target.x+=0.03;

    createCamera();

    glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,camera.getMatrix());
    glUniform3f(glGetUniformLocation(shaderID, "viewPos"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shaderID, "viewPosVertex"), position.x, position.y, position.z);
}

//**********************************************************************//

Matrix4f & Camera::getCamera(){
    return camera;
}

//**********************************************************************//

GLfloat * Camera::getView(){
    return camera.getMatrix();
}

//**********************************************************************//

Matrix4f & Camera::getOrthoProyection(){
    return orthoProjection;
}

//**********************************************************************//

vec3f Camera::getPosition(){
    return position;
}

//**********************************************************************//

vec3f Camera::getTarget(){
    return target;
}

//**********************************************************************//

vec3f Camera::getUp(){
    return up;
}

//**********************************************************************//

bool Camera::isViewMode(){
    return viewMode;
}

//**********************************************************************//

void Camera::setPosition(vec3f aPosition,GLuint shaderID){

    position=vec3f(aPosition.x,aPosition.y+8.0f,aPosition.z+13.0f); //test camera
    target=aPosition;

    createCamera();//Create camera

    glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,camera.getMatrix());
    glUniform3f(glGetUniformLocation(shaderID, "viewPos"), position.x, position.y, position.z);
}
