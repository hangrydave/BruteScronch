#include "util.h"

namespace util
{
	void sanitize_variable_name(std::string& name)
	{
		int size = name.size();
		for (int i = 0; i < size; i++)
		{
			char c = name[i];
			if (c == '#')
			{
				// maybe instead of this rewrite this to generate the whole field line instead
				// that way you can put the explanation in a // comment
				size = i;
				break;
			}

			if (c != '_' && !std::isalpha(c) && !std::isdigit(c))
				name[i] = '_';
		}

		name = name.substr(0, size);
		if (std::isdigit(name[0]))
			name.insert(0, "_");
	}
}
