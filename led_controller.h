#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "colors.h"
#include <math.h>

struct led_strip_t {
	int count;
	void (*set_led_native)(int id, int r, int g, int b);

	void clear_leds(int r, int g, int b);
	void clear_leds();
	void set_led(int i, const colors::color_rgb_t & rgb);
	void set_led(int i, const colors::color_hsv_t & hsv);
};

class LedController {
	protected:
		led_strip_t & leds;
	
	public:
		LedController(led_strip_t & leds);
		virtual void update() = 0;
};

class SnakeController : public LedController {
	int length;
	float speed;
	float head_pos;

	public:
		SnakeController(led_strip_t & leds, int length, float speed);
		void update();
};

class ScannerController : public LedController {
	int length;
	float speed;
	float head_pos;
	colors::color_hsv_t color;

	public:
		ScannerController(led_strip_t & leds, int length, float speed, colors::color_hsv_t & color);
		void update();
};

#endif
