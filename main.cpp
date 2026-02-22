/* PROJECT TITLE: CSV QUERY ENGINE
   REG/NO:        FEE3/2881/2025
   STUDENT NAME:  KIMANZI ANTONY MALUKI
   UNIT:          COMPUTER SCIENCE FEE3131
   COURSE:        ELECTRICAL ENGINEERING
   YEAR:          ONE
   =======================================



/This C++ Progam allows users to load CSV files
 and interact with the data through;
      *Viewing
      *filtering
      *sorting
      *column selection
      *exporting query results for analysis and reporting.*/

/*C++ to run backend processing and CSV manipulation*/
/*Browser interface for user interaction*/


#include <iostream>     // Handle console input and output operations
#include <fstream>      // Enable reading and writing of external files
#include <sstream>      // Allow breaking CSV rows into individual values
#include <vector>       // Store table rows dynamically
#include <string>       // Handle text data
#include <algorithm>   // Provide sorting functionality
#include <cstdlib>     // Allow execution of system commands

using namespace std;

int main()
{
    // Automatically launch the web interface when the program starts
    // Connect the console engine with the browser interface
    system("start \"\" \"C:\\CSV QUERY ENGINE FEE328812025\\CSV Q Engine\\web\\index.html\"");

    // Display program banner for user clarity
    cout << "==============================" << endl;
    cout << "      CSV QUERY ENGINE        " << endl;
    cout << "==============================" << endl << endl;

    // Location of the CSV data file used by the system
    string filePath = "data/students.csv";

    // Store the entire CSV table (all rows and columns)
    vector<vector<string>> table;

    // Store currently processed results (filtered or sorted data)
    vector<vector<string>> currentView;

    // Store column titles extracted from the first row of CSV
    vector<string> headers;

    // Open the CSV file for reading by the user
    ifstream file(filePath);

    // Ensure file exists and opens correctly
    if (!file.is_open())
    {
        cout << "ERROR: Could not open students.csv file." << endl;

        // Stop program if file cannot be accessed
        return 0;
    }

    // Detect header row of the CSV file
    string line;
    bool isFirstRow = true;

    // Read each line of the CSV file
    while (getline(file, line))
    {
        // Hold values for one CSV row
        vector<string> row;

        // Convert each line into stream for splitting
        stringstream ss(line);
        string cell;

        // Break line into values using comma as separator
        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        // Treat First row Column headings
        if (isFirstRow)
        {
            headers = row;
            isFirstRow = false;
        }
        // Treat the remaining as actual dataset values
        else
        {
            table.push_back(row);
        }
    }

    // Close file once reading is complete
    file.close();

    // Initialize working dataset to full table
    currentView = table;

    cout << "SUCCESS: CSV File loaded." << endl;



    // ===================== USER INTERACTION LOOP =====================
    // Keep program running until user chooses to exit
    while (true)
    {
        // Display clearly the available operations
        cout << endl;
        cout << "==============================" << endl;
        cout << "            MAIN MENU        " << endl;
        cout << "==============================" << endl;
        cout << "1. View all data" << endl;
        cout << "2. Filter data (any column)" << endl;
        cout << "3. Sort data (any column)" << endl;
        cout << "4. Select one column" << endl;
        cout << "5. Export query results to new CSV" << endl;
        cout << "E. Exit program" << endl;
        cout << "Enter your choice: ";

        string choice;
        cin >> choice;

        // Terminate the application safely
        if (choice == "E" || choice == "e")
        {
            cout << "Program exited by user." << endl;
            break;
        }



        // ===== OPTION 1: VIEW COMPLETE CSV FILE ===========
        else if (choice == "1")
        {
            // Display clearly column headings of the CSV file
            for (string h : headers)
                cout << "[" << h << "] ";
            cout << endl;

            // Display clearly every row and value in the file
            for (auto row : table)
            {
                for (string v : row)
                    cout << "[" << v << "] ";
                cout << endl;
            }

            // Reset current working view to full data
            currentView = table;
        }

        // ===== OPTION 2: FILTER BY DATA ( ANY COLUMN) BY NUMERIC VALUES =====
        else if (choice == "2")
        {
            vector<vector<string>> filteredResult;

            // Display columns available for filtering
            cout << endl << "Choose a column to filter by:" << endl;
            for (int i = 0; i < headers.size(); i++)
                cout << i << ". " << headers[i] << endl;

            int col;
            cout << "Enter column number: ";
            cin >> col;

            int minVal;
            cout << "Enter minimum numeric value: ";
            cin >> minVal;

            // Display reduced header for filtered output
            cout << endl;
            cout << "[" << headers[0] << "] [" << headers[col] << "]" << endl;

            // Loop through all data rows and apply condition
            for (auto r : table)
            {
                try
                {
                    // Convert string value to integer for comparison
                    // Skip invalid numeric values safely
                    if (stoi(r[col]) >= minVal)
                    {
                        filteredResult.push_back(r);
                        cout << "[" << r[0] << "] [" << r[col] << "]" << endl;
                    }
                }
                catch (...)
                {

                }
            }

            // Save filtered results as new working dataset
            currentView = filteredResult;

            cout << endl << "Current view updated (filtered data)." << endl;
        }



        // ===== OPTION 3: SORT DATA =====
        else if (choice == "3")
        {
            // Prompt user to choose preferred sorting direction
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cout << "Choose order: ";
            int order;
            cin >> order;

            // Display all available columns for sorting
            cout << endl << "Choose a column to sort by:" << endl;
            for (int i = 0; i < headers.size(); i++)
                cout << i << ". " << headers[i] << endl;

            int col;
            cout << "Enter column number: ";
            cin >> col;

            // Create a temporary copy of the working dataset
            // **avoid altering original data directly
            vector<vector<string>> temp = currentView;

            // Sort using custom comparison function
            // Attempt numeric comparison first, then text comparison
            sort(temp.begin(), temp.end(), [&](auto a, auto b)
            {
                try
                {
                    // Numerically sort the numbers in the chosen order
                    if (order == 1)
                        return stoi(a[col]) < stoi(b[col]);
                    else
                        return stoi(a[col]) > stoi(b[col]);
                }
                catch (...)
                {
                    // Sort alphabetically if conversion fails
                    return a[col] < b[col];
                }
            });



            // Store sorted result as new working dataset
            currentView = temp;

            // Display clearly the sorted output (name + selected column)
            cout << endl;
            cout << "[" << headers[0] << "] [" << headers[col] << "]" << endl;
            for (auto r : currentView)
                cout << "[" << r[0] << "] [" << r[col] << "]" << endl;

            cout << endl << "Current view updated (sorted data)." << endl;
        }




        // ======= OPTION 4: SELECT ONE COLUMN ===========
        else if (choice == "4")
        {
            // Display complete list of available columns
            cout << "Select column:" << endl;
            for (int i = 0; i < headers.size(); i++)
                cout << i << ". " << headers[i] << endl;

            int col;
            cin >> col;

            // Print only the selected column values
            cout << endl << headers[col] << endl;
            for (auto r : currentView)
                cout << r[col] << endl;
        }

        // ===== OPTION 5: EXPORT QUERY RESULTS TO NEW CSV FILE =====
        else if (choice == "5")
        {
            // Display export options to the user
            cout << endl;
            cout << "------ EXPORT MENU ------" << endl;
            cout << "1. Export ALL original data" << endl;
            cout << "2. Export CURRENT working data" << endl;
            cout << "Choose option: ";

            int ex;
            cin >> ex;

            // Create new CSV file for output
            ofstream outFile("exported_students.csv");

            // Check if file creation succeeded
            if (!outFile.is_open())
            {
                cout << "ERROR: Could not create export file." << endl;
            }
            else
            {
                // Print column headers first
                for (int i = 0; i < headers.size(); i++)
                {
                    outFile << headers[i];
                    if (i < headers.size() - 1) outFile << ",";
                }
                outFile << endl;

                // Determine which dataset to export
                // Option 1: Export complete CSV file data
                // Option 2: Export filtered/sorted results
                vector<vector<string>> &source = (ex == 1) ? table : currentView;

                // Write each row into the CSV file
                for (auto row : source)
                {
                    for (int i = 0; i < row.size(); i++)
                    {
                        outFile << row[i];
                        if (i < row.size() - 1) outFile << ",";
                    }
                    outFile << endl;
                }

                // Close created file after writing
                outFile.close();

                cout << "SUCCESS: exported_students.csv created." << endl;
            }
        }




        // ========== HANDLING INVALID INPUTS FROM THE USER =========
        else
        {

            // Prevent crashing and guide user back to menu
            cout << "Invalid option. Try again." << endl;
        }
    }

    // End program execution
    return 0;
}
