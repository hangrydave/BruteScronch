// TagBarf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using std::string;

int main(int argc, char **argv)
{
	string* halo1_guerilla_path = NULL;
	string* halo2_guerilla_path = NULL;
	string* output_path = NULL;

	for (int i = 0; i < argc; i++)
	{
		if (i >= argc)
			break;

		char* arg = argv[i];
		if (arg == "-h2")
		{
			i++;
			arg = argv[i];
			halo2_guerilla_path = new string(arg);
		}
		else if (arg == "-h1")
		{
			i++;
			arg = argv[i];
			halo1_guerilla_path = new string(arg);
		}
		else if (arg == "-o")
		{
			i++;
			arg = argv[i];
			output_path = new string(arg);
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
