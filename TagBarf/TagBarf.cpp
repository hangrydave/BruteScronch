// TagBarf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdlib.h>

using std::wstring;

int main(int argc, char **argv)
{
	size_t converted_char_count;
	wstring* halo1_guerilla_path = NULL;
	wstring* halo2_guerilla_path = NULL;
	wstring* output_path = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (i >= argc)
			break;

		char* arg = argv[i];
		if (strcmp(arg, "-h2") == 0)
		{
			i++;
			arg = argv[i];

			size_t len = strlen(arg);
			wchar_t* dest_buffer = new wchar_t[len];
			mbstowcs_s(&converted_char_count, dest_buffer, len + 1, arg, len);
			halo2_guerilla_path = new wstring(dest_buffer, len);
		}
		else if (strcmp(arg, "-h1") == 0)
		{
			i++;
			arg = argv[i];

			size_t len = strlen(arg);
			wchar_t* dest_buffer = new wchar_t[len];
			mbstowcs_s(&converted_char_count, dest_buffer, len + 1, arg, len);
			halo1_guerilla_path = new wstring(dest_buffer, len);
		}
		else if (strcmp(arg, "-o") == 0)
		{
			i++;
			arg = argv[i];

			size_t len = strlen(arg);
			wchar_t* dest_buffer = new wchar_t[len];
			mbstowcs_s(&converted_char_count, dest_buffer, len + 1, arg, len);
			output_path = new wstring(dest_buffer, len);
		}
	}

	if (halo2_guerilla_path == NULL || halo2_guerilla_path->empty())
	{
		std::cerr << "provide the path to halo 2 guerilla: -h2 <path>" << std::endl;
		return 1;
	}

	if (halo1_guerilla_path == NULL || halo1_guerilla_path->empty())
	{
		std::cerr << "provide the path to halo 1 guerilla: -h1 <path>" << std::endl;
		return 1;
	}

	if (output_path == NULL || output_path->empty())
	{
		std::cerr << "provide the path to an output folder: -o <path>" << std::endl;
		return 1;
	}
}
