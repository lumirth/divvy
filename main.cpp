/* program_4.cpp
    Divvy Bike Data Analysis program.
    Author: Lukas Unguraitis
    Date: 11/2/2021
    Class: CS 141, Fall 2021, UIC
    System: Xcode 13.1 MacOS 11.4
    Menu Option 5 Extra Credit URL: https://www.google.com/maps/place/41%C2%B053'27.8%22N+87%C2%B039'19.6%22W/@41.891067,-87.6559932,19z/data=!3m1!4b1!4m6!3m5!1s0x0:0x0!7e2!8m2!3d41.8910658!4d-87.6554465
    Coordinates for Home I would like to live in:  41.891066, -87.655446
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <iomanip>
using namespace std;

long double toRadians(const long double degree);
long double distance(long double lat1, long double long1,
                     long double lat2, long double long2);
vector<vector<string>> parseCSV(string fileName);
void csvToVector(vector<vector<string>> &csv, string fileName);
void cleanData(vector<vector<string>> &csv);
double getTotalMiles(vector<vector<string>> csv);
double getAvgTrip(vector<vector<string>> csv);
double getMemberPercent(vector<vector<string>> csv);
int numDigits(int x);
int maxValue(vector<int> vect);
void printDivvyDataRow(int rowNumber, int rowDigits, vector<int> columnOne, vector<int> columnTwo);
void printSpaces(int spaces);
void printDivvyChartRow(vector<int> valuesVect, int largestRides, int row, string symbol);


int main(){
    int menuChoice;             // used for all menus throughout program
    int runCount = 0;           // used for number of times beginning message displayed
    bool dataRead = false;      // bool for if data has been read into vector
    vector<vector<string>> csv; // 2d vector for entire program

    while(true) {
        if (runCount++ == 0) { // let user know they need to read data first
            cout << "Analyze Divvy bike ride information using September trip data." << endl <<
                    "First select option 1 to read and clean the data."              << endl;
        }
        
        cout << "Select a menu option:"                                         << endl <<
                "   1. Select datafile, display rides totals and clean data"    << endl <<
                "   2. Display overall trip information"                        << endl <<
                "   3. Display percentage of members vs. casual riders"         << endl <<
                "   4. Display weekday vs weekend usage"                        << endl <<
                "   5. Extra Credit: find closest station"                      << endl <<
                "   6. Exit"                                                    << endl;
        
        cout << "Your choice --> ";
        cin >> menuChoice;

        // if user hasnt read data, force them to.
        if (!dataRead && (menuChoice != 1)) {
            cout << "  First read in data by selecting menu option 1" << endl;
            continue;
        }
        
        switch(menuChoice) { // menu
            case 1: { // Select datafile, display rides totals and clean data
                cout << "        Select datafile:" << endl <<
                        "           1. Small subset of data with 14 rides to help create your program" << endl <<
                        "           2. Week day vs weekend rides" << endl <<
                        "           3. All September 2021 data (not tested in Zybooks)" << endl;
                
                cout << "       Your selection--> ";
                cin >> menuChoice; cout << endl;
                
                // choose different datafiles
                switch (menuChoice) {
                    case 1:
                        csvToVector(csv, "divvyridesampledata.csv");
                        csv.erase(csv.begin()); // erase first line, it's unneeded
                        cout << "        Total # of trips found in datafile:  " << csv.size() << endl;
                        cleanData(csv);
                        cout << "        Total # of trips in clean data:  " << csv.size() << endl;
                        break;
                    case 2:
                        csvToVector(csv, "weekdayweekend.csv");
                        csv.erase(csv.begin()); // erase first line, it's unneeded
                        cout << "        Total # of trips found in datafile:  " << csv.size() << endl;
                        cleanData(csv);
                        cout << "        Total # of trips in clean data:  " << csv.size() << endl;
                        break;
                    case 3:
                        csvToVector(csv, "all_divvy_rides_september.csv");
                        csv.erase(csv.begin()); // erase first line, it's unneeded
                        cout << "        Total # of trips found in datafile:  " << csv.size() << endl;
                        cleanData(csv);
                        cout << "        Total # of trips in clean data:  " << csv.size() << endl;
                        break;
                } // end switch(menuChoice)
                dataRead = true;
                continue;
                
            } // end case 1
            case 2: { // Display overall trip information
                double totalMiles = getTotalMiles(csv);
                double avgTripLength = getAvgTrip(csv);
                cout << " Total # of miles traveled: " << setprecision(0) << fixed << totalMiles << "\n"
                    << " Average length of trips in miles: " << setprecision(1) << fixed << avgTripLength
                    << "\n";
                
                cout << endl << "Longest trip information below:" << endl;
                cout <<         "-------------------------------" << endl;
                
                int longestIndex = 0;
                double longestDistance = 0;
                for (int i = 0; i < csv.size(); i++) {
                    double longestSoFar = distance(stod(csv[longestIndex][6]), stod(csv[longestIndex][7]),
                                                   stod(csv[longestIndex][8]), stod(csv[longestIndex][9]));
                    double dist = distance(stod(csv[i][6]), stod(csv[i][7]),
                                           stod(csv[i][8]), stod(csv[i][9]));
                    if(dist > longestSoFar) {
                        longestIndex = i;
                        longestDistance = dist;
                    }
                }
                
                cout << "Trip ID: " << csv[longestIndex][0] << endl;
                cout << "Trip start location: " << csv[longestIndex][4] << endl;
                cout << "Trip end location: " << csv[longestIndex][5] << endl;
                cout << "Trip distance in miles: " << longestDistance << endl;

                continue;
                
            } // end case 2
                
            case 3: { // Display percentage of members vs. casual riders
                double memberPercent = getMemberPercent(csv);
                cout << "   Casual Rider Percentage: " << fixed << setprecision(1) << 100 - memberPercent << "%" << endl <<
                        "   Member Rider Percentage: " << fixed << setprecision(1) << memberPercent << "%" << endl;
                continue;
                
            } // end case 3
            case 4: { // Display weekday vs weekend usage
                cout << "   Select type of display: " << endl <<
                        "      1. Counts of rides per hour in the day" << endl <<
                        "      2. Proportional 50 column graph with @ for weekday and + for weekend" << endl;
                cout << "   Your selection--> "; cin >> menuChoice;
                
                vector<int> numRidesWeek(24, 0); // number of rides in each hour on 9/1
                vector<int> numRidesEnd(24, 0);  // number of rides in each hour on 9/4
                vector<int> allNumRides;         // number of rides in each hour on 9/1 and 9/4
                string dateTime;                 // variable used for storing date and time value of each row
                string hour;                     // variable used for storing particular hour being manipulated
                
                for(int i = 0; i < csv.size(); i++) {
                    dateTime = csv[i][2];
                    // find where hour is in string
                    string hour = dateTime.substr(dateTime.find("21") + 3, (dateTime.find(":") - dateTime.find("21") - 3));
                    // add it to corresponding vector (9/1 or 9/4)
                    if (dateTime.at(2) == '1') numRidesWeek[stoi(hour)] += 1;
                    else                       numRidesEnd[stoi(hour)] += 1;
                } // end for
                
                // create allNumRides (combine numRidesWeek and numRidesEnd)
                allNumRides = numRidesWeek;
                allNumRides.insert(allNumRides.end(), numRidesEnd.begin(), numRidesEnd.end());
                
                int LargestNumberOfRides = maxValue(allNumRides);

                // display data in different ways
                switch(menuChoice) {
                    case 1: // Counts of rides per hour in the day
                        cout << "LargestNumberOfRides is: " << LargestNumberOfRides << endl;
                        cout << "Rides per hour for weekday and weekend:";
                        for(int i = 0; i < 24; i++) {
                            if (i < 10) {
                                printDivvyDataRow(i, 1, numRidesWeek, numRidesEnd);
                            } else {
                                printDivvyDataRow(i, 2, numRidesWeek, numRidesEnd);
                            } // end else
                        } // end for
                        break;
                        
                    case 2: // 50 column chart.
                        for (int i = 0; i < 24; i++){
                            if (i < 10) cout << i << ":  "; else cout << i << ": ";
                            printDivvyChartRow(numRidesWeek, LargestNumberOfRides, i, "@"); cout << endl;
                            printSpaces(4);
                            printDivvyChartRow(numRidesEnd, LargestNumberOfRides, i, "+"); cout << endl;
                        } // end for
                } // end switch
                continue;
            } // end case 4
                
            case 5: { // Extra Credit: find closest station
                double latitude;
                double longitude;
                cout << "   Input latitude and longitude of the home: "; cin >> latitude; cin >> longitude;
                cout << "   You entered: " << fixed << setprecision(1) << latitude << " for latitude and " << fixed << setprecision(1) << longitude << " for longitude" << endl;
                cout << "Closest Divvy station is: ";
                
                int index = 0;
                double lastClosest = 0;
                for(int i = 0; i < csv.size(); i++) {
                    double currentDistance = distance(latitude, longitude, stod(csv[i][6]), stod(csv[i][7]));
                    if (currentDistance < lastClosest) {
                        lastClosest = currentDistance;
                        index = i;
                    } // end if (currentDistance < lastClosest)
                } // end for (int i = 0; i < csv.size(); i++)
               
                // output closest station
                cout << csv[index][4] << " at " << csv[index][6] << ", " << csv[index][7] << ", ";
                cout << fixed << setprecision(1) << lastClosest << " miles away." << endl;
            } // end case 5

            case 6: { // Exit
                break;
            } // end case 6
                
        } // end switch(menuChoice)
        break;
        
    } // end while(true)
    return 0;
    
} // end main

// converts csv file with name fileName into a 2d vector csv
void csvToVector(vector<vector<string>> &csv, string fileName) {
    ifstream inStream;                      // input stream for reading
    inStream.open(fileName);                // open file with specified name
    assert( inStream.fail() == false );     // check if file opened
    
    string newRow; // input row
    while(getline(inStream, newRow)) {                                           // while inStream is reading a row
        newRow.erase(remove(newRow.begin(), newRow.end(), '\r'), newRow.end());  // remove carriage return from string version of row
        vector<string> vectorRow;                                                // vector version of row
        while(newRow.size()){                    // while newRow has elements
            int index = newRow.find(",");        // index of first comma in newRow
            if(index != string::npos){           // if index is not greatest possible value
                vectorRow.push_back(newRow.substr(0,index));   // add first item to vector (from 0 to first comma)
                newRow = newRow.substr(index + 1);             // cut off first item of newRow, as it has already been added to vector.
                // if newRow is empty, we don't have to do anything and can just add the empty string to the vector
                if(newRow.size() == 0) vectorRow.push_back(newRow);
            } // end if index != string::npos
            else { vectorRow.push_back(newRow); newRow = ""; }
        } // end while(newRow.size()
        csv.push_back(vectorRow); // add new row to vector
    } // end while(inStream >> addMe)
    inStream.close();
} // end csvToVector

// removes any line missing a value in any column. domain of x is all cells in a particular row, H(x) = "has value", if ∃x(¬H(x)), delete the row
void cleanData(vector<vector<string>> &csv) {
    vector<vector<string>> clean;
    bool dirty = false;
    for (int row = 0; row < csv.size(); row++) {             // traverse row
        dirty = false;
        for (int col = 0; col < csv[row].size(); col++) {    // traverse columns
            if (csv[row][col].size() == 0) { dirty = true; } // if any item in row i is empty
        } // end for (int j = 0; j < csv[0].size(); j++)
        if(!dirty) { clean.push_back(csv[row]); }            // if not dirty, add row to clean CSV
    } // end for (int i = 0; i < csv.size(); i++)
    csv = clean;
} // end cleanData()

// get total amount of miles from divvy csv
double getTotalMiles(vector<vector<string>> csv) {
    double totalDistance = 0;
    for (int row = 0; row < csv.size(); row++) {
        double startLat = stod(csv[row][6]);
        double startLong = stod(csv[row][7]);
        double endLat = stod(csv[row][8]);
        double endLong = stod(csv[row][9]);
        totalDistance += distance(startLat, startLong, endLat, endLong);
    } return totalDistance;
} // end getTotalMiles()

// get average trip length from divvy csv
double getAvgTrip(vector<vector<string>> csv) {
    double totalMiles = getTotalMiles(csv);
    double numRides = csv.size();
    return totalMiles / numRides;
} // end getAvgTrip()

// get percentage of riders who are members from divvy csv
double getMemberPercent(vector<vector<string>> csv) {
    double memberCnt = 0; double casualCnt = 0;     // counts for member and casual riders
    double totalRiders = csv.size();                // total number of rides is number of elements in rides
    for (int row = 0; row < csv.size(); row++) {    // iteratae through CSV and check whether each row is a member or not
        if (csv[row][10] == "member") {
            memberCnt += 1;
        } else continue;
    } // end for
    return (memberCnt / totalRiders) * 100.0;
} // end getMemberPercent()

// get number of digits for an integer
int numDigits(int x){
    int length = 1;
    while (x /= 10) { // integer division
       length++;
    } return length;
} // end numDigits

// get largest value in an integer vector
int maxValue(vector<int> vect){
    int maxVal = vect.at(0);

    for(int i = 0; i < vect.size(); ++i) {
        if(maxVal < vect.at(i)){
            maxVal = vect.at(i);
        } // end if(maxVal < vect.at(i))
    } // end for(int i = 0; i < vect.size(); ++i)
    return maxVal;
} // end maxValue()

void printDivvyDataRow(int rowNumber, int rowDigits, vector<int> columnOne, vector<int> columnTwo) {
    int numSpaces;                                              // variable for number of spaces
    cout << rowNumber << ":";                                   // display current row number
    numSpaces = 9 - numDigits(columnOne.at(rowNumber));         // get number of spaces to be printed before data
    printSpaces(numSpaces);                                     // print spaces
    cout << columnOne[rowNumber];                               // print data value of column one
    numSpaces = 7 - numDigits(columnTwo.at(rowNumber));         // get number of spaces to be printed before data
    printSpaces(numSpaces);                                     // print spaces
    cout << columnTwo[rowNumber];                               // print data value of column two
    cout << endl;
}

void printDivvyChartRow(vector<int> valuesVect, int largestRides, int row, string symbol) {
    int hourVal = valuesVect.at(row);
    int numSymbols = (static_cast<double>(hourVal) / static_cast<double>(largestRides)) * 50;
    for (int i = 0; i < numSymbols; i++) { cout << symbol; }
} // end printDivvyChartRow

// function for printing a given number of spaces
void printSpaces(int spaces) { for (int i = 0; i < spaces; i++) { cout << " "; } }

// Utility functions getting distant between two map points
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/
// converting degrees to radians
long double toRadians(const long double degree) {
    // cmath library in C++ defines the constant M_PI as the value of pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
    long double lat2, long double long2) {
    // Convert the latitudes and longitudes from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
        cos(lat1) * cos(lat2) *
        pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in Kilometers, R = 6371 Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}

// :] hi
