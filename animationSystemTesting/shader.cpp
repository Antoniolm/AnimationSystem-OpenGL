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

#include "shader.h"

Shader::Shader()
{
    //ctor
}

//**********************************************************************//

Shader::Shader(const string & aVertexfile,const string  & aFragmentfile){
    vertexfile=aVertexfile;
    fragmentfile=aFragmentfile;
    createProgram();
}

//**********************************************************************//

Shader::~Shader()
{
    //dtor
}

//**********************************************************************//

void Shader::setFiles(const string & aVertexfile,const string & aFragmentfile){
    vertexfile=aVertexfile;
    fragmentfile=aFragmentfile;
}

//**********************************************************************//

bool Shader::compileFragmentShaders(const string & aFragmentfile){
    //Check the parameters
    if(aFragmentfile!="")
        fragmentfile=aFragmentfile;

    //Initialize local variable
    bool result=true;
    GLint isShaderCompiled;
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    //Obtaining the code of our shaders
    string fShaderCode = LoadFileTxt(fragmentfile);

	//Compiling our FragmentShader
    char const * FragmentSourcePointer = fShaderCode.c_str();
	glShaderSource(fragmentID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(fragmentID);

	//Check Fragment Shader
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &isShaderCompiled);
    if(!isShaderCompiled)
    {
        cout<< "Unable to compile Fragment shader"<< fragmentfile<<endl;
        result = false;
    }

    return result;
}

//**********************************************************************//

bool Shader::compileVertexShaders(const string & aVertexfile){
    //Check the parameters
    if(aVertexfile!="")
        vertexfile=aVertexfile;

    //Initialize local variable
    bool result=true;
    GLint isShaderCompiled;
    vertexID = glCreateShader(GL_VERTEX_SHADER);

    //Obtaining the code of our shaders
    string vShaderCode = LoadFileTxt(vertexfile);

    //Compiling our vertexShader
    const char *VertexSourcePointer = vShaderCode.c_str();
    glShaderSource(vertexID,1,&VertexSourcePointer,NULL);
    glCompileShader(vertexID);

    //Check Vertex Shader
    glGetShaderiv( vertexID, GL_COMPILE_STATUS, &isShaderCompiled );
    if(!isShaderCompiled)
    {
        cout<< "Unable to compile vertex shader"<< vertexfile<<endl;
        result = false;
    }

    return result;
}

//**********************************************************************//

bool Shader::linkShaders(){
    GLint isProgramRight;
    bool result=true;

	//Creating our program and linking the shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    //Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &isProgramRight);
	if (!isProgramRight){
        cout<< "Unable to link the program"<<endl;
        result = false;
	}

	//Delete compiled shaders
	glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return result;
}

//**********************************************************************//

bool Shader::createProgram(const string & aVertexfile,const string & aFragmentfile){
    //Check the parameters
    if(aVertexfile!="" && aFragmentfile!=""){
        vertexfile=aVertexfile;
        fragmentfile=aFragmentfile;
    }

    bool result=true;
    result=compileVertexShaders(vertexfile);
    result=compileFragmentShaders(fragmentfile);
    result=linkShaders();

    return result;
}

//**********************************************************************//

GLuint Shader::getProgram(){
    return programID;
}

//**********************************************************************//
//* Private Methods

string Shader::LoadFileTxt(const string & file){

    string content;
    ifstream sourceFile;
    sourceFile.open(file.c_str(),ifstream::in);

    if( sourceFile.is_open() )
	{
        content.assign( ( istreambuf_iterator< char >( sourceFile ) ), istreambuf_iterator< char >() );
        sourceFile.close();
	}
    else{
        content="Unable to access the file"+ file;
    }

    return content;
}
