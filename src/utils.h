/*
Copyright 2020-2020 Lucas Heitzmann Gabrielli.
This file is part of gdstk, distributed under the terms of the
Boost Software License - Version 1.0.  See the accompanying
LICENSE file or <http://www.boost.org/LICENSE_1_0.txt>
*/

#define _USE_MATH_DEFINES

#ifndef __UTILS_H__
#define __UTILS_H__

#define _USE_MATH_DEFINES

#define MAP_CAP 7

#define MIN_POINTS 4

#define PARALLEL_EPS 1e-8

#define COUNT(a) (sizeof(a) / sizeof(0 [a]))

#define LERP(a, b, u) ((a) * (1 - (u)) + (b) * (u))
#define SERP(a, b, u) ((a) + ((b) - (a)) * (3 - 2 * (u)) * (u) * (u))

#define DEBUG_PRINT                               \
    printf("%s:%d: DEBUG\n", __FILE__, __LINE__); \
    fflush(stdout);

// From http://esr.ibiblio.org/?p=5095
#define IS_BIG_ENDIAN (*(uint16_t*)"\0\xFF" < 0x100)

#include <cmath>
#include <cstdint>

#include "array.h"
#include "vec.h"

namespace gdstk {

// Argument between 0 and 1
typedef double (*ParametricDouble)(double, void*);

// Argument between 0 and 1
typedef Vec2 (*ParametricVec2)(double, void*);

// Arguments: first_point, first_direction, second_point, second_direction, data
typedef Array<Vec2> (*EndFunction)(const Vec2, const Vec2, const Vec2, const Vec2, void*);

// Arguments: first_point, first_direction, second_point, second_direction, center, width, data
typedef Array<Vec2> (*JoinFunction)(const Vec2, const Vec2, const Vec2, const Vec2, const Vec2,
                                    double, void*);

// Arguments: radius, initial_angle, final_angle, center, data
typedef Array<Vec2> (*BendFunction)(double, double, double, const Vec2, void*);

uint64_t gdsii_real_from_double(double value);

double gdsii_real_to_double(uint64_t real);

double modulo(double x, double y);

int64_t arc_num_points(double angle, double radius, double tol);

double elliptical_angle_transform(double angle, double radius_x, double radius_y);

double distance_to_line_sq(const Vec2 p, const Vec2 p1, const Vec2 p2);

double distance_to_line(const Vec2 p, const Vec2 p1, const Vec2 p2);

// ut are unitary tangent vectors (in the segment direction)
void segments_intersection(const Vec2 p0, const Vec2 ut0, const Vec2 p1, const Vec2 ut1, double& u0,
                           double& u1);

void swap16(uint16_t* buffer, int64_t n);

void swap32(uint32_t* buffer, int64_t n);

void swap64(uint64_t* buffer, int64_t n);

// Read record and make necessary swaps
int32_t read_record(FILE* in, uint8_t* buffer);

Vec2 eval_line(double t, const Vec2 p0, const Vec2 p1);

Vec2 eval_bezier2(double t, const Vec2 p0, const Vec2 p1, const Vec2 p2);

Vec2 eval_bezier3(double t, const Vec2 p0, const Vec2 p1, const Vec2 p2, const Vec2 p3);

Vec2 eval_bezier(double t, const Vec2* ctrl, int64_t size);

// Defaults for tension and curl arguments should be 1
void hobby_interpolation(int64_t size, Vec2* points, double* angles, bool* angle_constraints,
                         Vec2* tension, double initial_curl, double final_curl, bool cycle);

}  // namespace gdstk

#endif
