﻿#include "Aoba/UIToggleButton.hpp"

namespace s3d::aoba {
    ColorTheme UIToggleButton::DefaultSelectedColor     = DynamicColor::BackgroundSecondary;
    ColorTheme UIToggleButton::DefaultSelectedTextColor = Palette::White;

    void UIToggleButton::initialize() {
        UIText::initialize();

        hoveredTextColor = Palette::White;
        cursorStyle      = CursorStyle::Hand;

        addEventListener<Event::Mouse::LeftDown>(
            [this] {
                setEnabled(!m_enabled);
            },
            true);

        addEventListener<Event::Mouse::Hovered>(
            [this] {
                if (!m_enabled) {
                    backgroundColor.highlight(hoveredColor);
                } else {
                    backgroundColor.highlight(selectedColor);
                }
            },
            true);

        addEventListener<Event::Mouse::UnHovered>(
            [this] {
                if (!m_enabled) {
                    backgroundColor.lowlight(defaultColor);
                } else {
                    backgroundColor.highlight(selectedColor);
                }
            },
            true);
    }
}
