#ifndef PHYSICSUTILITIES_H
#define PHYSICSUTILITIES_H

// C/C++ Includes
#include <iostream>
#include <cmath>

// Irrlicht Includes
#include <irrlicht.h>

//// Newton Includes
//#include <cstddef>
//#include <newton.h>
//
//// NewtonWrapper Includes
//#include "Utilities/NewtonAABB.h"
//#include "Utilities/NewtonFreezeThreshold.h"
//#include "Utilities/NewtonGlobalScale.h"
//#include "Utilities/NewtonMassMatrix.h"
//#include "Utilities/NewtonMatrix4.h"
//#include "Utilities/NewtonVector3.h"

namespace Utils
{
//    //! Convert a NewtonVector2 into an irr::core::vector2df
//    inline irr::core::vector2df convertNewtonVector2ToVector2df(NewtonVector2& in)
//    {
//        irr::core::vector2df out(in.getX(), in.getY());
//        out *= NewtonToRenderScale;
//        return out;
//    }
//    //! Convert a irr::core::vector2df to an NewtonVector2
//    inline NewtonVector2 convertVector2dfToNewtonVector2(irr::core::vector2df& in)
//    {
//        NewtonVector2 out(in.X, in.Y);
//        out *= RenderScaleToNewton;
//        return out;
//    }
//    //! Convert a NewtonVector3 into an irr::core::vector3df
//    inline irr::core::vector3df convertNewtonVector3ToVector3df(NewtonVector3& in)
//    {
//        irr::core::vector3df out(in.getX(), in.getY(), in.getZ());
//        out *= NewtonToRenderScale;
//        return out;
//    }
//    //! Convert a irr::core::vector3df to an NewtonVector3
//    inline NewtonVector3 convertVector3dfToNewtonVector3(irr::core::vector3df& in)
//    {
//        NewtonVector3 out(in.X, in.Y, in.Z);
//        out *= RenderScaleToNewton;
//        return out;
//    }
//    //! Convert a Irrlicht matrix4 to a Newton matrix
//    inline NewtonMatrix4 convertMatrix4ToNewtonMatrix(irr::core::matrix4& in)
//    {
//        NewtonMatrix4 out;
//        // Copy the irrlicht matrix to the out matrix
//        for (unsigned int i = 0; i < 16; i++)
//            out[i] = in[i];
//        // Scale the Translation component of the matrix
//        out[12] = in[12] * RenderScaleToNewton;
//        out[13] = in[13] * RenderScaleToNewton;
//        out[14] = in[14] * RenderScaleToNewton;
//        return out;
//    }
//    //! Convert a Newton matrix to a matrix4
//    inline irr::core::matrix4 convertNewtonMatrixToMatrix4(NewtonMatrix4& in)
//    {
//        irr::core::matrix4 out;
//        // Copy the newton matrix to the out matrix
//        for (unsigned int i = 0; i < 16; i++)
//            out[i] = in[i];
//        // Scale the Translation component of the matrix
//        out[12] = in[12] * NewtonToRenderScale;
//        out[13] = in[13] * NewtonToRenderScale;
//        out[14] = in[14] * NewtonToRenderScale;
//        return out;
//    }
//    //! Convert a Irrlicht axis aligned bounding box to a Newton axis aligned bounding box
//    inline NewtonAABB convertAABB3DFToNewtonAABB(irr::core::aabbox3df& in)
//    {
//        NewtonAABB out;
//        out.setMinEdge(in.MinEdge.X * RenderScaleToNewton, in.MinEdge.Y * RenderScaleToNewton, in.MinEdge.Z * RenderScaleToNewton);
//        out.setMaxEdge(in.MaxEdge.X * RenderScaleToNewton, in.MaxEdge.Y * RenderScaleToNewton, in.MaxEdge.Z * RenderScaleToNewton);
//        return out;
//    }
//    //! Convert a Newton axis aligned bounding box to an Irrlicht axis aligned bounding box
//    inline irr::core::aabbox3df convertNewtonAABBToAABB3DF(NewtonAABB in)
//    {
//        irr::core::aabbox3df out;
//        out.MinEdge = irr::core::vector3df(in.getMinEdgeX() * NewtonToRenderScale, in.getMinEdgeY() * NewtonToRenderScale, in.getMinEdgeZ() * NewtonToRenderScale);
//        out.MaxEdge = irr::core::vector3df(in.getMaxEdgeX() * NewtonToRenderScale, in.getMaxEdgeY() * NewtonToRenderScale, in.getMaxEdgeZ() * NewtonToRenderScale);
//        return out;
//    }
}

#endif // PHYSICSUTILITIES_H
