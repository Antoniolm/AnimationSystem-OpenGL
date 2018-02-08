// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#include "skinloader.h"

SkinLoader::SkinLoader(const rapidjson::Value & skinFeature){
  cout<< skinFeature["source"][0]["Name_array"]["#text"].GetString()<<endl;

  istringstream tokensbuf(skinFeature["source"][0]["Name_array"]["#text"].GetString());
  istream_iterator<string> tokensbeg(tokensbuf), tokensend;

  vector<string> tokens(tokensbeg, tokensend);

  for(unsigned i=0;i<tokens.size();i++)
    cout<< "Elem("<<i<<")="<< tokens[i]<<endl;

  istringstream buf(skinFeature["source"][2]["float_array"]["#text"].GetString());
  istream_iterator<float> beg(buf), end;

  vector<float> weights(beg, end);

  for(unsigned i=0;i<weights.size();i++)
    cout<< "Elem("<<i<<")="<< (float)weights[i]<<endl;
}

//**********************************************************************//

SkinLoader::~SkinLoader()
{
    //dtor
}
