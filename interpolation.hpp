#ifndef _INTERBELLUM_INTERPOLATION_H
#define _INTERBELLUM_INTERPOLATION_H

class interbellumInterpolator {
    protected:
    int number;
    float low_freq;
    float high_freq;
    float* frequency;
    float* frequency_mod;
    float* current_value;
    float phase;

    public:
    interbellumInterpolator(int number, float low_freq, float high_freq);
    float add_to_frequency(uint8_t idx, float added_amt);
    void update();
    float get(uint8_t idx);
};

class SineInterpolator : interbellumInterpolator {
    public:
    SineInterpolator(int number, float low_freq, float high_freq) : interbellumInterpolator(number, low_freq, high_freq){};
    void update();
};

class VolumeInterpolator : interbellumInterpolator {
    public:
    VolumeInterpolator(int number, float low_freq, float high_freq) : interbellumInterpolator(number, low_freq, high_freq){};
    void update();
    float output(uint8_t i);
};

#endif