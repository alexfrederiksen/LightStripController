#include "led_controller.h"

LedController::LedController(led_strip_t & leds) : leds(leds) { }

/*
 * Clear all the leds with the given color
 */ 
void led_strip_t::clear_leds(int r, int g, int b) {
	for (int i = 0; i < count; i++) {
		set_led_native(i, r, g, b);
	}
}

/*
 * Clear all the leds to off RGB(0, 0, 0)
 */
void led_strip_t::clear_leds() {
	clear_leds(0, 0, 0);
}

void led_strip_t::set_led(int i, const colors::color_rgb_t & rgb) {
	set_led_native(i, 
		(int) (rgb.r * 255),
		(int) (rgb.g * 255),
		(int) (rgb.b * 255));
}

void led_strip_t::set_led(int i, const colors::color_hsv_t & hsv) {
	colors::color_rgb_t rgb;
	colors::convert_HSV2RGB(hsv, rgb);
	set_led(i, rgb); 
}

namespace controllers {

	Snake::Snake(led_strip_t & leds, int length, float speed) : 
		LedController(leds), length(length), speed(speed), head_pos(0.0f) { }

	void Snake::update() {
		// clear strip
		leds.clear_leds();
		// compute new position
		head_pos = fmod(head_pos + speed, leds.count);
		// draw new snake
		colors::color_rgb_t rgb;
		float interval = 360.0f / (float) length;
		for (int i = 0; i < length; i++) {
			// convert the hsv color to rgb one
			colors::convert_HSV2RGB(interval * i, 1.0f, 1.0f, rgb);
			leds.set_led(((int) head_pos - i + leds.count) % leds.count, rgb);  
		}	
	}
	
	Scanner::Scanner(led_strip_t & leds, int length, float speed, colors::color_hsv_t & color) :
		LedController(leds), length(length), speed(speed), color(color), step(0.0f) { }
	
	void Scanner::update() {
		// clear strip
		leds.clear_leds();
		step = fmod(step + speed, 1.0);	
		float head_pos = leds.count * (-2.0f * fabs(step - 0.5f) + 1.0f);
		// apply function to entire strip
		for (int i = 0; i < leds.count; i++) {
			// use parabolic function: -(x / (length / 2))^2 + 1 where x is head to led
			float a = (i - head_pos) / (length * 0.5f);
			float v = -(a * a) + 1;
			if (v > 0.0f) {
				leds.set_led(i, colors::color_hsv_t(color.h, color.s, v));
			} 
		}
	}
}
