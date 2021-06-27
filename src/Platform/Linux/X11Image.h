#pragma once
#include "../../Image.h"
#include <cstdlib>

namespace x11 {
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
}

namespace rgl {

	class X11Image : public Image {
	public:
		X11Image(x11::Display* display, x11::XVisualInfo* visualInfo, unsigned int bytesPerPixel, Vector2i size);
		~X11Image();

		virtual Vector2i getSize() const override;
		virtual Vector3 getPixel(Vector2i pos) const override;

		virtual void setPixel(Vector2i pos, Vector3 value) override;

	private:
		x11::XImage* m_ximage;
		unsigned int m_bytesPerPixel;

		friend class X11Window;
	};

}