#include "pch.h"
#include "high_level_biped_definition.h"

using namespace high_level;

const s_tag_struct* high_level_biped_definition::define()
{
	return define_struct(
		"biped",
		{
			define_field(f_angle, "yabadabadoo"),
			define_field(f_block, "eeehaheee", define_struct(
				"weehawoo",
				{
					define_field(f_real, "fsadkl;hj hodgsoihpa")
				}
			))
		}
	);
}
