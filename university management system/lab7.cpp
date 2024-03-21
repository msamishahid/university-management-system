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