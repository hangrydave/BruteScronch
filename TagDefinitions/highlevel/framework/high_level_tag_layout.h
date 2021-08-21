#pragma once

#include <vector>
#include <string>
#include "high_level_tag_field.h"

namespace high_level
{
	// field types across halo 1 and halo 2
	enum e_field_type : short
	{
		f_string,
		f_long_string,
		f_string_id,
		f_old_string_id,
		f_char_integer,
		f_short_integer,
		f_long_integer,
		f_angle,
		f_tag,
		f_char_enum,
		f_enum,
		f_long_enum,
		f_long_flags,
		f_word_flags,
		f_byte_flags,
		f_point_2d,
		f_rectangle_2d,
		f_rgb_color,
		f_argb_color,
		f_real,
		f_real_fraction,
		f_real_point_2d,
		f_real_point_3d,
		f_real_vector_2d,
		f_real_vector_3d,
		f_real_quaternion,
		f_real_euler_angles_2d,
		f_real_euler_angles_3d,
		f_real_plane_2d,
		f_real_plane_3d,
		f_real_rgb_color,
		f_real_argb_color,
		f_real_hsv_color,
		f_real_ahsv_color,
		f_short_bounds,
		f_angle_bounds,
		f_real_bounds,
		f_real_fraction_bounds,
		f_tag_reference,
		f_block,
		f_long_block_flags,
		f_word_block_flags,
		f_byte_block_flags,
		f_char_block_index,
		f_custom_char_block_index,
		f_short_block_index,
		f_custom_short_block_index,
		f_long_block_index,
		f_custom_long_block_index,
		f_data,
		f_vertex_buffer,
		f_array_start,
		f_array_end,
		f_pad,
		f_useless_pad,
		f_skip,
		f_explanation,
		f_custom,
		f_struct,
		f_terminator,
		f_type_max,
	};

	enum e_game_version : char
	{
		halo1,
		halo2,
		both
	};

	struct s_tag_definition;

	struct s_tag_field
	{
		e_field_type type;
		const char* name;
	};

	struct s_tag_struct
	{
		std::string name;
		std::vector<s_tag_field*> fields;
	};

	class high_level_tag_layout
	{
	private:
		std::string* halo1_low_level_definition;
		std::string* halo2_low_level_definition;
	protected:
		const s_tag_field* define_field(const e_field_type& type, const char* name, const s_tag_struct* field_struct = nullptr);
		const s_tag_struct* define_struct(const char* name, std::vector<const s_tag_field*> fields);
		virtual const s_tag_struct* define() = 0;
	public:
		high_level_tag_layout();
	};
}
