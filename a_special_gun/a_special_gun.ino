#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    4
#define BRIGHTNESS  200
#define LED_PIN 5

const int motor_pin=12;
const int laser_pin=7;
const int trigger_button=2;

const int max_bullet=4;
const float bullet2led=NUM_LEDS/max_bullet;
int current_bullet=0;
int current_index=0;

int is_begin=0;
unsigned long last_charged_time=0;
unsigned long last_interrupt_time=0;
int led_charged_interval = 3000;
int animation_index = 0;
int animation_is_cleared=1;
int do_fire=0;

void setup() {
  Serial.begin(9600);
  laser_setup(laser_pin);
  motor_setup(motor_pin);
  led_setup();
  attachInterrupt(digitalPinToInterrupt(trigger_button), isr, RISING);
}

void loop() {
    if (! animation_is_cleared){
      clear_animation_led(animation_index);
      animation_is_cleared=1;
    }

    if (do_fire){
        do_fire=0;
        if(current_index){
          animation_is_cleared=0;
          digitalWrite(laser_pin, 1);
          digitalWrite(motor_pin, 1);
          delay(100);
          digitalWrite(motor_pin,0);
          digitalWrite(laser_pin,0);
          current_index = led_substract(current_index,round(bullet2led));
          last_charged_time = millis();
        }
    }
    
    while (!is_begin){
      led_startup_animation();
      if (is_begin){
         led_reset();
         last_charged_time = millis();
         break;
      }
    }
    if (millis()-last_charged_time>led_charged_interval and current_index != NUM_LEDS){
        current_index=led_charged(current_index);
        last_charged_time = millis();
        Serial.print("current_index: ");
        Serial.println(current_index);
    }
    else if (current_index < NUM_LEDS)
        led_charging_animation(current_index, 100);
    else
        delay(50);
}

/*
void bullet2leds(int bullet, int* current_index){
  *current_index += round(bullet*bullet2led);
  if (*current_index > NUM_LEDS) *current_index = NUM_LEDS;
  else if (*current_index < 0) *current_index = 0;
}*/

int leds2bullet(int current_index){
  int bullet = floor(current_index/bullet2led);
  if (bullet>max_bullet) bullet = max_bullet;
  else if (bullet<0) bullet=0;
  return bullet;
}

void isr(){
  if (millis() - last_interrupt_time > 500){
    is_begin=1;
    do_fire=1;
  }
  last_interrupt_time = millis();
}
