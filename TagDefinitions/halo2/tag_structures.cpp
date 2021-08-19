#include "pch.h"
#include "tag_structures.h"

using namespace tag_definition_common;

namespace halo2
{
	const char* get_field_code_type(e_field_type field_type)
	{
		switch (field_type)
		{
		case f_string:								return "string32";
		case f_long_string:							return "string256";
		case f_string_id:							return "string_id";
		case f_old_string_id:						return "string_id";
		case f_char_integer:						return "char";
		case f_short_integer:						return "short";
		case f_long_integer:						return "long";
		case f_angle:								return "angle";
		case f_tag:									return "whaaaat do ah dooooo with this taaaaag";
		case f_char_enum:							return "enum8";
		case f_enum:								return "enum16";
		case f_long_enum:							return "enum32";
		case f_long_flags:							return "long";
		case f_word_flags:							return "word";
		case f_byte_flags:							return "byte";
		case f_point_2d:							return "point2d";
		case f_rectangle_2d:						return "rectangle2d";
		case f_rgb_color:							return "pixel32";
		case f_argb_color:							return "pixel32";
		case f_real:								return "real";
		case f_real_fraction:						return "real_fraction";
		case f_real_point_2d:						return "real_point2d";
		case f_real_point_3d:						return "real_point3d";
		case f_real_vector_2d:						return "real_vector2d";
		case f_real_vector_3d:						return "real_vector3d";
		case f_real_quaternion:						return "real_quaternion";
		case f_real_euler_angles_2d:				return "real_euler_angles2d";
		case f_real_euler_angles_3d:				return "real_euler_angles3d";
		case f_real_plane_2d:						return "real_plane2d";
		case f_real_plane_3d:						return "real_plane3d";
		case f_real_rgb_color:						return "rgb_color";
		case f_real_argb_color:						return "argb_color";
		case f_real_hsv_color:						return "real_hsv_color";
		case f_real_ahsv_color:						return "real_ahsv_color";
		case f_short_bounds:						return "short_bounds";
		case f_angle_bounds:						return "angle_bounds";
		case f_real_bounds:							return "real_bounds";
		case f_real_fraction_bounds:				return "real_bounds";
		case f_tag_reference:						return "s_tag_ref";
		case f_block:								return "s_tag_block";
		case f_long_block_flags:					return "long";
		case f_word_block_flags:					return "word";
		case f_byte_block_flags:					return "byte";
		case f_char_block_index:					return "char";
		case f_custom_char_block_index:				return "char";
		case f_short_block_index:					return "short";
		case f_custom_short_block_index:			return "short";
		case f_long_block_index:					return "long";
		case f_custom_long_block_index:				return "long";
		case f_data:								return "h_data";
		case f_vertex_buffer:						return "s_tag_d3d_vertex_buffer";
		case f_pad:									return "pad plonker";	// dynamic
		case f_useless_pad:							return "useless pad u chucklefucker";	// dynamic
		case f_skip:								return "skip shitto";	// dynamic
		case f_explanation:							return "explanation shithead";	// empty
		case f_custom:								return "custom fucko";	// empty
		case f_struct:								return "struct :)";	// dynamic
		case f_terminator:							return "terminat";	// empty
		case f_array_start:							return "array start glurpo";
		case f_array_end:							return "array end glurpo";
		default: __debugbreak();
		}
	}

	size_t get_field_size(e_field_type field_type)
	{
		switch (field_type)
		{
		case f_string:								return sizeof(string32);
		case f_long_string:							return sizeof(string256);
		case f_string_id:							return sizeof(string_id);
		case f_old_string_id:						return sizeof(string_id);
		case f_char_integer:						return 1;
		case f_short_integer:						return 2;
		case f_long_integer:						return 4;
		case f_angle:								return 4;
		case f_tag:									return 4; // allegedly
		case f_char_enum:							return sizeof(enum8);
		case f_enum:								return sizeof(enum16);
		case f_long_enum:							return sizeof(enum32);
		case f_long_flags:							return sizeof(flags32);
		case f_word_flags:							return sizeof(flags16);
		case f_byte_flags:							return sizeof(flags8);
		case f_point_2d:							return sizeof(point2d);
		case f_rectangle_2d:						return sizeof(rectangle2d);
		case f_rgb_color:							return sizeof(pixel32);
		case f_argb_color:							return sizeof(pixel32);
		case f_real:								return 4;
		case f_real_fraction:						return sizeof(real_fraction);
		case f_real_point_2d:						return sizeof(real_point2d);
		case f_real_point_3d:						return sizeof(real_point3d);
		case f_real_vector_2d:						return sizeof(real_vector2d);
		case f_real_vector_3d:						return sizeof(real_vector3d);
		case f_real_quaternion:						return sizeof(real_quaternion);
		case f_real_euler_angles_2d:				return sizeof(real_euler_angles2d);
		case f_real_euler_angles_3d:				return sizeof(real_euler_angles3d);
		case f_real_plane_2d:						return sizeof(real_plane2d);
		case f_real_plane_3d:						return sizeof(real_plane3d);
		case f_real_rgb_color:						return sizeof(rgb_color);
		case f_real_argb_color:						return sizeof(argb_color);
		case f_real_hsv_color:						return sizeof(real_hsv_color);
		case f_real_ahsv_color:						return sizeof(real_ahsv_color);
		case f_short_bounds:						return sizeof(short_bounds);
		case f_angle_bounds:						return sizeof(angle_bounds);
		case f_real_bounds:							return sizeof(real_bounds);
		case f_real_fraction_bounds:				return sizeof(real_bounds);
		case f_tag_reference:						return sizeof(s_tag_ref);
		case f_block:								return sizeof(s_tag_block);
		case f_long_block_flags:					return sizeof(long);
		case f_word_block_flags:					return sizeof(short);
		case f_byte_block_flags:					return sizeof(byte);
		case f_char_block_index:					return sizeof(char);
		case f_custom_char_block_index:				return sizeof(char);
		case f_short_block_index:					return sizeof(short);
		case f_custom_short_block_index:			return sizeof(short);
		case f_long_block_index:					return sizeof(long);
		case f_custom_long_block_index:				return sizeof(long);
		case f_data:								return sizeof(long);
		case f_vertex_buffer:						return sizeof(s_tag_d3d_vertex_buffer);
		case f_pad:									return -1; // dynamic
		case f_useless_pad:							return -1; // dynamic
		case f_skip:								return -1; // dynamic
		case f_explanation:							return -1; // empty
		case f_custom:								return -1; // empty
		case f_struct:								return -1; // dynamic
		case f_terminator:							return -1; // empty
		case f_array_start:							return -1;
		case f_array_end:							return -1;
		default: __debugbreak();
		}
	}
}
