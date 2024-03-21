#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Teacher
{
private:

    int teacherID;
    string name;
    string email;
    vector<string> coursesTaught;

public:
    Teacher(int tid = 0, string tname = "", string temail = "")
    {
        teacherID = tid;
        name = tname;
        email = temail;
    }

    void assignCourse(string course)
    {
        coursesTaught.push_back(course);
    }

    void removeCourse(string course)
    {
        for (int i = 0; i < coursesTaught.size(); ++i)
        {
            if (coursesTaught[i] == course)
            {
                coursesTaught.erase(coursesTaught.begin() + i);
                break;
            }
        }
    }

    void viewCourses()
    {
        int index = 1;
        cout << endl << "Courses Taught by " << name << " are mentioned below " << endl << endl;

        for (string course : coursesTaught)
        {
            cout << "\t\t\t\t Teacher " << index << " : " << course << endl;
            index++;
        }

        cout << endl;
    }

    void saveToFile(ofstream& file)
    {
        file << teacherID << "," << name << "," << email << ",";

        for (string course : coursesTaught)
        {
            file << course << ";";
        }
        file << endl;

    }

    int getTeacherID()
    {
        return teacherID;
    }
};

class Course
{
private:
    string courseCode;
    string courseName;
    Teacher teacher;
    vector<string> studentsEnrolled;
    int maxCapacity;
    int currentCapacity;

public:
    Course(string code, string name, Teacher t, int capacity)
    {
        courseCode = code;
        courseName = name;
        teacher = t;
        maxCapacity = capacity;
        currentCapacity = 0;
    }

    bool addStudent(string student)
    {
        if (currentCapacity >= maxCapacity)
        {
            cout << "Course is full. Cannot enroll more students." << endl;
            return false;
        }

        studentsEnrolled.push_back(student);
        currentCapacity++;

        return true;
    }

    void removeStudent(string student)
    {
        for (int i = 0; i < studentsEnrolled.size(); ++i)
        {
            if (studentsEnrolled[i] == student)
            {
                studentsEnrolled.erase(studentsEnrolled.begin() + i);
                currentCapacity--;
                return;
            }
        }
    }

    void viewStudents()
    {
        int index = 1;
        cout << endl << "Students Enrolled in " << courseName << " are mentioned below " << endl << endl;
        for (string student : studentsEnrolled)
        {
            cout << "\t\t\t\t Student " << index << " : " << student << endl;
            index++;
        }
        cout << endl << endl;
    }

    void saveToFile(ofstream& file)
    {
        file << courseCode << "," << courseName << "," << teacher.getTeacherID() << "," << currentCapacity << "," << maxCapacity << ",";

        for (string student : studentsEnrolled)
        {
            file << student << ";";
        }

        file << endl;
    }

    string getCourseCode()
    {
        return courseCode;
    }

    string getCourseName()
    {
        return courseName;
    }
};

class Student
{
private:
    int studentID;
    string name;
    string email;
    vector<string> coursesEnrolled;

public:
    Student(int id, string n, string e)
    {
        studentID = id;
        name = n;
        email = e;
    }

    void enrollInCourse(Course& course)
    {
        coursesEnrolled.push_back(course.getCourseCode());
    }


    void dropCourse(string course)
    {
        for (int i = 0; i < coursesEnrolled.size(); ++i)
        {
            if (coursesEnrolled[i] == course)
            {
                coursesEnrolled.erase(coursesEnrolled.begin() + i);
                break;
            }
        }
    }

    void viewCourses()
    {
        int index = 1;

        cout << endl << "Courses Enrolled by " << name << " are mentioned below " << endl << endl;

        for (string course : coursesEnrolled)
        {
            cout << "\t\t\t\t Courses " << index << " : " << course << endl;
            index++;
        }

        cout << endl;
    }

    void saveToFile(ofstream& file)
    {
        file << studentID << "," << name << "," << email << ",";

        for (string course : coursesEnrolled)
        {
            file << course << ";";
        }

        file << endl;
    }

    string getName()
    {
        return name;
    }

    bool isEnrolledInCourse(string& courseCode)
    {
        return find(coursesEnrolled.begin(), coursesEnrolled.end(), courseCode) != coursesEnrolled.end();
    }


    vector<string> getEnrolledCourses()
    {
        return coursesEnrolled;
    }


};






/////////////////////////////////////////
/////////////////////////////////////////////////
///////////////////////////////////////////////////////



