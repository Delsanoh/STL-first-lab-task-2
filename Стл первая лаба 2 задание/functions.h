#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

struct Student {
    std::string lastName;
    std::string firstName;
    std::string middleName;
    int32_t course;
    std::string group;

    // Полное ФИО
    std::string fullName() const;

    // Для вывода в файл
    std::string toString() const;
};

// Функция для чтения студентов из файла
std::vector<Student> readStudentsFromFile(const std::string& filename);

// Функция для записи студентов в файл
void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students);


// Функции сравнения для сортировки

// Сравнение по фамилии (по алфавиту)
bool compareByLastName(const Student& a, const Student& b);

// Сравнение по курсу, группе и фамилии
bool compareByCourseGroupLastName(const Student& a, const Student& b);

void bubbleSort(std::vector<Student>& students, bool (*compare)(const Student&, const Student&));

#endif // FUNCTIONS_H