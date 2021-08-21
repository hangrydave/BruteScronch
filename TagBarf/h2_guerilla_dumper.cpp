#include <assert.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "h2_guerilla_dumper.h"
#include "tag_field_types.h"
//#include "halo2/definitions/bipd.h"
#include "util.h"
//#include "halo2/tag_structures.h"

//#include <Windows.h>

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
    void dump_struct(
        const std::string* name,
        const ptr32& definition_address,
        const std::unordered_map<unsigned long, std::string*>& tag_group_name_map,
        std::vector<std::string*>* tag_layout_structures,
        std::string* parent_name = nullptr);

    void dump_field(
        s_h2_field_type_definition*& field,
        const std::unordered_map<unsigned long, std::string*>& tag_group_name_map,
        std::string* container_structure_code,
        std::vector<std::string*>* tag_layout_structures);

    void read_string(const ptr32& address, std::string*& value)
    {
        if (address <= max_h2alang_string_id)
        {
            // we wanna use h2alang.dll

            char name_buffer[name_buffer_max_length];

            int loaded_string_length = LoadStringA(h2alang_handle, address, name_buffer, name_buffer_max_length);
            if (loaded_string_length >= name_buffer_max_length)
                loaded_string_length = name_buffer_max_length;

            value = new std::string(name_buffer, loaded_string_length);
        }
        else
        {
            const char* field_name_chars = h2_va_to_pointer(guerilla_file_data, address);
            value = new std::string(field_name_chars);
        }
    }

    void dump_struct(
        const std::string* name,
        const ptr32& definition_address,
        const std::unordered_map<unsigned long, std::string*>& tag_group_name_map,
        std::vector<std::string*>* tag_layout_structures,
        std::string* parent_name)
    {
        // definition header
        const char* definition_data = h2_va_to_pointer(guerilla_file_data, definition_address);
        const s_h2_tag_block_definition tag_block_definition_header = *reinterpret_cast<const s_h2_tag_block_definition*>(definition_data);

        // tag block names
        const char* tag_block_display_name = h2_va_to_pointer(guerilla_file_data, tag_block_definition_header.display_name_address);
        const char* tag_block_name = h2_va_to_pointer(guerilla_file_data, tag_block_definition_header.name_address);

        // latest field set
        s_h2_field_type_set_header field_set_header = *reinterpret_cast<const s_h2_field_type_set_header*>(h2_va_to_pointer(guerilla_file_data, tag_block_definition_header.field_set_latest_address));

        std::string* structure_code = new std::string();
        structure_code->append(
            "\tstruct s_" +
            *name);

        structure_code->append("\n\t{\n");

        if (parent_name != nullptr)
        {
            structure_code->append(
                "\t\ts_" +
                *parent_name +
                " parent_" +
                *parent_name +
                "_data;\n");
        }

        // go through fields
        char* field_data = h2_va_to_pointer(guerilla_file_data, field_set_header.fields_address);
        s_h2_field_type_definition* field = reinterpret_cast<s_h2_field_type_definition*>(field_data);
        while (field->type != f_terminator)
        {
            dump_field(field, tag_group_name_map, structure_code, tag_layout_structures);

            field++;
        }

        structure_code->append("\t};");

        tag_layout_structures->push_back(structure_code);
    }

    void dump_field(
        s_h2_field_type_definition*& field,
        const std::unordered_map<unsigned long, std::string*>& tag_group_name_map,
        std::string* container_structure_code,
        std::vector<std::string*>* tag_layout_structures)
    {
        if (field->type == f_custom ||
            field->type == f_useless_pad)
            return;

        // figure out the field name
        std::string* field_name;
        std::string* field_comment = nullptr;

        if (field->type == f_array_end)
        {
            field_name = new std::string("array end field");
        }
        else if (field->name_address == empty_string_id)
        {
            field_name = new std::string("\0");
        }
        else
        {
            read_string(field->name_address, field_name);

            if (field->type != f_explanation)
            {
                util::sanitize_variable_name(field_name, field_comment);
            }
        }

        // dump the field
        if (field->type == f_struct)
        {
            const s_h2_tag_struct_definition tag_struct = *reinterpret_cast<const s_h2_tag_struct_definition*>(h2_va_to_pointer(guerilla_file_data, field->definition_address));

            std::string* name;
            std::string* display_name;
            read_string(tag_struct.name_address, name);
            read_string(tag_struct.display_name_address, display_name);

            const s_h2_tag_block_definition struct_block = *reinterpret_cast<const s_h2_tag_block_definition*>(h2_va_to_pointer(guerilla_file_data, tag_struct.block_definition_address));

            std::string* block_name;
            std::string* block_display_name;
            read_string(struct_block.name_address, block_name);
            read_string(struct_block.display_name_address, block_display_name);

            bool b = true;

            std::string* comment; // useless
            util::sanitize_variable_name(name, comment);

            container_structure_code->append("\t\ts_" + *name + " " + *name + ";\n");
            dump_struct(name, tag_struct.block_definition_address, tag_group_name_map, tag_layout_structures);
        }
        else if (field->type == f_block)
        {            
            const s_h2_tag_block_definition struct_block = *reinterpret_cast<const s_h2_tag_block_definition*>(h2_va_to_pointer(guerilla_file_data, field->definition_address));

            std::string* block_name;
            std::string* block_display_name;
            read_string(struct_block.name_address, block_name);
            read_string(struct_block.display_name_address, block_display_name);

            bool b = true;

            std::string* comment; // useless
            util::sanitize_variable_name(block_name, comment);

            container_structure_code->append("\t\ts_tag_block " + *block_display_name + ";\n");
            dump_struct(block_name, field->definition_address, tag_group_name_map, tag_layout_structures);
        }
        else if (field->type == f_array_start)
        {
            size_t count = field->definition_address;
            size_t size = 0;
            field++;
            while (field->type != f_array_end && field->type != f_terminator)
            {
                size += get_field_size(field->type);
                field++;
            }
            container_structure_code->append("\t\tbyte " + *field_name + "[" + std::to_string(count) + "];\n");
        }
        else if (field->type == f_pad)
        {
            size_t pad_length = field->definition_address;
            container_structure_code->append("\t\tbyte padding[" + std::to_string(pad_length) + "];\n");
        }
        else if (field->type == f_skip)
        {
            size_t skip_length = field->definition_address;
            container_structure_code->append("\t\tbyte skip[" + std::to_string(skip_length) + "];\n");
        }
        else if (field->type == f_array_end)
        {
            container_structure_code->append("uh oh uh oh uh oh uh oh\n");
        }
        else if (field->type == f_explanation)
        {
            std::string* explanation;
            read_string(field->definition_address, explanation);
            container_structure_code->append(
                "\t\t"
                "// " +
                *field_name +
                "\n");

            if (!explanation->empty())
            {
                container_structure_code->append("\t\t// ");

                int size = explanation->size();
                for (int i = 0; i < explanation->size(); i++)
                {
                    char c = explanation->operator[](i);
                    container_structure_code->operator+=(c);

                    if (i != size - 1)
                    {
                        if (c == '\n')
                        {
                            container_structure_code->append("\t\t// ");
                        }
                    }

                    if (i == size - 1)
                    {
                        if (c != '\n')
                        {
                            container_structure_code->append("\n");
                        }
                    }
                }
            }
        }
        else
        {
            container_structure_code->append(
                "\t\t" +
                std::string(halo2::get_field_code_type(field->type)) +
                " " +
                *field_name +
                ";");

            if (field_comment != nullptr)
            {
                container_structure_code->append(" // " + *field_comment);
            }

            container_structure_code->append("\n");
        }
    }

    void dump_tag_layout(
        const s_h2_tag_layout_definition& tag_layout_header,
        const std::string* tag_layout_name,
        const std::unordered_map<unsigned long, std::string*>& tag_group_name_map,
        std::string*& file_code)
    {
        file_code = new std::string();
        file_code->append(
            "#pragma once\n\n"
            "#include \"tag_definitions_base.h\"\n\n"
            "namespace halo2\n"
            "{\n");

        std::string* parent_name = nullptr;
        if (tag_layout_header.parent_group_tag.value < ULONG_MAX)
        {
            parent_name = tag_group_name_map.at(tag_layout_header.parent_group_tag.value);
        }

        std::vector<std::string*>* tag_layout_structures = new std::vector<std::string*>();
        dump_struct(tag_layout_name, tag_layout_header.definition_address, tag_group_name_map, tag_layout_structures, parent_name);

        for (int i = 0; i < tag_layout_structures->size(); i++)
        {
            std::string* structure_code = tag_layout_structures->at(i);
            file_code->append(*structure_code + "\n\n");
        }

        file_code->append("}\n");
    }

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
        guerilla_file_data = new char[guerilla_data_length];
        guerilla_file_in.read(guerilla_file_data, guerilla_data_length);
        guerilla_file_in.close();

        // h2alang.dll
        size_t converted_num;
        wchar_t* wide_path = new wchar_t[h2alang_path->size()];
        mbstowcs_s(&converted_num, wide_path, h2alang_path->size() + 1, h2alang_path->c_str(), h2alang_path->size());
        h2alang_handle = LoadLibraryW(wide_path);

        std::unordered_map<unsigned long, std::string*> tag_group_name_map;

        s_h2_tag_layout_definition tag_layout_headers[halo2_num_tag_layouts];

        ptr32(&layout_addresses)[halo2_num_tag_layouts] = *reinterpret_cast<decltype(&layout_addresses)>(guerilla_file_data + h2_va_to_pa(halo2_tag_layout_table_address));
        for (unsigned long tag_layout_index = 0; tag_layout_index < halo2_num_tag_layouts; tag_layout_index++)
        {
            // tag layout
            ptr32 tag_layout_virtual_address = layout_addresses[tag_layout_index];
            const char* tag_layout_data = h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address);

            const s_h2_tag_layout_definition tag_layout_header = *reinterpret_cast<const s_h2_tag_layout_definition*>(h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address));

            // get and sanitize layout name
            std::string* tag_layout_name = new std::string(h2_va_to_pointer(guerilla_file_data, tag_layout_header.name_address));
            std::string* useless_comment = nullptr; // nothingburger
            util::sanitize_variable_name(tag_layout_name, useless_comment);

            //tag_layout_name->append("_definition");
            tag_group_name_map[tag_layout_header.group_tag.value] = tag_layout_name;

        }

        for (unsigned long tag_layout_index = 0; tag_layout_index < halo2_num_tag_layouts; tag_layout_index++)
        {
            // tag layout
            ptr32 tag_layout_virtual_address = layout_addresses[tag_layout_index];

            const s_h2_tag_layout_definition tag_layout_header =
                *reinterpret_cast<const s_h2_tag_layout_definition*>(h2_va_to_pointer(guerilla_file_data, tag_layout_virtual_address));

            bool unsupported_inheritance_flag = !!(tag_layout_header.inheritance_flags & 2);
            if (unsupported_inheritance_flag)
                continue; // todo: find out why i need to do this and what it means. currently only happens with snd!

            const std::string* tag_layout_name = tag_group_name_map.at(tag_layout_header.group_tag.value);

            const std::string file_name = *tag_layout_name + "_definition";
            tag_definition_list_out << "#include \"" << file_name.c_str() << ".h\"\n";

            std::string* tag_layout_code = nullptr;
            dump_tag_layout(tag_layout_header, tag_layout_name, tag_group_name_map, tag_layout_code);

            // print out tag def
            std::string tag_definition_path(*output_path);
            tag_definition_path += "\\" + file_name + ".h";
            std::ofstream tag_definition_out(tag_definition_path);

            tag_definition_out << *tag_layout_code << std::endl;
        }

        tag_definition_list_out.close();
	}
}
