#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Used for testing. If the input file contains floats, switch to 'float' and '0.0'
#define read_type int
#define initialise_type 0

// Function prototypes.
template <class T>
void calculate_stats(vector<T> &v_list);
int open_file(ifstream &input_file, string &filename);
void process_file(ifstream &input_file, vector<read_type> &data);

int main()
{
    // Setup the variables to open the file and confirm correct usage.
    ifstream input_file;
    string filename;
    vector<read_type> numbers;
    int flag = 0;

    // Loop until a file is opened correctly or exit requested.
    while (flag == 0)
    {
        cout << "Enter the filename ('EXIT' TO QUIT): ";
        cin >> filename;
        if (filename == "EXIT" || filename == "exit")
        {
            return 0;
        }
        else
        {
            flag = open_file(input_file, filename);
        }
    }
    process_file(input_file, numbers);
    calculate_stats(numbers);
    input_file.close();
    return 0;
}

template <class T>
void calculate_stats(vector<T> &v_list)
{
    // Set the min and max as the first element and initialise the total and count.
    auto min = v_list[0];
    auto max = v_list[0];
    auto total = initialise_type;
    auto count = initialise_type;

    // Iterate through the vector using a range-based loop to find the min, max, total and count values.
    for (auto val : v_list) {
        if (val < min)
        {
            min = val;
        }
        if (val > max)
        {
            max = val;
        }
        count++;
        total += val;        
    }

    // Calculate the average as a double and print the results.
    auto avg = (double)total / count;
    cout << "MAX: " << max << endl;
    cout << "MIN: " << min << endl;
    cout << "AVG: " << avg << endl;
}

int open_file(ifstream &input_file, string &filename) 
{
    // Open the file. If error occurs return 0, else 1.
    input_file.open(filename);
    if(!input_file)
    {
        cout << "Error: <USAGE> filename.extension (input.txt)\n";
        return 0;        
    }
    else
    {
        return 1;
    }
}

void process_file(ifstream &input_file, vector<read_type> &data)
{
    // Read the data from the file and add it to the vector.
    read_type number;
    while (input_file >> number)
    {
        data.push_back(number);
    }
}
