#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Function declarations
void loadCourses(map<string, Course>& courses);
void displayCourseList(const map<string, Course>& courses);
void displayCourseInformation(const map<string, Course>& courses);
void displayMenu();

int main() {
    map<string, Course> courses;
    int choice;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourses(courses);
            break;
        case 2:
            displayCourseList(courses);
            break;
        case 3:
            displayCourseInformation(courses);
            break;
        case 9:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}

// Display the main menu
void displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Load Courses" << endl;
    cout << "2. Display Course List" << endl;
    cout << "3. Display Course Information" << endl;
    cout << "9. Exit" << endl;
}

// Load course data from a file
void loadCourses(map<string, Course>& courses) {
    string filename;
    cout << "Enter the file name containing course data: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, title, prereq;
        getline(ss, courseNumber, ',');
        getline(ss, title, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.title = title;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Display all courses in alphanumeric order
void displayCourseList(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    cout << "\nCourse List:" << endl;
    for (const auto& pair : courses) {
        cout << pair.first << ", " << pair.second.title << endl;
    }
}

// Display information about a specific course, including prerequisites
void displayCourseInformation(const map<string, Course>& courses) {
    string courseNumber;
    cout << "Enter the course number: ";
    cin >> courseNumber;

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << "\nCourse Number: " << it->second.courseNumber << endl;
        cout << "Title: " << it->second.title << endl;
        cout << "Prerequisites: ";
        if (it->second.prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const string& prereq : it->second.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}
