#include "colors.h"

#include <math.h>

namespace colors {

	void color_rgb_t::set(float r, float g, float b) {
		this -> r = r;
		this -> g = g;
		this -> b = b;
	}

	void color_hsv_t::set(float h, float s, float v) {
		this -> h = h;
		this -> s = s;
		this -> v = v;
	}

	void convert_HSV2RGB(color_hsv_t & hsv, color_rgb_t & rgb) {
		convert_HSV2RGB(hsv.h, hsv.s, hsv.v, rgb);
	}

	void convert_HSV2RGB(float h, float s, float v, color_rgb_t & rgb) {
		float c = s * v;
		float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
		float m = v - c;
		
		switch ((int) (h / 60.0f)) {
				// 0 <= h < 60
			case 0: rgb.set(c, x, 0.0f);
				break;
				// 60 <= h < 120
			case 1: rgb.set(x, c, 0.0f);
				break;
				// 120 <= h < 180
			case 2: rgb.set(0.0f, c, x);
				break;
				// 180 <= h < 240
			case 3: rgb.set(0.0f, x, c);
				break;
				// 240 <= h < 300
			case 4: rgb.set(x, 0.0f, c);
				break;
				// 300 <= h < 360
			case 5: rgb.set(c, 0.0f, x);
				break;
		}

		rgb.set(rgb.r + m,
			rgb.g + m,
			rgb.b + m);
	}
};
