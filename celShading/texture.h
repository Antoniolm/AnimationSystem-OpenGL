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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glew.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Texture();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        Texture(const std::string& aFileName);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Texture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the file of our texture
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setFile(const std::string& aFileName);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will bind that texture in our current Shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
    	void bindTexture(int ch=0);

    protected:
        std::string fileName;
        GLuint texture;
    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a openGL texture
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createTexture();

};

#endif // TEXTURE_H
