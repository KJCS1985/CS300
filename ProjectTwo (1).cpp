#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Convert input to uppercase for consistent course matching
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Load courses from CSV file into map
void loadCourses(map<string, Course>& courses, const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.title, ',');

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courses[toUpper(course.courseNumber)] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Print all courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    cout << "\nHere is a sample schedule:\n" << endl;
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.title << endl;
    }
}

// Print specific course info and prerequisites
void printCourseInfo(const map<string, Course>& courses, const string& courseNum) {
    string key = toUpper(courseNum);
    auto it = courses.find(key);
    if (it == courses.end()) {
        cout << "Course not found: " << courseNum << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.title << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites:" << endl;
        for (const string& prereqCode : course.prerequisites) {
            string prereqKey = toUpper(prereqCode);
            auto prereqIt = courses.find(prereqKey);
            if (prereqIt != courses.end()) {
                cout << "  " << prereqIt->second.courseNumber << ", " << prereqIt->second.title << endl;
            }
            else {
                cout << "  " << prereqCode << " (not found)" << endl;
            }
        }
    }
}

// Display menu
void displayMenu() {
    cout << "\n1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit\n" << endl;
}

int main() {
    map<string, Course> courses;
    bool dataLoaded = false;
    int choice = 0;

    cout << "Welcome to the course planner.\n" << endl;

    while (choice != 9) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter the file name to load: ";
            getline(cin, fileName);
            loadCourses(courses, fileName);
            dataLoaded = true;
            break;
        }
        case 2:
            if (!dataLoaded) {
                cout << "Please load the data structure first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        case 3:
            if (!dataLoaded) {
                cout << "Please load the data structure first." << endl;
            }
            else {
                string courseNum;
                cout << "What course do you want to know about? ";
                getline(cin, courseNum);
                printCourseInfo(courses, courseNum);
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
