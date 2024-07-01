#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// DATA MANAGER CLASS - DERIVED CLASS
class DataManager : public DataVersion
{
private:
    vector<DataRecord> samples;
    void load_samples(const string &version, const string &filename);

public:
    DataManager() : DataVersion() {}
    DataManager(const string &version, const string &filename);
    void operator()(const string &version, const string &filename);
    int countTripleMeanSamples() const;
    DataRecord getBestSample() const;
    void print_info() const override;
};

void DataManager::load_samples(const string &version, const string &filename)
{
    // If the file is open. Loop through each line.
    ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        // Loop through each line in the file and copy the contents to line.
        string line;
        while (getline(inputFile, line))
        {
            // Try to process the line. If there are negative numbers in the line, throw an error.
            try
            {
                vector<double> input_data;
                double number;
                istringstream iss(line);
                while (iss >> number)
                {
                    if (number < 0)
                    {
                        throw DataException("Error: Negative values are not allowed in the data sample.");
                    }
                    // Push each number to the input data.
                    input_data.push_back(number);
                }
                // Create a new Data Record with the input data. Push the data record to the samples vector.
                this->samples.push_back(DataRecord(version, input_data));
            }
            // If a negative number is found, print the message and continue.
            catch (const DataException &msg)
            {
                cerr << msg.what() << endl;
            }
        }
        // Close the file.
        inputFile.close();
    }
    // If the file can't be opened, throw an error.
    else
    {
        throw DataException("Cannot open file: " + filename);
    }
}

DataManager::DataManager(const string &version, const string &filename) : DataVersion(version)
{
    // Standard constructor function.
    try
    {
        load_samples(version, filename);
    }
    // If the functions above return an error throw, wrap the message and throw it back to the main function.
    catch (const DataException &msg)
    {
        throw DataException(msg);
    }
}

// Overloaded constructor function to initialise an empty object.
void DataManager::operator()(const string &version, const string &filename)
{
    try
    {
        set_version(version);
        load_samples(version, filename);
    }
    // If the functions above return an error throw, wrap the message and throw it back to the main function.
    catch (const DataException &msg)
    {
        throw DataException(msg);
    }
}

int DataManager::countTripleMeanSamples() const
{
    // Loop through all of the sample vectors. For each record, count if the max value is more than 3 * the mean value.
    return count_if(samples.begin(), samples.end(), [this](const DataRecord &record)
                    { return record.getStatisticsA() > 3 * record.getStatisticsB(); });
}

DataRecord DataManager::getBestSample() const
{
    // Set the max at 0, as there can't be any negative numbers. Create a pointer to point to the matching record.
    double max_mean = 0.0;
    const DataRecord *best_record = nullptr;

    // Loop through all the records in the sample vector.
    for (const auto &record : samples)
    {
        // Calculate the mean for each record.
        double mean = record.getStatisticsB();

        // Update the best record if the mean is highest.
        if (mean > max_mean)
        {
            max_mean = mean;
            best_record = &record;
        }
    }
    return *best_record;
}

void DataManager::print_info() const
{
    // Print the info according to the requirements.
    cout << "Count of TripleMeanSamples: " << countTripleMeanSamples() << endl;
    DataRecord best_record = this->getBestSample();
    best_record.print_info();
}