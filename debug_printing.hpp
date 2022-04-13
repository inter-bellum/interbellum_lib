#ifndef _INTERBELLUM_DEBUG_PRINTING_H
#define _INTERBELLUM_DEBUG_PRINTING_H


class DebugOut {
    public:
    enum VarType {F = 0, D, U8, U16, U32, I8, I16, I32};
    DebugOut(uint32_t print_interval, uint8_t num_values, enum VarType* types, void** vars, char* label_pattern, bool show_min_max);
    ~DebugOut();
    void set_types(enum VarType* types);
    void set_vars(void** vars);
    void set_num_vars(uint8_t n);
    void set_labels(String* labels);
    void print();

    protected:
    uint8_t num_values;
    uint32_t print_interval;
    void** variables;
    enum DebugOut::VarType* types;
    elapsedMillis debug_millis;
    String* labels;
    bool show_min_max;
};


class DebugPlot : DebugOut {
    public:
    DebugPlot(uint32_t print_interval, uint8_t num_values, enum VarType* types, void** vars) : DebugOut(print_interval, num_values, types, vars, "Value %d: "){};
    void print();
};

class DebugPrint : DebugOut {
    public:
    DebugPrint(uint32_t print_interval, uint8_t num_values, enum VarType* types, void** vars) : DebugOut(print_interval, num_values, types, vars, "v%d:"){};
    void print();
};

#endif