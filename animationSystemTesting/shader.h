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

#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Shader
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Shader();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Shader(const string & aVertexfile,const string & aFragmentfile);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Shader();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set our files
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setFiles(const string & aVertexfile,const string & aFragmentfile);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will compile our fragmentShaders
        *    \return bool true -> fragmentShaders was compiled successfully
        *                 false-> fragmentShaders was not  compiled successfully
        */
        //////////////////////////////////////////////////////////////////////////
        bool compileFragmentShaders(const string & aFragmentfile="");

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will compile our vertexShaders
        *    \return bool true -> VertexShaders was compiled successfully
        *                 false-> VertexShaders was not  compiled successfully
        */
        //////////////////////////////////////////////////////////////////////////
        bool compileVertexShaders(const string & aVertexfile="");

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will link the shaders to a program
        *    \return bool true -> Shaders was linked successfully
        *                 false-> Shaders was not  linked successfully
        */
        //////////////////////////////////////////////////////////////////////////
        bool linkShaders();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will create a program
        *    \return bool true -> Program created successfully
        *                 false-> Program don't created successfully
        */
        //////////////////////////////////////////////////////////////////////////
        bool createProgram(const string & aVertexfile="",const string & aFragmentfile="");

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get our program
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getProgram();

    protected:

    private:
        string vertexfile,fragmentfile;
        GLuint programID,fragmentID,vertexID;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will load a text file. This type of file contains the GLSL code
        *    for our shader
        *    \return string -> That string contains the text in the file
        */
        //////////////////////////////////////////////////////////////////////////
        string LoadFileTxt(const string & file);
};

#endif // SHADER_H
