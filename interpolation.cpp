#include "interpolation.hpp"
#include "Arduino.h"
#include <stdlib.h>


interbellumInterpolator::interbellumInterpolator(int number, float low_freq, float high_freq){
    this->number = number;
    this->low_freq = low_freq;
    this->high_freq = high_freq;
    frequency = (float*) malloc(sizeof(float)* number);
    frequency_mod = (float*) malloc(sizeof(float)* number);
    current_value = (float*) malloc(sizeof(float)* number);

    for (int i = 0; i < number; i++){
      frequency[i] = random(low_freq, high_freq);
    }
}

float interbellumInterpolator::add_to_frequency(uint8_t idx, float added_amt){
    frequency_mod[idx] = added_amt;
}

void interbellumInterpolator::update(){
    phase += 0.0001;
}

float interbellumInterpolator::get(uint8_t idx){
    if (idx < number){
      return current_value[idx];
    }

    return -1;
}



void SineInterpolator::update(){
    this->phase += 0.0001;

    for (int i = 0; i < number; i++){
        current_value[i] = (sin(this->phase * (frequency[i] + frequency_mod[i])) + 1) / 2.;
    }
}

float VolumeInterpolator::output(uint8_t i){
    float internal_phase = this->phase * (frequency[i] + frequency_mod[i]);
    if (internal_phase < .05){
      return ((1. - cos(internal_phase / .05)) + 1) / 2.;
    } else if (internal_phase >= .05 && internal_phase < .475){
      return 1;
    } else if (internal_phase >= .475 && internal_phase < .525){
      internal_phase -= .475;
      return ((cos(internal_phase / .05)) + 1) / 2.;
    } else {
      return 0;
    }
}

void VolumeInterpolator::update(){
    this->phase += 0.0001;

    for (int i = 0; i < number; i++){
      current_value[i] = this->output(i);
    }
}