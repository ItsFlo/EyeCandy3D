#pragma once
#include "Widget.h"

#include <functional>

/*
* Checkbox GUI element
* Can handle callbacks for selection and de-selection
*/
namespace ec_gui
{
	class Checkbox : public Widget
	{
	public:
		explicit Checkbox(Widget* parent);
		virtual ~Checkbox();

		/* Set the callback, for when the check box gets enabled */
		void setSelectedCallback(std::function<void()> callback);
		/* Set the callback, for when the check box gets disabled */
		void setDeselectedCallback(std::function<void()> callback);

		/* Selection access */
		virtual void select(bool selected);
		virtual void toggleSelection();
		bool isSelected() const;

		bool onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;

	protected:
		std::function<void()> m_selectedCallback;
		std::function<void()> m_deselectedCallback;

		bool m_selected;

	private:
		void updateDrawable();
	};
}