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

#ifndef STRUCTDATA_H
#define STRUCTDATA_H

#include <math.h>
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a vector with 4 float value
*/
//////////////////////////////////////////////////////////////////////////
struct vec4f{
    float x;
    float y;
    float z;
    float w;
    vec4f(){x=0.0f;y=0.0;z=0.0;w=1;}
    vec4f(float dx,float dy,float dz,float dw){
        x=dx;
        y=dy;
        z=dz;
        w=dw;
    }
    void setValue(int in,float value){
        switch(in){
            case 0:
                x=value;
            break;
            case 1:
                y=value;
            break;
            case 2:
                z=value;
            break;
            case 3:
                w=value;
            break;
        }
    }
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a vector with 3 float value
*/
//////////////////////////////////////////////////////////////////////////
struct vec3f{
    float x;
    float y;
    float z;
    vec3f(){
        x=0.0f;
        y=0.0f;
        z=0.0f;
    }
    vec3f(float dx,float dy,float dz){
        x=dx;
        y=dy;
        z=dz;
    }
    vec3f(vec4f aVec){
        x=aVec.x;
        y=aVec.y;
        z=aVec.z;
    }
    vec3f operator=(vec3f aVec){
        x=aVec.x;
        y=aVec.y;
        z=aVec.z;

        return *this;
    }
    vec3f operator+(vec3f aVec){
        vec3f result;

        result.x=x+aVec.x;
        result.y=y+aVec.y;
        result.z=z+aVec.z;

        return result;
    }

    vec3f operator*(vec3f aVec){
        vec3f result;

        result.x=x*aVec.x;
        result.y=y*aVec.y;
        result.z=z*aVec.z;

        return result;
    }

    vec3f operator*(float value){
        vec3f result;

        result.x=x*value;
        result.y=y*value;
        result.z=z*value;

        return result;
    }

    vec3f operator/(vec3f aVec){
        vec3f result;

        result.x=x/aVec.x;
        result.y=y/aVec.y;
        result.z=z/aVec.z;

        return result;
    }

    vec3f operator/(float value){
        vec3f result;

        result.x=x/value;
        result.y=y/value;
        result.z=z/value;

        return result;
    }

    bool operator<(vec3f aVec){
        bool result=false;
        if(x<aVec.x && y<aVec.y && z<aVec.z)
            result=true;

        return result;
    }

    bool operator>(vec3f aVec){
        bool result=false;
        if(x>aVec.x && y>aVec.y && z>aVec.z)
            result=true;

        return result;
    }

    bool operator==(vec3f aVec){
        bool result=false;
        if(x==aVec.x && y==aVec.y && z==aVec.z)
            result=true;

        return result;
    }

    bool operator!=(vec3f aVec){
        bool result=false;
        if(x!=aVec.x && y!=aVec.y && z!=aVec.z)
            result=true;

        return result;
    }

    float dot(vec3f aVec){
        float result=0.0f;

        result+=(x*aVec.x)+(y*aVec.y)+(z*aVec.z);

        return result;
    }

    vec3f operator-(vec3f aVec){
        vec3f result;
        result.x=x-aVec.x;
        result.y=y-aVec.y;
        result.z=z-aVec.z;

        return result;
    }
    vec3f cross(vec3f aVec){
       vec3f result;
       result.x=(y*aVec.z)-(z*aVec.y);
       result.y=-((x*aVec.z)-(z*aVec.x));
       result.z=(x*aVec.y)-(y*aVec.x);
       return result;
    }
    void normalize(){
        float result=0;
        result=sqrt((x*x)+(y*y)+(z*z));
        x/=result;
        y/=result;
        z/=result;
    }
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a vector with 3 integer value
*/
//////////////////////////////////////////////////////////////////////////
struct vec3i{
    int x;
    int y;
    int z;
    vec3i(){x=0;y=0;z=0;}
    vec3i(int dx,int dy,int dz){
        x=dx;
        y=dy;
        z=dz;
    }
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a vector with 2 float value
*/
//////////////////////////////////////////////////////////////////////////
struct vec2f{
    float x;
    float y;
    vec2f(){x=0.0;y=0.0;}
    vec2f(float dx,float dy){
        x=dx;
        y=dy;
    }
    vec2f operator=(vec2f aVec){
        x=aVec.x;
        y=aVec.y;

        return *this;
    }
    vec2f operator-(vec2f aVec){
        vec2f result;
        result.x=x-aVec.x;
        result.y=y-aVec.y;

        return result;
    }
    vec2f operator*(float value){
        vec2f result;

        result.x=x*value;
        result.y=y*value;

        return result;
    }
    vec2f operator*(vec2f aVec){
        vec2f result;

        result.x=x*aVec.x;
        result.y=y*aVec.y;

        return result;
    }
};

#endif
