#pragma once

#include "../UIRect/UIRect.h"

namespace s3d::gui {
	class UIImage : public UIRect {
	public:
		Image image;
		bool manualScalingEnabled = true;

	private:
		DynamicTexture m_texture;
		Rect m_textureRegion;
		double m_scale = 1.0;
		Point m_pixel, m_prePixel;

	public:
		UIImage(const ColorTheme& _backgroundColor = DynamicColor::BackgroundSecondary) :
			UIRect(_backgroundColor)
		{}

		void updateTexture() {
			m_texture.fill(image);
		}

		void setScale(double scale) {
			m_scale = scale;
		}

		void setScaleBy(double magnification) {
			m_scale *= magnification;
		}

		void resetScale() {
			m_scale = calcInitialScale();
		}

		void setImage(const Image& _image);

		void paint(double thickness, const Color& color, bool antialiased = true);

		void draw() override;

		void updateLayer() override;

	protected:
		bool mouseHovering() override;

		bool mouseDragging() override;

		bool mouseWheel() override;

	private:
		double calcInitialScale();
	};
}