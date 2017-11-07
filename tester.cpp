#include "led_controller.h"

#include <iostream>

using namespace std;

void set_led(int id, int r, int g, int b) {
	cout << "Set " << id << " to (" << r << " " << g << " " << b << ")" << endl;
}

int main(int, char **) {
	// setup led strip
	led_strip_t leds = {
		100, 
		set_led
	};

	SnakeController controller(leds, 3, 1.0);

	for (int i = 0; i < 10; i++) {
		controller.update();
	}
}
