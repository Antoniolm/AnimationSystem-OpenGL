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

#ifndef SHADOWTEXTURE_H
#define SHADOWTEXTURE_H

#include "texture.h"

class ShadowTexture
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ShadowTexture();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ShadowTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will bind that texture in our current Shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
    	void bindTexture();

        void setShadowBuffer(bool value);
        GLuint getFrameBuffer();
        GLuint getTexture();
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a openGL texture
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createTexture();
        GLuint depthMapFBO, depthMap;
        GLuint shadowHeight,shadowWidth;
};

#endif // SHADOWTEXTURE_H
