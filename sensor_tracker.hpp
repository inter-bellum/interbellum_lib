#ifndef _INTERBELLUM_SENSOR_TRACKER_H
#define _INTERBELLUM_SENSOR_TRACKER_H

class SensorTracker {
    private:
    uint8_t pin;
    uint16_t low;
    uint16_t high;
    bool is_invert;
    float scale_amount;

    float delta_value;
    float scaled_value;
    float old_scaled_value;

    uint16_t raw_value;

    public:
    SensorTracker(uint8_t pin, uint16_t low, uint16_t high, bool is_invert, float scale_amount);
    void set_value(uint16_t new_value);
    void calculate_delta();
    float get_scaled_value();
    float get_delta();
    uint8_t get_pin();
    uint16_t get_low();
    uint16_t get_high();
    float scale_sensor_values(uint16_t reading, float range);
};

#endif