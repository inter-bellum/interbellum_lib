#ifndef _INTERBELLUM_LPF_H
#define _INTERBELLUM_LPF_H


class LPF {
    private:
    float lowpass_amount;
    float lowpassed_value;
    float target_value;
    

    public:
    LPF(float lowpass_amount);
    void update();
    float get();
    void set_value(float new_val);
    void set_value_force(float new_val);
    void set_if_greater(float new_val);
    void slow_tail_to_zero();
    void set_lowpass_amount(float amount);
};

#endif