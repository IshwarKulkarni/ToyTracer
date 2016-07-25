/***************************************************************************
* tessellation.h                                                           *
*                                                                          *
* The "Tessellate" class serves as a base class for Containers that        *
* generate tessellations of parametric surfaces into triangles or quads,   *
* with or without normals.  Examples: bezier, superquadric, supertoroid.   *
*                                                                          *
* History:                                                                 *
*   05/11/2010  Initial coding.                                            *
*                                                                          *
***************************************************************************/
#ifndef __TESSELLATION_INCLUDED__
#define __TESSELLATION_INCLUDED__

#include "toytracer.h"
#include "interval.h"
#include "vec3.h"
#include "triangle.h"


// If a surface possesses some basic symmetries (i.e. they are symmetric
// about the x=0, y=0, or z=0 planes), then the Tessellation class can
// automatically generate the entire shape from one octant, quadrant, or
// half-space of the surface.  This flag controlls how many reflections
// of each triangle are to be added to the container.
enum symmetry_type {
    no_symmetry,
    x_symmetry,
    xy_symmetry,
    xyz_symmetry
    };

// This enumerated type is used to control which types of elements are
// generated by the tessellation.  NOT YET IMPLEMENTED
enum tess_elem_type {
    triangles_only,
    quads_only,
    tris_and_quads
    };

// A Tessellation is a sub-class of Container that holds the triangles generated by
// tessellating a parametric surface.  Since this is a common operation, it has been
// abstracted into this common base class for the benefit of classes such as bezier,
// superquadric, and supertoroid.
class Tessellation : public Container {
    public:
        Tessellation();
        virtual ~Tessellation() {}
        virtual void Tessellate( Interval U, unsigned nu, Interval V, unsigned nv );
        virtual void Eval( double u, double v, Vec3 &P, Vec3 &N ) const = 0;
        virtual void SetNormals ( Vec3 &v1, Vec3 &v2, Vec3 &v3 );
        virtual void AddTriangle( Vec3 &v1, Vec3 &v2, Vec3 &v3 );
        void EnableNormals( bool on_off ) { with_normals = on_off; }
        void EnableSymmetry( symmetry_type st ) { symtype = st; }
        void EnableElement( tess_elem_type tem ) { elemtype = tem; }
    private:
        bool with_normals;
        bool normals_set;
        symmetry_type symtype;
        tess_elem_type elemtype;
        Vec3 N1, N2, N3, N4;
    };

#endif