#include "functions.h"
#include <iostream>
#include <vector>
#include <string>

int main() {

    std::setlocale(LC_ALL, "Russian");
    const std::string inputFile = "Students.txt";
    const std::string outputFile1 = "Fio.txt";
    const std::string outputFile2 = "Groups.txt";


    std::vector<Student> students = readStudentsFromFile(inputFile);

    if (students.empty()) {
        std::cerr << "Нет данных для обработки!" << std::endl;
        return 1;
    }

    std::cout << "Прочитано " << students.size() << " студентов" << std::endl;

    //for sort
    std::vector<Student> studentsForFio = students;
    std::vector<Student> studentsForGroups = students;

    bubbleSort(studentsForFio, compareByLastName);
    writeStudentsToFile(outputFile1, studentsForFio);
    std::cout << "Создан файл " << outputFile1 << " (сортировка по фамилиям)" << std::endl;

    bubbleSort(studentsForGroups, compareByCourseGroupLastName);
    writeStudentsToFile(outputFile2, studentsForGroups);
    std::cout << "Создан файл " << outputFile2 << " (сортировка по курсам, группам и фамилиям)" << std::endl;

    return 0;
}