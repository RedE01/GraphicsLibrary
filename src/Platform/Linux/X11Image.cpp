#include "X11Image.h"
#include <cstring>

namespace rgl {

	X11Image::X11Image(x11::Display* display, x11::XVisualInfo* visualInfo, unsigned int bytesPerPixel, Vector2i size) : m_bytesPerPixel(bytesPerPixel) {
		char* buffer = (char*)malloc(size.x * size.y * m_bytesPerPixel);
		std::memset(buffer, 0, size.x * size.y * m_bytesPerPixel);
		m_ximage = x11::XCreateImage(display, visualInfo->visual, visualInfo->depth, ZPixmap, 0, buffer, size.x, size.y, m_bytesPerPixel * 8, 0);
	}

	X11Image::~X11Image() {
		XDestroyImage(m_ximage);
	}

	Vector2i X11Image::getSize() const {
		return Vector2i(m_ximage->width, m_ximage->height);
	}

	Vector3 X11Image::getPixel(Vector2i pos) const {
		Vector2i size = getSize();
		if(pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y) return Vector3();

		int offset = (pos.x + pos.y * size.x) * m_bytesPerPixel;
		unsigned int data = *((unsigned int*)(m_ximage->data + offset));
		Vector3 res;
		res.x = float((data & 0x00FF0000) >> 16) / 255.0;
		res.y = float((data & 0x0000FF00) >> 8) / 255.0;
		res.z = float((data & 0x000000FF) >> 0) / 255.0;
		return res;
	}

	void X11Image::setPixel(Vector2i pos, Vector3 value) {
		Vector2i size = getSize();
		if(pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y) return;

        value *= 255.0;
        unsigned int pixelVal = 0xFF000000 | ((unsigned int)value.x << 16) | ((unsigned int)value.y << 8) | (unsigned int)value.z;

        int offset = (pos.x + pos.y * size.x) * m_bytesPerPixel;
        *((unsigned int*)(m_ximage->data + offset)) = pixelVal;
	}

}