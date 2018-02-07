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

#ifndef CAMERA_H
#define CAMERA_H

#include "structdata.h"
#include "matrix4f.h"
#include "shader.h"
#include <glew.h>
#include <SDL.h>

class RootMap;
class Camera
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Camera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor with parameters
        *   \param eye -> Position of the camera
        *   \param Target -> Target of the camera
        *   \param up -> The inclination of the camera
        */
        //////////////////////////////////////////////////////////////////////////
        Camera(vec3f eye,vec3f aTarget,vec3f aUp);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Camera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param eye -> Position of the camera
        *   \param Target -> Target of the camera
        *   \param up -> The inclination of the camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setCamera(vec3f eye,vec3f aTarget,vec3f aUp);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the projection
        *   \param fov
        *   \param aspect
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPerspectiveProjection(float fov, float aspect, float nearPro, float farPro);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the projection
        *   \param left
        *   \param right
        *   \param bottom
        *   \param top
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setOrthographicProjection(float left,float right,float bottom,float top,float nearPro = -1.0f,float farPro = 1.0f );

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will create the matrix of the object
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createCamera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateCamera(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our current orthographic projection
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateOrthoProjection(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our current perspective projection
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatePerspecProjection(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will move the position of our camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void update(const Uint8* currentKeyStates,GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return our matrix camera
        *   \return Matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getCamera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return our camera
        *   \return GLfloat
         */
        //////////////////////////////////////////////////////////////////////////
        GLfloat * getView();

        Matrix4f & getOrthoProyection();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return the position of our camera
        *   \return vec3f
         */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return the target of our camera
        *   \return vec3f
         */
        //////////////////////////////////////////////////////////////////////////
        vec3f getTarget();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return the up of our camera
        *   \return vec3f
         */
        //////////////////////////////////////////////////////////////////////////
        vec3f getUp();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return if our camera is in viewMode or not
        *   \return bool
         */
        //////////////////////////////////////////////////////////////////////////
        bool isViewMode();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will set the position and direction of our camera
        *   \return void
         */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f aPosition,GLuint shaderID);

    protected:

    private:
        Matrix4f camera;
        Matrix4f orthoProjection,perspecProjection;
        vec3f position;
        vec3f target;
        vec3f up;
        bool viewMode;
        float currentTime,viewDelay;
};

#endif // CAMERA_H
