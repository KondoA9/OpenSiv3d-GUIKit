﻿#include <Aoba/UICheckBox.hpp>

namespace s3d::aoba {
	void UICheckBox::initialize() {
		addEventListener<MouseEvent::LeftDown>([this] {
			setChecked(!m_checked);
			}, true);

		drawFrame = true;
		setCornerRadius(3_px);

		UIButton::initialize();
	}

	void UICheckBox::setChecked(bool checked) {
		m_checked = checked;
		setIcon(m_checked ? m_checkdIcon : Texture());
	}
}