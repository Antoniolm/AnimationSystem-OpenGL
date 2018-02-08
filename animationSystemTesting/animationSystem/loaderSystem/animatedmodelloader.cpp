// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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

#include "animatedmodelloader.h"

AnimatedModelLoader::AnimatedModelLoader(string modelFile){
    //Open file
    FILE * fp = fopen(modelFile.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);
    fclose(fp);
    cout<< "Created"<<endl;

    cout<< "< Loading skin >"<< endl;
    const rapidjson::Value & skinFeature=document["COLLADA"]["library_controllers"]["controller"]["skin"];
    SkinLoader * skinLoader=new SkinLoader(skinFeature);
    delete skinLoader;
}

//**********************************************************************//

AnimatedModelLoader::~AnimatedModelLoader()
{
    //dtor
}
