#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// DATA RECORD CLASS - DERIVED CLASS
class DataRecord : public DataVersion
{
private:
    vector<double> dataVector;

public:
    DataRecord(const string &version, const vector<double> &dataValues) : DataVersion(version), dataVector(dataValues) {}
    double getStatisticsA() const;
    double getStatisticsB() const;
    void print_info() const override;
};

// Get the max value of the data vector.
double DataRecord::getStatisticsA() const
{
    return *max_element(dataVector.begin(), dataVector.end());
}

// Get the mean value of the data vector.
double DataRecord::getStatisticsB() const
{
    // Calculate the sum of all elements.
    double sum = 0.0;
    for (const auto &value : dataVector)
    {
        sum += value;
    }

    // Calculate the mean by dividing the sum by the number of elements.
    return sum / dataVector.size();
}

// Call the base class to print the version, then the A / B methods to print max and mean.
void DataRecord::print_info() const
{
    cout << "Details of the sample with the max Mean:" << endl;
    cout << *this << " | Max Value: " << getStatisticsA() << " | Mean Value: " << getStatisticsB();
}