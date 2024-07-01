#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


// Vector class.
class NewVector
{
private:
    vector<float> data;

public:
    // Default constructor function for random data generation.
    NewVector(int num_elems = 10)
    {
        data.resize(num_elems);
        generate(data.begin(), data.end(), [&]() { return static_cast<float>(1 + rand() % 99) / 10.0; });
    }
    // Secondary constructor function for predetermined data input.
    NewVector(vector<float> user_input)
    {
        data.insert(data.end(), user_input.begin(), user_input.end());
    }
    size_t get_size() const { return data.size(); }
    vector<float> get_data() const { return data; }
    // Overloaded functions.
    NewVector operator*(const NewVector &v2) const;
    NewVector operator/(const NewVector &v2) const;
    friend ostream &operator<<(ostream &out, const NewVector &v1);
};

// Multiplication functor.
class Multiplication
{
public:
    NewVector operator()(const NewVector &v1, const NewVector &v2)
    {
        // Get the data for each vector object.
        vector<float> data1 = v1.get_data();
        vector<float> data2 = v2.get_data();

        // Perform element-wise multiplication and store the result in a new vector.
        vector<float> result_data;
        for (size_t i = 0; i < v1.get_size(); i++)
        {
            result_data.push_back(data1[i] * data2[i]);
        }

        // Return the new vector with the result data.
        return NewVector(result_data);
    }
};

// Division functor.
class Division
{
public:
    NewVector operator()(const NewVector &v1, const NewVector &v2)
    {
        // Get the data for each vector object.
        vector<float> data1 = v1.get_data();
        vector<float> data2 = v2.get_data();

        // Perform element-wise division and store the result in a new vector.
        vector<float> result_data;
        for (size_t i = 0; i < v1.get_size(); i++)
        {
            if (data1[i] == 0 || data2[i] == 0)
            {
                throw VectorOperationException("Division by zero encountered.");
            }
            else
            {
                result_data.push_back(data1[i] / data2[i]);
            }
        }

        // Return the new vector with the result data.
        return NewVector(result_data);
    }
};


// New vector member function definitions.
NewVector NewVector::operator*(const NewVector &v2) const
{
    // Check if the vectors have the same size and return an error if not.
    if (get_size() != v2.get_size())
    {
        throw VectorOperationException("Vectors must be of the same size.");
    }

    // Call the multiplication functor with the two NewVector objects. Catch any errors.
    try
    {
        NewVector m_vector = Multiplication()(*this, v2);
        cout << "Result of vec1 * vec2:" << endl;
        cout << m_vector << endl;
        return m_vector;
    }
    catch (const VectorOperationException &msg)
    {
        cerr << "Vector operation error: " << msg.what() << endl;
        return NewVector();
    }
}

NewVector NewVector::operator/(const NewVector &v2) const
{
    // Call the division functor with the two NewVector objects. Catch any errors.
    try
    {
        NewVector d_vector = Division()(*this, v2);
        cout << "Result of vec1 / vec2:" << endl;
        cout << d_vector << endl;
        return d_vector;
    }
    catch (const VectorOperationException &msg)
    {
        cerr << "Vector operation error: " << msg.what() << endl;
        return NewVector();
    }
}

ostream &operator<<(ostream &out, const NewVector &v1)
{
    // Loop over the new vector and print the data elements.
    for (auto val : v1.data)
    {
        out << val << " ";
    }
    return out;
}







