#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

struct led_strip_t {
	int count;
	void (*set_led)(int id, int r, int g, int b);
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

#endif
