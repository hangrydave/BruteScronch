#include "util.h"

namespace util
{
	void sanitize_variable_name(std::string*& name, std::string*& comment)
	{
		size_t size = name->size();
		size_t name_end_index = size;
		for (int i = 0; i < size; i++)
		{
			char c = name->operator[](i);
			if (c == '#')
			{
				name_end_index = i;
				break;
			}

			if (c != '_' && !std::isalpha(c) && !std::isdigit(c))
				name->operator[](i) = '_';
		}

		if (name_end_index < size)
		{
			comment = new std::string(name->substr(name_end_index + 1, size - name_end_index));
		}
		size = name_end_index;

		*name = name->substr(0, size);
		if (std::isdigit(name->operator[](0)))
			*name = "_" + *name;

	}
}
