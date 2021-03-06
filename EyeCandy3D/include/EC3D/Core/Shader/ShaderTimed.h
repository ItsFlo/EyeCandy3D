#pragma once
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Common/Common.h"

namespace ec
{
	class EC3D_DECLSPEC ShaderTimed : public Shader
	{
	public:
		explicit ShaderTimed(const std::string& vertPath,
							 const std::string& fragPath,
							 const std::string& geomPath = "",
							 const std::string& tessCtrlPath = "",
							 const std::string& tessEvalPath = "");
		~ShaderTimed();

		virtual void update(float time, float timeDelta);
	};
}