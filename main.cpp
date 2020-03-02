#include <iostream>
#include <utility>

#include "AvlTree.h"

struct Worker
{
    std::string Name;
    int Age;
    int Salary;

    explicit Worker(std::string name = "Def", int age = -1, int salary = -1)
        : Name(std::move(name)), Age(age), Salary(salary) {};

    friend bool operator< (const Worker& a, const Worker& b)
    {
        return a.Salary < b.Salary;
    }

    friend std::ostream& operator<< (std::ostream& os, const Worker& worker)
    {
        return os << worker.Name << " " << worker.Age << " " << worker.Salary;
    }
};

int main() {
    AvlTree<int> container;

    for(int i = 0; i < 5; ++i)
        container.insert(rand() % 100);

    for(int i = 0; i < container.size(); ++i)
        std::cout << container.at(i) << " ";

    for(int i = 0; i < container.size(); ++i)
        std::cout << container.find(container.at(i)) << " ";
    std::cout << "\n";
    AvlTree<Worker> workerContainer;

    workerContainer.emplace("Vladimir", 18, 20000);
    workerContainer.emplace("Dikiy", 19, 0);
    workerContainer.emplace("Anya", 19, 5000);
    workerContainer.emplace("Kuleshov", 19, 18998);

    for(int i = 0; i < workerContainer.size(); ++i)
        std::cout << workerContainer.at(i) << std::endl;
    std::cout << workerContainer.at(4) << std::endl;
    std::cout <<  workerContainer.find(Worker("Vladimir", 18, 20000));

    return 0;
}
