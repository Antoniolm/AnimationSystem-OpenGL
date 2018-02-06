#include "lightcamera.h"

LightCamera::LightCamera()
{
    //ctor
}

LightCamera::~LightCamera()
{
    //dtor
}

Matrix4f LightCamera::createCamera(vec3f position,vec3f target,vec3f up){
    Matrix4f camera;
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
	matrix[12]=0.0; matrix[13]=0.0; matrix[14]=-(zCamera.dot(position)); matrix[15]=1;

	camera.setMatrix(matrix);

	return camera;

}
Matrix4f LightCamera::createOrtho(float left,float right,float bottom,float top,float nearPro,float farPro){
    Matrix4f orthoProjection;
    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=2.0f/(right-left);        projec[1]=0;                        projec[2]=0;                 projec[3]=((right+left)/(right-left));
	projec[4]=0;                        projec[5]=2.0f/(top-bottom);        projec[6]=0;                 projec[7]=((top+bottom)/(top-bottom));
	projec[8]=0;                        projec[9]=0;                        projec[10]=-2.0f/(farPro-nearPro); projec[11]=0.0;
	projec[12]=0;                       projec[13]=0;                       projec[14]=-(farPro+nearPro)/(farPro-nearPro);projec[15]=1;

	orthoProjection.setMatrix(projec);
	return orthoProjection;
}
