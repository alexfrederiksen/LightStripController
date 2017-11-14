#include "led_controller.h"
#include "colors.h"

#include <math.h>

LedController::LedController(led_strip_t & leds) : leds(leds) { }

SnakeController::SnakeController(led_strip_t & leds, int length, float speed) : 
	LedController(leds), length(length), speed(speed), head_pos(0.0f) { }

void SnakeController::update() {
	// reset previous snake
	for (int i = 0; i < length; i++) {
		leds.set_led(((int) head_pos - i + leds.count) % leds.count,
			0, 0, 0);
	}
	// compute new position
	head_pos = fmod(head_pos + speed, leds.count);
	// draw new snake
	colors::color_rgb_t rgb;
	float interval = 360.0 / (float) length;
	for (int i = 0; i < length; i++) {
		// convert that hsv color to a cooler rgb color
		colors::convert_HSV2RGB(interval * i, 1.0f, 1.0f, rgb);
		leds.set_led(((int) head_pos - i + leds.count) % leds.count, 
			(int) (rgb.r * 255), 
			(int) (rgb.g * 255), 
			(int) (rgb.b * 255)); 
	}
	
}
