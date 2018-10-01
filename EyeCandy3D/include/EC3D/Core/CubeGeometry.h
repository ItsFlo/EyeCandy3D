#pragma once
#include "EC3D/Core/StaticGeometry.h"
#include "EC3D/Common/Common.h"

/*
* Specialized geometry
* Initializes vertices, normals and texture coordinates of a cube
*/
namespace ec
{
	class EC3D_DECLSPEC CubeGeometry : public StaticGeometry
	{
	public:
		explicit CubeGeometry(float uniformSize = 1.0f);
		explicit CubeGeometry(float width, float height, float depth);
		~CubeGeometry();

		void resize(float width, float height, float depth);

		float getWidth() const;
		float getHeight() const;
		float getDepth() const;

	private:
		void init(float width, float height, float depth);

		float m_width;
		float m_height;
		float m_depth;
	};
}