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

SnakeController::SnakeController(led_strip_t & leds, int length, float speed) : 
	LedController(leds), length(length), speed(speed), head_pos(0.0f) { }

void SnakeController::update() {
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

ScannerController::ScannerController(led_strip_t & leds, int length, float speed, colors::color_hsv_t & color) :
	LedController(leds), length(length), speed(speed), color(color), head_pos(0.0f) { }

void ScannerController::update() {
	// clear strip
	leds.clear_leds();
	// apply function to entire strip
	for (int i = 0; i < leds.count; i++) {
		// use parabolic function: -(x / lenght)^2 + 1 where x is head to led
		float a = (i - head_pos) / length;
		float v = -(a * a) + 1;
		if (v > 0.0f) {
			leds.set_led(i, colors::color_hsv_t(color.h, color.s, v));
		} 
	}
}

