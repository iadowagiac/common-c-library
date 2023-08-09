/**
 * vector3.h - A Single-Header Library for 3D Vectors
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct { float x, y, z; } vec3;
typedef struct { float xy, yz, zx; } bivec3;

#define smulvec3(s, v)  ((vec3) { s * v.x, s * v.y, s * v.z })

#define vec3len(v)  sqrt(vec3dot(v, v))

#define vec3add(v1, v2)  ((vec3) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z })
#define vec3sub(v1, v2)  ((vec3) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z })
#define vec3mul(v1, v2)  ((vec3) { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z })
#define vec3div(v1, v2)  ((vec3) { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z })

#define vec3dot(v1, v2)  (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)

#define vec2cross(v1, v2)  ((vec3) \
{ \
    v1.y * v2.z - v1.z * v2.y, \
    v1.z * v2.x - v1.x * v2.z, \
    v1.x * v2.y - v1.y * v2.x, \
})

#define vec2wedge(v1, v2)  ((bivec3) \
{ \
    v1.x * v2.y - v1.y * v2.x, \
    v1.y * v2.z - v1.z * v2.y, \
    v1.z * v2.x - v1.x * v2.z, \
})

#endif /* ndef VECTOR3_H */
