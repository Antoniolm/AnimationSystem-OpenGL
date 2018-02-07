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

#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <glew.h>
#include <math.h>
#include <iostream>
#include "structdata.h"

using namespace std;

class Matrix4f
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f(const Matrix4f & aMatrix);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Matrix4f();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a translation transform
        *    \param x,y,z -> Value for a translation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void translation(const float x,const float y, const float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a Scale transform
        *    \param x,y,z -> Value for a scale matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void scale(const float x,const float y,const float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a rotation transform
        *    \param grade,x,y,z -> Value for a rotation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void rotation(const float grade,const float x,const float y,const float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the identity matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void identity();


        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a matrix product
        *    \param aMatrix -> the other matrix to make the matrix product
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void product(const GLfloat * aMatrix);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between matrix and a vector
        *    \param aVector -> The vector for the product
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec4f product(const vec4f aVector);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    This method will asign a new values for our matrix
        *    \return Void
        */
        //////////////////////////////////////////////////////////////////////////
        void setMatrix(const GLfloat * aMatrix);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return Return our current matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        GLfloat * getMatrix();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return Return our current matrix4f in constant mode
        */
        //////////////////////////////////////////////////////////////////////////
        const GLfloat * getMatrixc()const;


    protected:

    private:
        GLfloat * matrix;
};

#endif // MATRIX4F_H
