#include <FastLED.h>
CRGB leds[NUM_LEDS];

void led_setup(){
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );
    led_reset();
}

void set_led(int led_index, int r, int g, int b){
      leds[led_index].r = r;
      leds[led_index].g = g;
      leds[led_index].b = b;
      FastLED.show();
}

void led_reset(){
    for (int i=0; i< NUM_LEDS;i++){
      set_led(i,50,0,0);
    }
}

void led_startup_animation(){
    for (int i=0; i< NUM_LEDS;i++){
      if (!i) set_led(NUM_LEDS-1,50,0,0);
      set_led(i,0,50,0);
      if (i) set_led(i-1,50,0,0);
      delay(200);
    }
}

void led_charging_animation(int pending_index, int delay_time){
    animation_index=pending_index;
    set_led(pending_index,50,0,0);
    delay(delay_time);
    set_led(pending_index,0,0,50);
    delay(delay_time);
}

void clear_animation_led(int index){
  set_led(index,50,0,0);
}
/*
void led_charged(int* current_index){
    int temp = * current_index;
    if (temp < NUM_LEDS){
      set_led(temp,0,50,0);
      *current_index=temp+1;
    }
    else
      *current_index = NUM_LEDS - 1;
}*/

int led_charged(int current_index){
    if (current_index < NUM_LEDS){
      set_led(current_index,0,50,0);
      return current_index+1;
    }
    else
      return NUM_LEDS;
}
/*
void led_substract(int* current_index, int num){
    int index = *current_index;
    if (index-num<0) num=index;
    for (int i=num; i>= 0;i--){
      set_led(index-i,50,0,0);
    }
    *current_index -= num;
}*/


int led_substract(int current_index, int num){
    if (current_index-num<0) num=current_index;
    for (int i=num; i>= 0;i--){
      set_led(current_index-i,50,0,0);
    }
    return current_index -= num;
}
