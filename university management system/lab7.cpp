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