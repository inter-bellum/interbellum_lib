#include "sensor_tracker.hpp"
#include "Arduino.h"
#include <stdint.h>

SensorTracker::SensorTracker(uint8_t pin, uint16_t low, uint16_t high, bool is_invert, float scale_amount){
    this->pin = pin;
    this->low = low;
    this->high = high;
    this->is_invert = is_invert;
    this->scale_amount = scale_amount;
}

void SensorTracker::set_value(uint16_t new_value){
    scale_sensor_values(new_value, scale_amount);
    calculate_delta();
    raw_value = new_value;
}

void SensorTracker::calculate_delta(){
    delta_value = abs(scaled_value - old_scaled_value);
    old_scaled_value = scaled_value;
}

float SensorTracker::get_scaled_value(){
    return scaled_value;
}

float SensorTracker::get_delta(){
    return delta_value;
}

uint8_t SensorTracker::get_pin(){
    return pin;
}

uint16_t SensorTracker::get_low(){
    return low;
}

uint16_t SensorTracker::get_high(){
    return high;
}

float SensorTracker::scale_sensor_values(uint16_t reading, float range){
    float t_scaled_val = ((reading - low) / ((float) (high - low))) * range;
    if (is_invert){
      scaled_value = 1. - t_scaled_val;
    } else {
      scaled_value = t_scaled_val;
    }
    return t_scaled_val;
}