#pragma once

#include <string>

#define NOMINMAX
#include <Windows.h>

#include "lowlevel/halo2/tag_structures.h"
#include "tag_field_types.h"

// a bunch of this is from Blam Creation Suite

namespace halo2
{
	namespace
	{
		static HMODULE h2alang_handle;
		static char* guerilla_file_data;

		constexpr static size_t max_h2alang_string_id = 5207; // max id for string in h2alang
		constexpr static size_t name_buffer_max_length = 4096;
		constexpr static size_t empty_string_id = 87;

		#if defined(_WIN64)
		#define ptr32 unsigned long
		#endif

		static constexpr ptr32 halo2_base_address = 0x400000;
		static constexpr ptr32 halo2_tag_layout_table_address = 0x00901B90;
		static constexpr unsigned long halo2_num_tag_layouts = 120;

		#define h2_va_to_pa(address) (address - halo2_base_address)
		#define h2_va_to_pointer(data, address) (address ? ((const char*)(data + h2_va_to_pa(address))) : 0)
	}

	struct s_h2_tag_group
	{
		union
		{
			unsigned long value;
			char name[4];
		};
	};
#define h2_tag_group_size sizeof(s_h2_tag_group)

	struct s_h2_field_type_definition
	{
		e_field_type type;
		unsigned short _padding;
		ptr32 name_address;
		ptr32 definition_address;
		unsigned long group_tag;
	};
#define h2_field_type_definition_size sizeof(s_h2_field_type_definition)

	struct s_h2_tag_reference_definition
	{
		unsigned long flags;
		unsigned long group_tag2;
		ptr32 group_tags_address;
	};
#define h2_tag_reference_size sizeof(s_h2_tag_reference_definition)

	struct s_h2_tag_struct_definition
	{
		ptr32 name_address;
		s_h2_tag_group group_tag;
		ptr32 display_name_address;
		ptr32 block_definition_address;
		size_t unknown1;
		s_h2_tag_group group_tag2;
		size_t unknown2;
	};
#define h2_tag_struct_size sizeof(s_h2_tag_struct_definition)

	struct s_h2_tag_data_definition
	{
		ptr32 definition_name_address;
		unsigned long flags;
		unsigned long alignment_bit;
		unsigned long maximum_size;
		ptr32 maximum_size_string_address;
		ptr32 byteswap_procedure;
		ptr32 copy_procedure;
	};
#define h2_tag_data_size sizeof(s_h2_tag_data_definition)

	struct s_h2_tag_enum_definition
	{
		unsigned long option_count;
		ptr32 options_address;
		unsigned long flags; //?
	};
#define h2_tag_enum_size sizeof(s_h2_tag_enum_definition)

	struct s_h2_tag_block_index_definition
	{
		ptr32 get_block_procedure;
		ptr32 is_valid_source_block_procedure;
	};
#define h2_tag_block_index_definition_size sizeof(s_h2_tag_block_index_definition)

	struct s_h2_byte_swap_definition
	{
		ptr32 name_address;
		unsigned long _unknown0;
		unsigned long _unknown1;
		unsigned long magic;
		unsigned long _unknown2;
		unsigned long _unknown3;
		unsigned long _unknown4;
		unsigned long _unknown5;
		unsigned long _unknown6;
	};
#define h2_byte_swap_definition_size sizeof(s_h2_byte_swap_definition)

	struct s_h2_field_type_set_version_header
	{
		ptr32 fields_address;
		unsigned long index;
		ptr32 upgrade_procedure;
		unsigned long _unknown;
		unsigned long size_of;
	};
#define h2_field_type_set_version_size sizeof(s_h2_field_type_set_version_header)

	struct s_h2_field_type_set_header
	{
		s_h2_field_type_set_version_header version;
		unsigned long size;
		unsigned long alignment_bit;
		unsigned long parent_version_index;
		ptr32 fields_address;
		ptr32 size_string_address;
		s_h2_byte_swap_definition byte_swap_definition;
	};
#define h2_field_type_set_header_size sizeof(s_h2_field_type_set_header)

	struct s_h2_tag_block_definition
	{
		ptr32 display_name_address;
		ptr32 name_address;
		unsigned long flags;
		unsigned long maximum_element_count;
		ptr32 maximum_element_count_string_address;
		ptr32 field_sets_address;
		unsigned long field_set_count;
		ptr32 field_set_latest_address;
		unsigned long _unknown;
		ptr32 postprocess_procedure;
		ptr32 format_procedure;
		ptr32 generate_default_procedure;
		ptr32 dispose_element_procedure;
	};
#define h2_tag_block_definition_size sizeof(s_h2_tag_block_definition)

	struct s_h2_tag_layout_definition
	{
		ptr32 name_address;
		unsigned long flags;
		s_h2_tag_group group_tag;
		s_h2_tag_group parent_group_tag;
		unsigned short version;
		unsigned char initialized;
		unsigned char : 8;
		ptr32 postprocess_procedure;
		ptr32 save_postprocess_procedure;
		ptr32 postprocess_for_sync_procedure;
		unsigned long inheritance_flags;
		ptr32 definition_address;
		s_h2_tag_group child_group_tags[16];
		unsigned short num_child_group_tags;
		unsigned short : 16;
		ptr32 default_tag_path_address;
	};
#define h2_tag_layout_definition_size sizeof(s_h2_tag_layout_definition)

	void dump(const std::string* guerilla_path, const std::string* h2alang_path, const std::string* output_path);
};

