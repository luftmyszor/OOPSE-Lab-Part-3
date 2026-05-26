#include "ADC.h"
#include <cmath>

template <typename T, int N>
T ADC<T, N>::convert(double voltage)
{
    if (voltage < rangeMin)
        voltage = rangeMin;
    if (voltage > rangeMax)
        voltage = rangeMax;

    double fraction = (voltage - rangeMin) / (rangeMax - rangeMin);

    if (rangeMin < 0.0)
    {
        double min_code = -std::pow(2, bits - 1);
        double max_code = std::pow(2, bits - 1) - 1;
        return static_cast<T>(min_code + fraction * (max_code - min_code));
    }
    else
    {
        double max_code = std::pow(2, bits) - 1;
        return static_cast<T>(fraction * max_code);
    }
}

template <typename T, int N>
size_t ADC<T, N>::read_input(std::vector<double> &inputs)
{
    size_t added_count = 0;
    for (double v : inputs)
    {
        if (samples.size() >= static_cast<size_t>(N))
        {
            break;
        }
        if (v > trigger_level)
        {
            samples.push_back(convert(v));
            added_count++;
        }
    }
    return added_count;
}

template <typename T, int N>
double ADC<T, N>::value(size_t i)
{
    if (i >= samples.size())
    {
        throw std::out_of_range("ADC sample index out of range.");
    }

    double fraction = 0.0;
    if (rangeMin < 0.0)
    {
        double min_code = -std::pow(2, bits - 1);
        double max_code = std::pow(2, bits - 1) - 1;
        fraction = (static_cast<double>(samples[i]) - min_code) / (max_code - min_code);
    }
    else
    {
        double max_code = std::pow(2, bits) - 1;
        fraction = static_cast<double>(samples[i]) / max_code;
    }

    double voltage = rangeMin + fraction * (rangeMax - rangeMin);

    return voltage * sensitivity;
}

template <typename T, int N>
std::vector<double> ADC<T, N>::values()
{
    std::vector<double> true_values;
    true_values.reserve(samples.size());
    for (size_t i = 0; i < samples.size(); ++i)
    {
        true_values.push_back(value(i));
    }
    return true_values;
}

template <typename T, int N>
std::string ADC<T, N>::to_string()
{
    return "ADC: bits=" + std::to_string(bits) +
           ", clock_rate=" + std::to_string(clock_rate.count()) + "ms" +
           ", range=[" + std::to_string(rangeMin) + "V, " + std::to_string(rangeMax) + "V]" +
           ", samples=" + std::to_string(samples.size()) + "/" + std::to_string(N);
}