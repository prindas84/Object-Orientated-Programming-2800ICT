#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <exception>
#include <fstream>
#include <sstream>
#include "exception.cpp"
#include "data_version.cpp"
#include "data_record.cpp"
#include "data_manager.cpp"
using namespace std;

//=================================================
// MUST NOT CHANGE ANYTHING IN THE MAIN FUNCTION
//=================================================
int main()
{
    DataManager manager;
    try
    {
        manager("v1.5.0", "wrong_input.txt");
    }
    catch (const exception &e)
    {
        cout << e.what() << endl
             << endl;
        manager("v1.5.0", "input_datarecords.txt");
        manager.print_info();
    }
    return 0;
}