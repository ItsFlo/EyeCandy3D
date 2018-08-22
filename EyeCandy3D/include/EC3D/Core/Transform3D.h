#pragma once
#include "EC3D/Common/Config.h"

#include <glm/glm.hpp>

namespace ec
{
	class Transform3D
	{
	public:
		explicit Transform3D(const glm::vec3& position = glm::vec3(0.0f),
							 const glm::vec3& scale = glm::vec3(1.0f),
							 const glm::vec3& orientation = conf::g_coordinateSystemOrientation);
		virtual ~Transform3D();

		/** 
		 * This function should be called once before accessing the local
		 * matrix, if a prior transformation has been executed.
		 * Create a new local mat from the current position, rotation and
		 * scale. 
		 */
		virtual void updateLocalMat();

		/** 
		 * Get the current local position .
		 * Performance critical, since the local matrix has to be updated.
		 */
		const glm::vec3& getLocalPosition();

		/** Get the current view matrix. */
		const glm::mat4& getLocalMat() const;
		/** Get the current up vector. */
		const glm::vec3& getUpVector() const;
		/** Get the current forward vector. */
		const glm::vec3& getForwardVector() const;

		/** 
		 * Get the current translation 
		 * WITHOUT scale and rotation applied!
		 */
		const glm::vec3& getTranslation() const;
		/** Get the x component of the current translation */
		float getTranslationX() const;
		/** Get the y component of the current translation */
		float getTranslationY() const;
		/** Get the z component of the current translation */
		float getTranslationZ() const;

		/** Adds the given coordinates to the current position. */
		void translate(float x, float y, float z);
		/** Adds the given vector to the current position. */
		void translate(const glm::vec3& v);
		/** Adds the given value to the current x-coordinate. */
		void translateX(float x);
		/** Adds the given value to the current y-coordinate. */
		void translateY(float y);
		/** Adds the given value to the current z-coordinate. */
		void translateZ(float z);

		/** Assign the given position to the current position. */
		void setTranslation(const glm::vec3& translation);
		/** Assign the given position to the current position. */
		void setTranslation(float x, float y, float z);
		/** Assign the given value to the current x-coordinate. */
		void setTranslationX(float x);
		/** Assign the given value to the current y-coordinate. */
		void setTranslationY(float y);
		/** Assign the given value to the current z-coordinate. */
		void setTranslationZ(float z);

		/** 
		 * Translate by the given coordinates and with respect to the
		 * current orientation.
		 */
		void translateLocal(float x, float y, float z);
		/**
		* Translate by the given vector and with respect to the
		* current orientation.
		*/
		void translateLocal(const glm::vec3& v);

		/** Rotate with a quaternion. */
		void rotate(const glm::quat& rot);
		/** Rotate around an axis by a given angle. */
		void rotate(float angle, const glm::vec3& axis);
		/** Rotate around the x axis by a given angle. */
		void rotateX(float angle);
		/** Rotate around the y axis by a given angle. */
		void rotateY(float angle);
		/** Rotate around the z axis by a given angle. */
		void rotateZ(float angle);

		/** Rotate around the local x axis by a given angle */
		void rotateXLocal(float angle);
		/** Rotate around the local y axis by a given angle */
		void rotateYLocal(float angle);
		/** Rotate around the local z axis by a given angle */
		void rotateZLocal(float angle);

		/** Get the current scale. */
		const glm::vec3& getScale() const;
		/** Get the x component of the scale. */
		float getScaleX() const;
		/** Get the y component of the scale. */
		float getScaleY() const;
		/** Get the z component of the scale. */
		float getScaleZ() const;

		/** Multiplicative scaling of the current scale. */
		void scale(float sx, float sy, float sz);
		/** Multiplicative scaling of the current scale. */
		void scale(const glm::vec3& val);
		/** Multiplicatively scale the x scale component. */
		void scaleX(float sx);
		/** Multiplicatively scale the y scale component. */
		void scaleY(float sy);
		/** Multiplicatively scale the z scale component. */
		void scaleZ(float sz);

		/** Assign the given value to the current scale. */
		void setScale(const glm::vec3& val);
		/** Assign the given value to the current scale. */
		void setScale(float sx, float sy, float sz);
		/** Assign the given value to the current x-scale component. */
		void setScaleX(float sx);
		/** Assign the given value to the current x-scale component. */
		void setScaleY(float sy);
		/** Assign the given value to the current x-scale component. */
		void setScaleZ(float sz);

	protected:
		glm::vec3 m_up;
		glm::vec3 m_position;
		glm::vec3 m_forwardVector;
		glm::vec3 m_scale;

	private:
		glm::mat4 m_localMat;
	};
}