#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string Student::fullName() const {
    return lastName + " " + firstName + " " + middleName;
}

std::string Student::toString() const {
    return lastName + " " + firstName + " " + middleName + " "
        + std::to_string(course) + " " + group;
}

std::vector<Student> readStudentsFromFile(const std::string& filename) {
    if (!fs::exists(filename)) {
        throw std::runtime_error("Файл не существует: " + filename);
    }

    if (!fs::is_regular_file(filename)) {
        throw std::runtime_error("'" + filename + "' не является обычным файлом");
    }

    if (fs::file_size(filename) == 0) {
        throw std::runtime_error("Файл пуст: " + filename);
    }

    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        file.close();
        throw std::runtime_error("Файл пуст: " + filename);
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        std::istringstream iss(line);
        Student student;

        if (iss >> student.lastName >> student.firstName >> student.middleName
            >> student.course >> student.group) {

            std::string extra;
            if (iss >> extra) {
                file.close();
                throw std::runtime_error("Неверный формат в строке " + std::to_string(lineNumber) +
                    ": лишние данные: '" + extra + "'");
            }

            students.push_back(student);
        }
        else {
            file.close();
            throw std::runtime_error("Неверный формат данных в строке " + std::to_string(lineNumber));
        }
    }

    if (students.empty()) {
        file.close();
        throw std::runtime_error("Файл не содержит корректных данных: " + filename);
    }

    file.close();
    return students;
}

void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students) {
    if (students.empty()) {
        throw std::runtime_error("Нет данных для записи в файл: " + filename);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось создать файл для записи: " + filename);
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
    if (students.empty()) {
        throw std::runtime_error("Нет студентов для сортировки");
    }

    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!compare(students[j], students[j + 1])) {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}