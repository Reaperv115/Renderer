#pragma once

namespace glitc
{
	// vertex data structure
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;

		struct
		{
			float u, v;
		} col;
	};
}