void displayMenu()
{
    cout << "===== University Management System =====\n";
    cout << "1. Enroll in a course\n";
    cout << "2. View enrolled courses\n";
    cout << "3. Exit\n";

}


void displayAvailableCourses(vector<Course>& courses)
{
    cout << "Available Courses:\n";
    int index = 1;
    for (Course& course : courses)
    {
        cout << index << ". " << course.getCourseCode() << " - " << course.getCourseName() << endl;
        index++;
    }
}


void displayStudentCourses(Student& student)
{
    cout << "\nCourses Enrolled by " << student.getName() << " are mentioned below\n\n";

    const vector<string>& enrolledCourses = student.getEnrolledCourses();

    int index = 1;
    for (const string& course : enrolledCourses)
    {
        cout << "\t" << index << ". " << course << endl;
        index++;
    }
    cout << endl;
}


int main()
{
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;

    // Sample data for 10 students, 5 teachers, and 15 courses
    for (int i = 1; i <= 10; ++i)
    {
        students.push_back(Student(1000 + i, "Student " + to_string(i), "student" + to_string(i) + "@example.com"));
    }

    for (int i = 1; i <= 5; ++i)
    {
        teachers.push_back(Teacher(2000 + i, "Teacher " + to_string(i), "teacher" + to_string(i) + "@example.com"));
    }

    for (int i = 1; i <= 15; ++i)
    {
        string courseCode = "CSCI" + to_string(i);
        string courseName;

        if (i <= 5)
        {
            courseName = "AI Course " + to_string(i);
        }
        else if (i <= 10)
        {
            courseName = "CS Course " + to_string(i);
        }
        else if (i <= 15)
        {
            courseName = "Web Development Course " + to_string(i);
        }

        int teacherIndex = (i - 1) % 5;
        courses.push_back(Course(courseCode, courseName, teachers[teacherIndex], 30));
    }

    char choice = ' ';

    do
    {
        cout << endl << endl;


        displayMenu();
        cout << endl << endl;
        cout << "Enter your choice: ";


        cin >> choice;
        cout << endl;
        cout << endl;

        switch (choice)
        {
        case '1':
        {

            cout << "List of Students:\n";
            for (size_t i = 0; i < students.size(); ++i)
            {
                cout << i + 1 << ". " << students[i].getName() << endl;
            }

            cout << "\nSelect a student by index: ";

            int studentIndex;
            cin >> studentIndex;

            if (studentIndex < 1 || studentIndex > students.size())
            {
                cout << "Invalid student index. Please try again.\n";
                break;
            }
            Student& selectedStudent = students[studentIndex - 1];


            displayAvailableCourses(courses);
            cout << "Select a course by index: ";

            int courseIndex;
            cin >> courseIndex;

            if (courseIndex < 1 || courseIndex > courses.size())
            {
                cout << "Invalid course index. Please try again.\n";
                break;
            }
            Course& selectedCourse = courses[courseIndex - 1];


            selectedStudent.enrollInCourse(selectedCourse);
            cout << "Enrolled " << selectedStudent.getName() << " in " << selectedCourse.getCourseName() << endl;
            break;
        }

        case '2':
        {
            cout << "Select a student by index: ";
            int studentIndex;
            cin >> studentIndex;

            if (studentIndex < 1 || studentIndex > students.size())
            {
                cout << "Invalid student index. Please try again.\n";
                break;
            }
            Student& selectedStudent = students[studentIndex - 1];
            displayStudentCourses(selectedStudent);
            break;
        }

        case '3':
        {
            cout << "Exiting the program.\n";
            break;
        }

        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }

    } while (choice != '3');




    // Save data to file

    ofstream studentsFile("students.txt");
    if (!studentsFile.is_open())
    {
        cout << "Error: Unable to open students.txt for writing." << endl;
        return 1;
    }

    for (auto& student : students)
    {
        student.saveToFile(studentsFile);
    }
    studentsFile.close();

    ofstream teachersFile("teachers.txt");
    if (!teachersFile.is_open())
    {
        cout << "Error: Unable to open teachers.txt for writing." << endl;
        return 1;
    }

    for (auto& teacher : teachers)
    {
        teacher.saveToFile(teachersFile);
    }
    teachersFile.close();

    ofstream coursesFile("courses.txt");
    if (!coursesFile.is_open())
    {
        cout << "Error: Unable to open courses.txt for writing." << endl;
        return 1;
    }

    for (auto& course : courses)
    {
        course.saveToFile(coursesFile);
    }
    coursesFile.close();

    return 0;
}