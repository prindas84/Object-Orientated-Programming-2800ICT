#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

template <class T>
double calculate_average(vector<T> &v_list);
bool count_greater(int &n);
void update_scores(int &n);
void read_numbers(vector<int> &numbers, string file_name = "input.txt");

int main()
{
    // Create a vector to store the integers read from the file
    std::vector<int> scores;
    read_numbers(scores, "week3_input.txt");

    // Task 1.
    int count = count_if(scores.begin(), scores.end(), count_greater);
    cout << "Task1: Number of scores greater than 85: " << count << endl;

    // Task 2.
    sort(scores.begin(), scores.end());
    bool found = binary_search(scores.begin(), scores.end(), -1);
    if (found)
    {
        cout << "Task2: Score -1 exists" << endl;
        // Task 3.
        auto new_end = remove(scores.begin(), scores.end(), -1);
        scores.erase(new_end, scores.end());
        double average = calculate_average(scores);
        cout << "Task3: Average scores after removing -1: " << average << endl;
    }
    else 
    {
        cout << "Task2: Score -1 does not exist" << endl;
    }

    // Task 4.
    for_each(scores.begin(), scores.end(), update_scores);
    double updated_average = calculate_average(scores);
    cout << "Task4: Average of updated scores: " << updated_average << endl;

    return 0;
}

template <class T>
double calculate_average(vector<T> &v_list)
{
    int sum = accumulate(v_list.begin(), v_list.end(), 0);
    return double(sum) / v_list.size();
}

bool count_greater(int &n) 
{
    return n > 85;
}

void update_scores(int &n)
{
    if (n >= 85)
    {
        n = 7;
    }
    else if (n >= 75)
    {
        n = 6;
    }
    else if (n >= 65)
    {
        n = 5;
    }
    else if (n >= 50)
    {
        n = 4;
    }
    else
    {
        n = 3;
    }
}

void read_numbers(vector<int> &numbers, string file_name)
{
    std::ifstream inputFile(file_name);
    if (!inputFile)
    {
        std::cerr << "Error: Could not open the file." << std::endl;
    }
    int num;
    while (inputFile >> num)
    {
        numbers.push_back(num);
    }
    inputFile.close();

    numbers.shrink_to_fit();
}

