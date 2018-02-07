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

#include "texture.h"

Texture::Texture(){

}

//**********************************************************************//

Texture::Texture(const std::string& aFileName)
{
    fileName=aFileName;
    createTexture();
}

//**********************************************************************//

Texture::~Texture()
{
   glDeleteTextures(1, &texture);
}

//**********************************************************************//

void Texture::setFile(const std::string& aFileName){
    fileName=aFileName;
    createTexture();
}

//**********************************************************************//

void Texture::bindTexture(int ch){
    if(ch==0)
        glActiveTexture(GL_TEXTURE0);
    else if(ch==1)
        glActiveTexture(GL_TEXTURE1);
    else
        glActiveTexture(GL_TEXTURE2);

    glBindTexture(GL_TEXTURE_2D, texture);
}

//**********************************************************************//

void Texture::createTexture(){
    int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

    if(data == NULL)
		std::cout << "Unable to load texture: " << fileName << std::endl;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

}
