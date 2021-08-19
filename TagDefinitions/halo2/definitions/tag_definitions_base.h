#pragma once

#include "tag_field_types.h"
#include "../tag_structures.h"

using namespace tag_definition_common;

namespace halo2
{
	struct tag_struct {};

	struct object : tag_struct
	{
		short flags;
		float bounding_radius;
		point3d bounding_offset;
		enum16 lightmap_shadow_mode;
		s_tag_ref model;
	};
}
