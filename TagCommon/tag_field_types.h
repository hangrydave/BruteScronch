#pragma once

typedef float angle;
typedef float real;
typedef unsigned char byte;
typedef short word;
typedef unsigned long dword;
typedef long string_id;

namespace tag_definition_common
{
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
}
