#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

/*  NOTES FOR TA
 *  Paired programming with Hunter Gruwell & Anastasia Thomas
 *  Section: 002
 *
 *  CONTRIBUTIONS:
 *  Anastasia Thomas: parts 1-3
 *  Hunter Gruwell: parts 4-6
 */


using namespace std;

const int NUM_ROWS = 10;
const int NUM_COLUMNS = 10;
const int ARRAY_WIDTH = 9;
const int ARRAY_PRECISION = 3;
const double ARRAY_CHANGE = 0.1;

void FindSteadyState(double oldArray[NUM_ROWS][NUM_COLUMNS]);
void OutFile(double newArray[NUM_ROWS][NUM_COLUMNS]);
void OneIteration(double oldArray[NUM_ROWS][NUM_COLUMNS]);

int main() {
    double myArray[NUM_ROWS][NUM_COLUMNS];
    double newArray[NUM_ROWS][NUM_COLUMNS];
    double inputArray[NUM_ROWS][NUM_COLUMNS];

    cout << "Hotplate simulator" << endl;
    cout << endl;

    /********** PART 1: Initialize and Print 2D Array **********/
    cout << "Printing the initial plate values..." << endl;
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            cout << fixed << setw(ARRAY_WIDTH) << setprecision(ARRAY_PRECISION);
            myArray[j][i] = 0.0;
            if (j == NUM_ROWS - 1) {
                cout << myArray[j][i];
            }
            else if (((i == 0) || (i == NUM_COLUMNS - 1)) && ((j == 0) && (j != NUM_ROWS - 1))) {
                cout << myArray[j][i] << ",";
            }
            else if (((j > 0) || (j != NUM_ROWS - 1)) && ((i == 0) || (i == NUM_COLUMNS - 1))) {
                myArray[j][i] = 100.0;
                cout << myArray[j][i] << ",";
            }
            else if (((j != 0) && (j < NUM_ROWS - 1)) && (i != NUM_COLUMNS - 1)) {
                myArray[j][i] = 0.0;
                cout << myArray[j][i] << ",";
            }
            else {
                cout << myArray[j][i] << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
    /********** END OF PART 1 **********/

    /********** PART 2: Update Elements Once **********/
    cout << "Printing plate after one iteration... " << endl;
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            cout << fixed << setw(ARRAY_WIDTH) << setprecision(ARRAY_PRECISION);
            newArray[j][i] = 0.0;
            if (j == NUM_ROWS - 1) {
                cout << newArray[j][i] << " ";
            }
            else if (((i == 0) || (i == NUM_COLUMNS - 1)) && ((j == 0) && (j != NUM_ROWS - 1))) {
                cout << newArray[j][i] << ", ";
            }
            else if (((j > 0) || (j != NUM_ROWS - 1)) && ((i == 0) || (i == NUM_COLUMNS - 1))) {
                newArray[j][i] = 100.0;
                cout << newArray[j][i] << ", ";
            }
            else if (((j != 0) && (j < NUM_ROWS - 1)) && (i != NUM_COLUMNS - 1)) {
                // FIXME: Double check if this equation is correct
                newArray[j][i] = (myArray[j-1][i] + myArray[j][i-1] + myArray[j+1][i] + myArray[j][i+1]) / 4;
                cout << newArray[j][i] << ", ";
            }
            else {
                cout << newArray[j][i] << ", ";
            }
        }
        cout << endl;
    }
    cout << endl;
    /********** END OF PART 2 **********/

    /********** PART 3: Repeat Update until Steady State is Achieved **********/
    cout << "Printing final plate... " << endl;
    // This is the stead state
    FindSteadyState(newArray);
    cout << endl;
    /********** END OF PART 3 **********/

    /********** PART 4: Write Data to a File **********/
    cout << "Writing final plate to \"Hotplate.csv\"... " << endl;
//this is a function that copied the FindSteadyState function but writing to Hotplate.csv
    OutFile(newArray);
    cout << endl;

    /********** END OF PART 4 **********/

    /********** PART 5: Input Plate **********/
    cout << "Printing input plate after 3 updates... " << endl;

    ifstream inFile("Inputplate.txt");
    if (!inFile.is_open()) {
        cerr << "File not open.";
        exit(1);
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLUMNS; j++) {
            inFile >> inputArray[j][i];
        }
    }

    inFile.close();


    OneIteration(inputArray);

    cout << endl;
    /********** END OF PART 5 **********/

    /********** PART 6: Use Excel to Graph the Results **********/
    /********** END OF PART 6 **********/

    return 0;
}

