#pragma one

//#include <iostream>
#include <vector>

enum Type
{
    MinType,
    MaxType,
    MeanType,
    StdType,
    PctType

};

///############################################################
/// @class Min
///############################################################
class IStatistics {
public:
	virtual ~IStatistics() {}

    virtual void update(double next)  = 0;
    virtual double eval() const       = 0;
	virtual const char * name() const = 0;
};

///############################################################
/// @class Min
///############################################################
class Min : public IStatistics {
public:
    Min();

    void   update(double next) override;
    double eval() const        override;
    const char * name() const  override;

private:
    double m_min;
};

///############################################################
/// @class Max
///############################################################
class Max : public IStatistics {
public:
    Max();

    void   update(double next) override;
    double eval() const        override;
    const char * name() const  override;

private:
    double m_max;
};

///############################################################
/// @class mean
///############################################################
class Mean : public IStatistics {
public:
    Mean();

    void   update(double next) override;
    double eval() const        override;
    const char * name() const  override;

private:
    double m_mean;
    std::size_t m_size;
};

///############################################################
/// @class Std
///############################################################
class Std : public IStatistics {
public:
    Std(double mean);

    void   update(double next) override;
    double eval() const        override;
    const char * name() const  override;

private:
    double m_std;
    std::size_t m_size;
    double mean;
};

///############################################################
/// @class Pct
///############################################################
class Pct : public IStatistics {
public:
    enum PctType
    {
        Pct90,
        Pct95
    };

    Pct(std::vector<double> vector, PctType type);

    void   update(double next) override;
    double eval() const        override;
    const char * name() const  override;

private:
    std::vector<double> m_vector;
    PctType m_type;

};
