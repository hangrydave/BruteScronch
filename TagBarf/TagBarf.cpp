// TagBarf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include "h2_guerilla_dumper.h"

using std::string;

int main(int argc, char **argv)
{
	size_t converted_char_count;
	string* halo1_guerilla_path = NULL;
	string* halo2_guerilla_path = NULL;
	string* h2alang_path = NULL;
	string* output_path = NULL;

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
			halo2_guerilla_path = new string(arg, len);
		}
		else if (strcmp(arg, "-h2alang") == 0)
		{
			i++;
			arg = argv[i];

			size_t len = strlen(arg);
			h2alang_path = new string(arg, len);
		}
		else if (strcmp(arg, "-h1") == 0)
		{
			i++;
			arg = argv[i];

			size_t len = strlen(arg);
			halo1_guerilla_path = new string(arg, len);
		}
		else if (strcmp(arg, "-o") == 0)
		{
			i++;
			arg = argv[i];

			size_t len = strlen(arg);
			output_path = new string(arg, len);
		}
	}

	if (halo2_guerilla_path == NULL || halo2_guerilla_path->empty())
	{
		std::cerr << "provide the path to halo 2 guerilla executable: -h2 <path>" << std::endl;
		return 1;
	}

	if (h2alang_path == NULL || h2alang_path->empty())
	{
		std::cerr << "provide the path to h2alang.dll: -h2alang <path>" << std::endl;
		return 1;
	}

	if (halo1_guerilla_path == NULL || halo1_guerilla_path->empty())
	{
		std::cerr << "provide the path to halo 1 guerilla executable: -h1 <path>" << std::endl;
		return 1;
	}

	if (output_path == NULL || output_path->empty())
	{
		std::cerr << "provide the path to an output folder: -o <path>" << std::endl;
		return 1;
	}

	halo2::dump(halo2_guerilla_path, h2alang_path, output_path);
}
