#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

std::string Student::fullName() const {
    return lastName + " " + firstName + " " + middleName;
}

std::string Student::toString() const {
    return lastName + " " + firstName + " " + middleName + " "
        + std::to_string(course) + " " + group;
}

std::vector<Student> readStudentsFromFile(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return students;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student student;

        if (iss >> student.lastName >> student.firstName >> student.middleName
            >> student.course >> student.group) {
            students.push_back(student);
        }
    }

    file.close();
    return students;
}

void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    for (std::vector<Student>::const_iterator it = students.begin(); it != students.end(); ++it) {
        file << it->toString() << std::endl;
    }

    file.close();
}



bool compareByLastName(const Student& a, const Student& b) {
    return a.lastName < b.lastName;
}

bool compareByCourseGroupLastName(const Student& a, const Student& b) {
    if (a.course != b.course) {
        return a.course < b.course;
    }
    if (a.group != b.group) {
        return a.group < b.group;
    }
    return a.lastName < b.lastName;
}

void bubbleSort(std::vector<Student>& students, bool (*compare)(const Student&, const Student&)) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!compare(students[j], students[j + 1])) {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}