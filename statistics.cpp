#include "statistics.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

///############################################################
/// @class Min
///############################################################
Min::Min()
    : m_min{std::numeric_limits<double>::max()} {}

void Min::update(double next)
{
    if (next < m_min) {
        m_min = next;
    }
}

double Min::eval() const
{
    return m_min;
}

const char *Min::name() const
{
    return "min";
}

///############################################################
/// @class Max
///############################################################
Max::Max()
    : m_max{std::numeric_limits<double>::min()} {}

void Max::update(double next)
{
    if (next > m_max) {
        m_max = next;
    }
}

double Max::eval() const
{
    return m_max;
}

const char *Max::name() const
{
    return "max";
}

///############################################################
/// @class mean
///############################################################
Mean::Mean()
    : m_mean{0}
    , m_size{0} {}

void Mean::update(double next)
{
    m_mean += next;
    m_size++;
}

double Mean::eval() const
{
    return m_mean / m_size;
}

const char *Mean::name() const
{
    return "mean";
}

///############################################################
/// @class Std
///############################################################
Std::Std(double mean)
    : mean(mean)
    , m_size{0}
    , m_std{0} {}

void Std::update(double next)
{
    m_std += pow(next - mean, 2);
    m_size++;
}

double Std::eval() const
{
    return  sqrt(m_std / m_size);
}

const char *Std::name() const
{
    return "std";
}

///############################################################
/// @class Pct
///############################################################
Pct::Pct(std::vector<double> vector, PctType type)
    : m_vector(vector)
    , m_type(type) {}

void Pct::update(double next)
{
    std::sort(m_vector.begin(), m_vector.end());
}

double Pct::eval() const
{
    switch (m_type)
    {
    case PctType::Pct90 :
        return m_vector[std::min(static_cast<size_t>(std::floor(m_vector.size() * 0.9)), m_vector.size() - 1)];
    case PctType::Pct95 :
        return m_vector[std::min(static_cast<size_t>(std::floor(m_vector.size() * 0.95)), m_vector.size() - 1)];
    default:
        return -1;
    }

}

const char *Pct::name() const
{
    switch (m_type)
    {
    case PctType::Pct90 :
        return "pct90";
    case PctType::Pct95 :
        return "pct95";
    default:
        return "error";
    }
}
