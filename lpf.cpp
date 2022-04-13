#include "lpf.hpp"

LPF::LPF(float lowpass_amount){
    this->lowpass_amount = lowpass_amount;
}

void LPF::set_value(float new_val){
    target_value = new_val;
}

void LPF::update(){
    lowpassed_value = (lowpassed_value * lowpass_amount) + ((1. - lowpass_amount) * target_value);
}

void LPF::set_value_force(float new_val){
    lowpassed_value = new_val;
}

void LPF::set_if_greater(float new_val){
    if (new_val > lowpassed_value){
      lowpassed_value = new_val;
    }
}

void LPF::slow_tail_to_zero(){
    lowpassed_value = lowpassed_value * lowpass_amount;
}

void LPF::set_lowpass_amount(float amount){
    this->lowpass_amount = amount;
}

float LPF::get(){
    return lowpassed_value;
}
