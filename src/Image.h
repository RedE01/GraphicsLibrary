#pragma once
#include "Etc/Vector.h"

namespace rgl {

	class Image {
	public:
		virtual ~Image() {}

		virtual Vector2i getSize() const = 0;
		virtual Vector3 getPixel(Vector2i pos) const = 0;

		virtual void setPixel(Vector2i pos, Vector3 value) = 0;
	};

}