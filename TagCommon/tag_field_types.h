#pragma once

/*
 * general field stuff that applies across engine versions
 */
namespace tag_definition_common
{
    typedef float angle;
    typedef float real;
    typedef unsigned char byte;
    typedef short word;
    typedef unsigned long dword;
    typedef long string_id;
    typedef real real_fraction;

    struct real_bounds
    {
        real lower;
        real upper;
    };

    struct angle_bounds
    {
        angle lower;
        angle upper;
    };

    struct real_fraction_bounds
    {
        real_fraction lower;
        real_fraction upper;
    };

    struct short_bounds
    {
        short lower;
        short upper;
    };

    struct point2d
    {
        short x;
        short y;
    };

    struct point3d
    {
        short x;
        short y;
        short z;
    };

    struct rectangle2d
    {
        short top;
        short left;
        short bottom;
        short right;
    };

	struct real_point2d
	{
        real x;
        real y;
	};

    struct real_point3d
    {
        real x;
        real y;
        real z;
    };

    struct real_vector2d
    {
        real i;
        real j;
    };

    struct real_vector3d
    {
        real i;
        real j;
        real k;
    };

    struct real_vector4d
    {
        real i;
        real j;
        real k;
        real w;
    };

    struct real_quaternion
    {
        real i;
        real j;
        real k;
        real w;
    };

    struct real_euler_angles2d
    {
        real yaw;
        real pitch;
    };

    struct real_euler_angles3d
    {
        real yaw;
        real pitch;
        real roll;
    };

    struct real_plane2d
    {
        real_vector2d normal;
        real distance;
    };

    struct real_plane3d
    {
        real_vector3d normal;
        real distance;
    };

    struct real_matrix3x3
    {
        real_vector3d forward;
        real_vector3d left;
        real_vector3d up;
    };

    struct real_matrix4x3
    {
        real_vector3d forward;
        real_vector3d left;
        real_vector3d up;
        real_point3d position;
        real scale;
    };

    struct real_orientation
    {
        real_quaternion rotation;
        real_point3d translation;
        real scale;
    };

    struct real_rectangle2d
    {
        real_bounds x;
        real_bounds y;
    };

    struct real_rectangle3d
    {
        real_bounds x;
        real_bounds y;
        real_bounds z;
    };

    struct rgb_color
    {
        real red;
        real green;
        real blue;
    };

    struct argb_color
    {
        real alpha;
        real red;
        real green;
        real blue;
    };

    struct real_hsv_color
    {
        real hue;
        real saturation;
        real value;
    };

    struct real_ahsv_color
    {
        real alpha;
        real hue;
        real saturation;
        real value;
    };

    union pixel32
    {
        struct
        {
            byte : 8;
            byte red;
            byte green;
            byte blue;
        };
        dword value;
    };

    struct enum8
    {
        char c;
    };

    struct enum16
    {
        short s;
    };

    struct enum32
    {
        long l;
    };

    struct flags8
    {
        char c;
    };

    struct flags16
    {
        short s;
    };

    struct flags32
    {
        long l;
    };

    struct s_tag_d3d_vertex_buffer
    {
        char data[32];
    };
}
