#ifndef COLORS_H
#define COLORS_H

namespace colors {
	struct color_rgb_t {
		float r;
		float g;
		float b;

		void set(float r, float g, float b);
	};

	struct color_hsv_t {
		float h;
		float s;
		float v;

		void set(float h, float s, float v);
	};

	void convert_HSV2RGB(color_hsv_t & hsv, color_rgb_t & rgb);

	void convert_HSV2RGB(float h, float s, float v, color_rgb_t & rgb);
};

#endif
