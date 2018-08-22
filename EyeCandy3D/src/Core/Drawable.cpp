#include "EC3D/Common/Config.h"

#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Material.h"

#include <string>
#include <sstream>
#include <GL/glew.h>

namespace ec
{
	Drawable::Drawable()
		: m_geometry{nullptr},
		m_material{nullptr},
		m_shader{nullptr}
	{
	}

	Drawable::Drawable(Geometry* geometry, Material* material, Shader* shader)
		: m_geometry{geometry},
		m_material{material},
		m_shader{shader}
	{
	}

	Drawable::~Drawable() = default;

	void Drawable::init(Geometry* geometry, Material* material, Shader* shader)
	{
		m_geometry = geometry;
		m_material = material;
		m_shader = shader;
	}

	void Drawable::beginRender(const glm::mat4& model)
	{
		m_shader->bind();
		m_shader->setMat4("model", model);
		setMaterialUniforms(m_shader, m_material);
	}

	void Drawable::render(const glm::mat4& model)
	{
		beginRender(model);
		render(m_shader, model);
		endRender();
	}

	void Drawable::render(Shader* shader, const glm::mat4& model)
	{
		m_geometry->render(shader, model);
	}

	void Drawable::endRender()
	{
		m_shader->unbind();
	}

	void Drawable::setMaterialUniforms(Shader* shader, Material* material)
	{
		if(material)
		{
			/* Set uniform flat colors */
			shader->setVec4(conf_shader::g_materialAmbient, material->getColorAmbient());
			shader->setVec4(conf_shader::g_materialDiffuse, material->getColorDiffuse());
			shader->setVec4(conf_shader::g_materialSpecular, material->getColorSpecular());
			shader->setVec4(conf_shader::g_materialEmissive, material->getColorEmissive());
			shader->setFloat(conf_shader::g_materialShininess, material->getShininess());
			shader->setBool(conf_shader::g_materialHasTexture, material->hasTexture());

			/* Activate textures */
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			const auto& textures = material->getTextures();
			for(unsigned int i = 0; i < textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
												  // retrieve texture number (the N in diffuse_textureN)
				std::stringstream ss;
				const auto name = textures[i].getType();
				if(name == conf_shader::g_textureDiffuse)
				{
					ss << diffuseNr++; // transfer unsigned int to stream
				}					
				else if(name == conf_shader::g_textureSpecular)
				{
					ss << specularNr++; // transfer unsigned int to stream
				}					
				const auto number = ss.str();

				shader->setInt(("material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].getId());
			}
		}
		else
		{
			/* Set uniform flat colors */
			shader->setVec4(conf_shader::g_materialAmbient, conf_shader::g_materialAmbientDefault);
			shader->setVec4(conf_shader::g_materialDiffuse, conf_shader::g_materialDiffuseDefault);
			shader->setVec4(conf_shader::g_materialSpecular, conf_shader::g_materialSpecularDefault);
			shader->setVec4(conf_shader::g_materialEmissive, conf_shader::g_materialEmissiveDefault);
			shader->setFloat(conf_shader::g_materialShininess, conf_shader::g_materialShininessDefault);
			shader->setBool(conf_shader::g_materialHasTexture, conf_shader::g_materialHasTextureDefault);
		}
	}

	void Drawable::setGeometry(Geometry* geometry)
	{
		m_geometry = geometry;
	}

	ec::Geometry* Drawable::getGeometry()
	{
		return m_geometry;
	}

	void Drawable::setMaterial(Material* material)
	{
		m_material = material;
	}

	ec::Material* Drawable::getMaterial()
	{
		return m_material;
	}

	void Drawable::setShader(Shader* shader)
	{
		m_shader = shader;
	}

	ec::Shader* Drawable::getShader()
	{
		return m_shader;
	}
}