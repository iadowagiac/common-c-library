/**
 * vector2.h - A Single-Header Library for 2D Vectors
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

typedef struct { float x, y; } vec2;
typedef struct { float xy; } bivec2;

#define smulvec2(s, v)  ((vec2) { s * v.x, s * v.y })

#define vec2len(v)  sqrt(vec2dot(v, v))

#define vec2add(v1, v2)  ((vec2) { v1.x + v2.x, v1.y + v2.y })
#define vec2sub(v1, v2)  ((vec2) { v1.x - v2.x, v1.y - v2.y })
#define vec2mul(v1, v2)  ((vec2) { v1.x * v2.x, v1.y * v2.y })
#define vec2div(v1, v2)  ((vec2) { v1.x / v2.x, v1.y / v2.y })

#define vec2dot(v1, v2)  (v1.x * v2.x + v1.y * v2.y)

#define vec2wedge(v1, v2)  ((bivec2) { v1.x * v2.y - v1.y * v2.x })

#endif /* ndef VECTOR2_H */
