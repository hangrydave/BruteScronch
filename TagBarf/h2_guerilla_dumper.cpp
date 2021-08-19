#include <assert.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "h2_guerilla_dumper.h"
#include "tag_field_types.h"
//#include "halo2/definitions/bipd.h"
#include "util.h"
//#include "halo2/tag_structures.h"

#define NOMINMAX
#include <Windows.h>

using namespace tag_definition_common;

/*

IF YOU VALUE YOUR HIGHER BRAIN FUNCTION

YOU WILL NOT PROCEED PAST THIS POINT

I HAVE MADE AN INDISCRIMINATE AMOUNT OF PROGRESS IN THE PAST 10 HOURS

I HAVE CEASED TO CARE ABOUT SILLY THINGS LIKE "STANDARDS" AND "READABILITY"

:)

*/

namespace halo2
{
	void dump(const std::string* guerilla_path, const std::string* h2alang_path, const std::string* output_path)
	{
        // tag def list output
        std::string tag_definition_list_path(*output_path);
        tag_definition_list_path += "\\tag_definition_list.h";
        std::ofstream tag_definition_list_out(tag_definition_list_path);

        tag_definition_list_out <<
            "#pragma once\n\n";

        // map file
        std::fstream guerilla_file_in(guerilla_path->c_str(), std::ios::in | std::ios::binary);

        // https://stackoverflow.com/a/22986486/5132781
        guerilla_file_in.ignore(std::numeric_limits<std::streamsize>::max());
        std::streamsize guerilla_data_length = guerilla_file_in.gcount();
        guerilla_file_in.clear();
        guerilla_file_in.seekg(0, std::ios_base::beg);
        char* guerilla_file_data = new char[guerilla_data_length];
        guerilla_file_in.read(guerilla_file_data, guerilla_data_length);
        guerilla_file_in.close();

        // h2alang.dll
        size_t converted_num;
        wchar_t* wide_path = new wchar_t[h2alang_path->size()];
        mbstowcs_s(&converted_num, wide_path, h2alang_path->size() + 1, h2alang_path->c_str(), h2alang_path->size());
        HMODULE h2alang_handle = LoadLibraryW(wide_path);

        std::unordered_map<unsigned long, std::string*> tag_group_name_map;

        s_h2_tag_group_definition tag_layout_headers[halo2_num_tag_layouts];

        ptr32(&layout_addresses)[halo2_num_tag_layouts] = *reinterpret_cast<decltype(&layout_addresses)>(guerilla_file_data + h2_va_to_pa(halo2_tag_layout_table_address));
        for (unsigned long tag_layout_index = 0; tag_layout_index < halo2_num_tag_layouts; tag_layout_index++)
        {
            // tag layout
            ptr32 tag_layout_virtual_address = layout_addresses[tag_layout_index];
            const char* tag_layout_data = h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address);

            const s_h2_tag_group_definition tag_layout_header =
                *reinterpret_cast<const s_h2_tag_group_definition*>(h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address));

            // get and sanitize layout name
            std::string* tag_layout_name
                = new std::string(h2_va_to_pointer(guerilla_file_data, tag_layout_header.name_address));
            util::sanitize_variable_name(*tag_layout_name);

            tag_layout_name->append("_definition");
            tag_group_name_map[tag_layout_header.group_tag.value] = tag_layout_name;

