/**
 * vector4.h - A Single-Header Library for 4D Vectors
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct { float x, y, z, w; } vec4;

#define smulvec4(s, v)  ((vec4) { s * v.x, s * v.y, s * v.z, s * v.w })

#define vec4len(v)  sqrt(vec4dot(v, v))

#define vec4add(v1, v2) \
    ((vec4) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w })

#define vec4sub(v1, v2) \
    ((vec4) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w })

#define vec4mul(v1, v2) \
    ((vec4) { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w })

#define vec4div(v1, v2) \
    ((vec4) { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w })

#define vec4dot(v1, v2) \
    (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w)

#endif /* ndef VECTOR4_H */
