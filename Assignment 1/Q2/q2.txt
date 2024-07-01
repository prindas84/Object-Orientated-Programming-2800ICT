#include <iostream>
#include <limits>
#include <vector>
using namespace std;

void fold_card(int M, int N, int K, const vector<vector<char>> &card);

int main()
{
    int M, N, K;
    int count = 1;

    while (count <= 4)
    {
        // Loop to get the first line of user input.
        while (true)
        {
            cout << "Input " << count << ":" << endl;
            cin >> M >> N >> K;
            // Validate according to the rules.
            if ((M >= 1 && M <= 1000) && ((N >= 2 && N <= 1000) && ((M * N) <= 1000)) && (K >= 1 && K <= N - 1))
            {
                break;
            }
            // If invalid, clear the buffer and loop again.
            else
            {
                cin.clear();                                         // Clear the error flag.
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input.
                cout << "Invalid input. " << endl;
            }
        }

        // Clear the previous input buffer.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Initialise the vector of vectors and copy in the string input to each row.
        vector<vector<char>> card(M, vector<char>(N));
        for (int i = 0; i < M; i++)
        {
            // Loop until a valid row input is recieved.
            while (true)
            {
                string line;
                getline(cin, line);
                if (line.length() != N)
                {
                    cout << "Error: Incorrect input. Each row must be " << N << " characters long." << endl;
                    // Check if there are characters left in the buffer and remove.
                    if (cin.rdbuf()->in_avail() > 1)
                    {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                else
                {
                    // Store each character into the corresponding element of the card vector.
                    bool valid = true;
                    for (int j = 0; j < N; j++)
                    {
                        // If the input contains invalid characters, reject and loop again. Else update the vector.
                        if (line[j] != '#' && tolower(line[j]) != 'o')
                        {
                            valid = false;
                            break;
                        }
                        card[i][j] = line[j];
                    }
                    // If the input is valid, break and move to the next row.
                    if (valid)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Error: Incorrect input. Characters must be '#' or 'o'." << endl;
                        if (cin.rdbuf()->in_avail() > 1)
                        // Check if there are characters left in the buffer and remove.
                        { 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                }
            }
        }
        cout << endl;

        cout << "Output " << count << ":" << endl;

        // Process the fold and print.
        fold_card(M, N, K, card);
        cout << endl;
        count++;
    }
}

void fold_card(int M, int N, int K, const vector<vector<char>> &card)
{
    // If the fold is in the middle of a card with even columns...
    if ((N % 2 == 0) && (N / 2 == K))
    {
        for (int row = 0; row < M; row++)
        {
            int x = 1;
            // Compare the elements in the first half of the list to their corresponding index in the second half.
            for (int col = 0; col < K; col++)
            {
                // If the elements are the same, print their value.
                if (card[row][col] == card[row][N - x])
                {
                    cout << card[row][col];
                }
                // Else, print closed because they do not match and can't be open.
                else
                {
                    cout << '#';
                }
                x++;
            }
            cout << endl;
        }
    }
    // If there are overhanging columns from the original left...
    else if (K > (static_cast<float>(N) / 2))
    {
        int start = K - (N % K);
        for (int row = 0; row < M; row++)
        {
            // Print the overhanging elements from the left.
            for (int col = 0; col < start; col++)
            {
                cout << card[row][col];
            }
            int x = 1;
            // For the remaining elements...
            // Compare the elements in the first half of the list to their corresponding index in the second half.
            for (int col = start; col < start + ((N - start) / 2); col++)
            {
                // If the elements are the same, print their value.
                if (card[row][col] == card[row][N - x])
                {
                    cout << card[row][col];
                }
                // Else, print closed because they do not match and can't be open.
                else
                {
                    cout << '#';
                }
                x++;
            }
            cout << endl;
        }
    }
    // If there are overhanging columns from the original right...
    else
    {
        int end = N - (K * 2);
        for (int row = 0; row < M; row++)
        {
            // Print the overhanging elements from the left.
            for (int col = N - 1; col >= N - end; col--)
            {
                cout << card[row][col];
            }
            int x = end + 1;
            // For the remaining elements...
            // Compare the elements in the first half of the list to their corresponding index in the second half.
            for (int col = 0; col < (N - end) / 2; col++)
            {
                // If the elements are the same, print their value.
                if (card[row][col] == card[row][N - x])
                {
                    cout << card[row][col];
                }
                // Else, print closed because they do not match and can't be open.
                else
                {
                    cout << '#';
                }
                x++;
            }
            cout << endl;
        }
    }
}
