#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Node structure representing a course
struct Node {
    int courseCode;
    vector<Node*> prerequisites;

    Node(int code) : courseCode(code) {}
};

class CourseRegistration {
public:
    Node* root = nullptr;

    // Build the course tree from given data
    void buildCourseTree(vector<pair<int, vector<int>>>& courseData) {
        root = new Node(0); // Dummy root node
        for (auto& entry : courseData) {
            int courseCode = entry.first;
            Node* courseNode = findOrCreateNode(courseCode);
            for (int prereqCode : entry.second) {
                Node* prereqNode = findOrCreateNode(prereqCode);
                courseNode->prerequisites.push_back(prereqNode);
            }
        }
    }

    // Find or create a node in the tree
    Node* findOrCreateNode(int code) {
        Node* existingNode = findNode(code);
        if (existingNode) {
            return existingNode;
        }
        Node* newNode = new Node(code);
        return newNode;
    }

    // Find a node in the tree
    Node* findNode(int code) {
        return findNodeRecursive(root, code);
    }

    // Recursively find a node in the tree
    Node* findNodeRecursive(Node* current, int code) {
        if (!current) {
            return nullptr;
        }
        if (current->courseCode == code) {
            return current;
        }
        for (Node* prereq : current->prerequisites) {
            Node* result = findNodeRecursive(prereq, code);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    // Simulate user input for past and future courses
    void userInput(vector<int>& pastCourses, vector<int>& futureCourses) {
        // Code for taking user input on past and future courses
    }

    // Check if a course can be taken based on prerequisites and completed courses
    bool canTakeCourse(Node* course, vector<int>& completedCourses) {
        // Code for checking if a course can be taken
        return false;
    }

    // Display results of feasible and infeasible courses
    void displayResults(vector<int>& completedCourses, vector<int>& futureCourses) {
        // Code for displaying results
    }
};
// Simulate user input for past and future courses
void userInput(vector<int>& pastCourses, vector<int>& futureCourses) {
    cout << "Enter the courses you have completed (enter -1 to stop):\n";
    int courseCode;
    while (cin >> courseCode && courseCode != -1) {
        pastCourses.push_back(courseCode);
    }

    cout << "Enter the courses you are interested in (enter -1 to stop):\n";
    while (cin >> courseCode && courseCode != -1) {
        futureCourses.push_back(courseCode);
    }
}

// Check if a course can be taken based on prerequisites and completed courses
bool canTakeCourse(Node* course, vector<int>& completedCourses) {
    if (!course) {
        return false;
    }

    for (Node* prereq : course->prerequisites) {
        if (find(completedCourses.begin(), completedCourses.end(), prereq->courseCode) == completedCourses.end()) {
            return false; // A prerequisite hasn't been completed
        }
    }
    return true; // All prerequisites have been completed
}


int main() {
    vector<pair<int, vector<int>>> courseData = {
        {207, {101}},
        {311, {101}},
        // Add more course data here
    };

    CourseRegistration registrationSystem;
    registrationSystem.buildCourseTree(courseData);

    vector<int> pastCourses;
    vector<int> futureCourses;
    registrationSystem.userInput(pastCourses, futureCourses);

    vector<int> completedCourses;
    for (int course : pastCourses) {
        completedCourses.push_back(course);
    }

    cout << "Processing..." << endl;
    registrationSystem.displayResults(completedCourses, futureCourses);

    return 0;
}