void FindSteadyState(double oldArray[NUM_ROWS][NUM_COLUMNS]) {
    double newArray[NUM_ROWS][NUM_COLUMNS];

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            newArray[i][j] = 0;
        }
    }
    double sumValue = 0;
    double maxValue = 100.0;

    while (maxValue >= ARRAY_CHANGE) {
        maxValue = 0.0;
        for (int i = 1; i < NUM_COLUMNS - 1; ++i) {
            for (int j = 1; j < NUM_ROWS - 1; ++j) {
                newArray[j][i] = (oldArray[j - 1][i] + oldArray[j][i - 1] + oldArray[j + 1][i] + oldArray[j][i + 1]) / 4;
            }
        }
        for (int i = 1; i < NUM_COLUMNS - 1; ++i) {
            for (int j = 1; j < NUM_ROWS - 1; ++j) {
                sumValue = fabs(newArray[j][i] - oldArray[j][i]);
                if (maxValue <= sumValue) {
                    maxValue = sumValue;
                }
            }
        }
        for (int i = 1; i < NUM_COLUMNS - 1; ++i) {
            for (int j = 1; j < NUM_ROWS - 1; ++j) {
                oldArray[j][i] = newArray[j][i];
            }
        }
    }

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            cout << fixed << setw(ARRAY_WIDTH) << setprecision(ARRAY_PRECISION);
            if (j == NUM_ROWS - 1) {
                newArray[j][i] = 0.0;
                cout << newArray[j][i] << " ";
            }
            else if (((i == 0) || (i == NUM_COLUMNS - 1)) && ((j == 0) && (j != NUM_ROWS - 1))) {
                newArray[j][i] = 0.0;
                cout << newArray[j][i] << ", ";
            }
            else if (((j > 0) || (j != NUM_ROWS - 1)) && ((i == 0) || (i == NUM_COLUMNS - 1))) {
                newArray[j][i] = 100.0;
                cout << newArray[j][i] << ", ";
            }
            else if (((j != 0) && (j < NUM_ROWS - 1)) && (i != NUM_COLUMNS - 1)) {
                cout << newArray[j][i] << ", ";
            }
            else {
                cout << newArray[j][i] << ", ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void OutFile(double newArray[NUM_ROWS][NUM_COLUMNS]) {

    ofstream outFile;
    outFile.open("Hotplate.csv");

    if (!outFile.is_open()) {
        cerr << "File is not open";
        exit (1);
    }

    //double newArray[NUM_ROWS][NUM_COLUMNS];

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            outFile << fixed << setw(ARRAY_WIDTH) << setprecision(ARRAY_PRECISION);
            if (j == NUM_ROWS - 1) {
                newArray[j][i] = 0.0;
                outFile << newArray[j][i] << "";
            }
            else if (((i == 0) || (i == NUM_COLUMNS - 1)) && ((j == 0) && (j != NUM_ROWS - 1))) {
                newArray[j][i] = 0.0;
                outFile << newArray[j][i] << ",";
            }
            else if (((j > 0) || (j != NUM_ROWS - 1)) && ((i == 0) || (i == NUM_COLUMNS - 1))) {
                newArray[j][i] = 100.0;
                outFile << newArray[j][i] << ",";
            }
            else if (((j != 0) && (j < NUM_ROWS - 1)) && (i != NUM_COLUMNS - 1)) {
                outFile << newArray[j][i] << ",";
            }
            else {
                outFile << newArray[j][i] << ",";
            }
        }
        outFile << endl;
    }
    outFile << endl;
    outFile.close();
}

void OneIteration(double oldArray[NUM_ROWS][NUM_COLUMNS]) {

    double newArray[NUM_ROWS][NUM_COLUMNS];
    double sumValue = 0;
    double maxValue = 100.0;

    for (int x = 0; x < 3; x++) {
        maxValue = 0.0;
        for (int i = 1; i < NUM_COLUMNS - 1; ++i) {
            for (int j = 1; j < NUM_ROWS - 1; ++j) {
                newArray[j][i] = (oldArray[j - 1][i] + oldArray[j][i - 1] + oldArray[j + 1][i] + oldArray[j][i + 1]) / 4;
            }
        }
        for (int i = 1; i < NUM_COLUMNS - 1; ++i) {
            for (int j = 1; j < NUM_ROWS - 1; ++j) {
                sumValue = fabs(newArray[j][i] - oldArray[j][i]);
                if (maxValue <= sumValue) {
                    maxValue = sumValue;
                }
            }
        }
        for (int i = 1; i < NUM_COLUMNS - 1; ++i) {
            for (int j = 1; j < NUM_ROWS - 1; ++j) {
                oldArray[j][i] = newArray[j][i];
            }
        }
    }

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            cout << fixed << setw(ARRAY_WIDTH) << setprecision(ARRAY_PRECISION);
            if (j == NUM_ROWS - 1) {
                newArray[j][i] = 0.0;
                cout << newArray[j][i] << " ";
            }
            else if (((i == 0) || (i == NUM_COLUMNS - 1)) && ((j == 0) && (j != NUM_ROWS - 1))) {
                newArray[j][i] = 0.0;
                cout << newArray[j][i] << ", ";
            }
            else if (((j > 0) || (j != NUM_ROWS - 1)) && ((i == 0) || (i == NUM_COLUMNS - 1))) {
                newArray[j][i] = 100.0;
                cout << newArray[j][i] << ", ";
            }
            else if (((j != 0) && (j < NUM_ROWS - 1)) && (i != NUM_COLUMNS - 1)) {
                cout << newArray[j][i] << ", ";
            }
            else {
                cout << newArray[j][i] << ", ";
            }
        }
        cout << endl;
    }
    cout << endl;
}