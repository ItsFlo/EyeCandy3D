#pragma once

#include <glm/glm.hpp>

namespace ec
{
	struct Vertex
	{
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec2 m_texCoords;
	};
}