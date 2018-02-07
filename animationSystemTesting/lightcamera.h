#ifndef LIGHTCAMERA_H
#define LIGHTCAMERA_H

#include "structdata.h"
#include "matrix4f.h"

class LightCamera
{
    public:
        /** Default constructor */
        LightCamera();
        /** Default destructor */
        virtual ~LightCamera();
        Matrix4f createCamera(vec3f eye,vec3f aTarget,vec3f aUp);
        Matrix4f createOrtho(float left,float right,float bottom,float top,float nearPro = -1.0f,float farPro = 1.0f );
    protected:

    private:
};

#endif // LIGHTCAMERA_H
