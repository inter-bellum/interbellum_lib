#include "debug_printing.hpp"
#include "Arduino.h"

DebugOut::DebugOut(uint32_t print_interval, uint8_t num_values, VarType* types, void** vars, char* label_pattern, bool show_min_max=true){
    this->print_interval = print_interval;
    this->num_values = num_values;
    this->types = types;
    this->variables = vars;
    this->labels = (String*) malloc(sizeof(String) * num_values);

    for (uint8_t i = 0; i < num_values; i++){
        char buf[12] = {0};
        snprintf(buf, 12, label_pattern, i);
        labels[i] = String(buf);
    }
}

DebugOut::~DebugOut(){
    free(labels);
}

void DebugOut::set_types(VarType* types){
    this->types = types;
}

void DebugOut::set_vars(void** vars){
    this->variables = vars;
}

void DebugOut::set_num_vars(uint8_t num_vars){
    this->num_values = num_vars;
}

void DebugOut::print(){
    if (!print_interval || debug_millis >= print_interval){
        if (show_min_max){
            SERIAL_PORT_MONITOR.print("low:");
            SERIAL_PORT_MONITOR.print(0);
            SERIAL_PORT_MONITOR.print(",hi:");
            SERIAL_PORT_MONITOR.print(1023);
            SERIAL_PORT_MONITOR.print(",");
        }

        for (uint8_t i = 0; i < num_values; i++){
            SERIAL_PORT_MONITOR.print(labels[i]);
            switch(types[i]){
                case I8: {
                    SERIAL_PORT_MONITOR.print(*((int8_t*) variables[i]));
                    break;
                }
                case I16: {
                    SERIAL_PORT_MONITOR.print(*((int16_t*) variables[i]));
                    break;
                }
                case I32: {
                    SERIAL_PORT_MONITOR.print(*((int32_t*) variables[i]));
                    break;
                }
                case U8: {
                    SERIAL_PORT_MONITOR.print(*((uint8_t*) variables[i]));
                    break;
                }
                case U16: {
                    SERIAL_PORT_MONITOR.print(*((uint16_t*) variables[i]));
                    break;
                }
                case U32: {
                    SERIAL_PORT_MONITOR.print(*((uint32_t*) variables[i]));
                    break;
                }
                case F: {
                    SERIAL_PORT_MONITOR.print(*((float*) variables[i]));
                    break;
                }
                case D: {
                    SERIAL_PORT_MONITOR.print(*((double*) variables[i]));
                    break;
                }
            }

            if (i < num_values-1){
                SERIAL_PORT_MONITOR.print(",");
            }
        }

        SERIAL_PORT_MONITOR.println();
        debug_millis = 0;
    }
}
