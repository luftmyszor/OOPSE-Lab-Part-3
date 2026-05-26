#pragma once
#include <string>
#include <chrono>
#include <vector>
#include <stdexcept>

template <typename T=short, int N=1024>
struct ADC {
    int bits; // number of bits of the ADC
    std::chrono::milliseconds clock_rate; // clock rate in ms
    double rangeMin, rangeMax; // range of the ADC in volts
    double sensitivity;     // sensitivity in unit/volts
    double trigger_level;   // trigger level in volts
    std::vector<T> samples;
public:
    // convert the input voltage to the corresponding ADC value
    T convert(double voltage) {;}
    
    // read input values and if any of them is above
    // the trigger_level, append it to the 'samples'
    size_t read_input(std::vector<double>& inputs) {;}
    
    // evaluate the sample true value of the measured quantity
    double value(size_t i) {;}
    
    // evaluate true values for all collected samples
    std::vector<double> values() {;}
    
    // generate string representing the ADC data
    std::string to_string() {;}
};