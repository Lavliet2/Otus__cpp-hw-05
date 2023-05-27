#include <iostream>
#include <vector>

#include "statistics.h"

using namespace std;

int main()
{
    double val;
    vector<double> numVector;
    while ( cin >> val ) {
        numVector.push_back(val);
    }
    //Блок для быстрого теста
    //    numVector.clear();
    //    numVector.push_back(0);
    //    numVector.push_back(1);
    //    numVector.push_back(2);
    //    numVector.push_back(3);
    //    numVector.push_back(4);
    //    numVector.push_back(5);
    //    numVector.push_back(6);
    //    numVector.push_back(7);
    //    numVector.push_back(8);
    //    numVector.push_back(9);
    //    numVector.push_back(10);
    const size_t statistics_count = 6;
    IStatistics *statistics[statistics_count];

    statistics[Type::MinType] = new Min {};
    statistics[Type::MaxType] = new Max {};
    statistics[Type::MeanType]= new Mean{};



    //- min – минимальное значение из последовательности
    //- max – максимальное значение из последовательности
    //- mean – арифметическое среднее, посчитанное на основе всех элементов последовательности


    for (double num : numVector) {
        for (size_t i = 0; i < statistics_count; ++i) {
            if ( i != Type::StdType && i != Type::PctType && i != Type::PctType+1) {
                statistics[i]->update(num);
            }
        }
    }

    //- std - среднеквадратическое отклонение
    statistics[Type::StdType] = new Std(statistics[Type::MeanType]->eval());
    for (size_t i = 0; i < numVector.size(); i++) {
        statistics[Type::StdType]->update(i);
    }

    //- [опционально] pct90 - 90-й процентиль
    //- [опционально] pct95 - 95-й процентиль
    statistics[Type::PctType] = new Pct(numVector, Pct::Pct90);
    statistics[Type::PctType+1] = new Pct(numVector, Pct::Pct95);


    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }

    // Print results if any
    for (size_t i = 0; i < statistics_count; ++i) {
        std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
    }
    //       std::cout << statistics[2]->name() << " = " << statistics[2]->eval() << "size" << statistics[2].getSize() << std::endl;
    // Clear memory - delete all objects created by new
    for (size_t i = 0; i < statistics_count; ++i) {
        delete statistics[i];
    }

    return 0;
}