            // child groups
            /*for (unsigned short child_group_tag_index = 0; child_group_tag_index < tag_layout_header.num_child_group_tags; child_group_tag_index++)
            {
                s_h2_tag_group child_tag_group = tag_layout_header.child_group_tags[child_group_tag_index];
            }*/
        }

        for (unsigned long tag_layout_index = 0; tag_layout_index < halo2_num_tag_layouts; tag_layout_index++)
        {
            // tag layout
            ptr32 tag_layout_virtual_address = layout_addresses[tag_layout_index];
            const char* tag_layout_data = h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address);

            const s_h2_tag_group_definition tag_layout_header =
                *reinterpret_cast<const s_h2_tag_group_definition*>(h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address));

            std::string* tag_layout_name = tag_group_name_map[tag_layout_header.group_tag.value];

            // print out to tag def list
            s_h2_tag_group tag_group = tag_layout_header.group_tag;
            tag_definition_list_out << "#include \"" << tag_layout_name->c_str() << ".h\"\n";

            // definition header
            const char* definition_data = h2_va_to_pointer(guerilla_file_data, tag_layout_header.definition_address);
            const s_h2_tag_block_definition tag_block_definition_header = *reinterpret_cast<const s_h2_tag_block_definition*>(definition_data);

            // tag block names
            const char* tag_block_display_name = h2_va_to_pointer(guerilla_file_data, tag_block_definition_header.display_name_address);
            const char* tag_block_name = h2_va_to_pointer(guerilla_file_data, tag_block_definition_header.name_address);

            //std::cout << '\t' << tag_block_display_name << ", " << tag_layout_name << '\n';

            // print out tag def
            std::string tag_definition_path(*output_path);
            tag_definition_path += "\\" + *tag_layout_name + ".h";
            std::ofstream tag_definition_out(tag_definition_path);

            tag_definition_out <<
                "#pragma once\n\n" <<
                "#include \"tag_definitions_base.h\"\n\n" <<
                "namespace halo2\n" <<
                "{\n" <<
                "\tstruct " <<
                *tag_layout_name;

            // parent tag name
            if (tag_layout_header.parent_group_tag.value < ULONG_MAX)
            {
                tag_definition_out << " : " << *tag_group_name_map[tag_layout_header.parent_group_tag.value];
            }
            tag_definition_out << "\n\t{\n";

            bool unsupported_inheritance_flag = !!(tag_layout_header.inheritance_flags & 2);
            if (unsupported_inheritance_flag)
                continue;

            // latest field set
            s_h2_field_type_set_header field_set_header = *reinterpret_cast<const s_h2_field_type_set_header*>(h2_va_to_pointer(guerilla_file_data, tag_block_definition_header.field_set_latest_address));

            // go through fields
            const char* field_data = h2_va_to_pointer(guerilla_file_data, field_set_header.fields_address);
            const s_h2_field_type_definition* field = reinterpret_cast<const s_h2_field_type_definition*>(field_data);
            while (field->field_type != f_terminator)
            {
                if (field->field_type == f_block ||
                    field->field_type == f_tag_reference ||
                    field->field_type == f_enum)
                {
                    bool b = false;
                    //__debugbreak();
                }

                std::string* field_name;
                if (field->field_type == f_custom)
                {
                    field_name = new std::string("custom field");
                }
                else if (field->field_type == f_explanation)
                {
                    field_name = new std::string("explanation field");
                }
                else if (field->field_type == f_pad || field->field_type == f_useless_pad)
                {
                    field_name = new std::string("padding field");
                }
                else if (field->field_type == f_skip)
                {
                    field_name = new std::string("skip field");
                }
                else if (field->field_type == f_array_end)
                {
                    field_name = new std::string("array end field");
                }
                else if (field->name_address == empty_string_id)
                {
                    field_name = new std::string("\0");
                }
                else if (field->name_address <= max_h2alang_string_id)
                {
                    char name_buffer[name_buffer_max_length];

                    // we wanna use h2alang.dll
                    int loaded_string_length = LoadStringA(h2alang_handle, field->name_address, name_buffer, name_buffer_max_length);

                    if (loaded_string_length >= name_buffer_max_length)
                        loaded_string_length = name_buffer_max_length;

                    field_name = new std::string(name_buffer, loaded_string_length);
                }
                else
                {
                    const char* field_name_chars = h2_va_to_pointer(guerilla_file_data, field->name_address);
                    field_name = new std::string(field_name_chars);
                }

                util::sanitize_variable_name(*field_name);
                tag_definition_out <<
                    "\t\t" <<
                    halo2::get_actual_field_type(field->field_type) <<
                    " " <<
                    *field_name <<
                    ";\n";

                //std::cout << "\t\t" << field_name->c_str() << '\n';
                
                field++;
            }

            tag_definition_out << "\t};\n}" << std::endl;
            tag_definition_out.close();
        }

        tag_definition_list_out.close();
	}
}