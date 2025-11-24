#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;


class Human {
protected:
    string name;
public:
    Human(const string& n) : name(n) {}
    virtual void display() const {
        cout << "Человек: " << name << endl;
    }
    virtual ~Human() {}
};

class Preschooler : public Human {
public:
    Preschooler(const string& n) : Human(n) {}
    void display() const override {
        cout << "Дошкольник: " << name << endl;
    }
};

class Schoolchild : public Human {
public:
    Schoolchild(const string& n) : Human(n) {}
    void display() const override {
        cout << "Школьник: " << name << endl;
    }
};

class Student : public Human {
public:
    Student(const string& n) : Human(n) {}
    void display() const override {
        cout << "Студент: " << name << endl;
    }
};

class Worker : public Human {
public:
    Worker(const string& n) : Human(n) {}
    void display() const override {
        cout << "Работающий: " << name << endl;
    }
};


template<typename T>
class PointerArray {
private:
    vector<T*> pointers;
public:
    ~PointerArray() {
        for (auto ptr : pointers) {
            delete ptr;
        }
    }

    // Перегрузка оператора 
    T*& operator[](size_t index) {
        if (index >= pointers.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        return pointers[index];
    }

    void add(T* ptr) {
        pointers.push_back(ptr);
    }

    size_t size() const {
        return pointers.size();
    }
};

int safeMultiply(int a, int b) {
    if (a > 0 && b > 0 && a > INT_MAX / b) {
        throw overflow_error("Переполнение при умножении");
    }
    return a * b;
}

int main() {
    setlocale(LC_ALL, "RU");
    PointerArray<Human> array;

    array.add(new Preschooler("Маша"));
    array.add(new Schoolchild("Петя"));
    array.add(new Student("Иван"));
    array.add(new Worker("Анна"));

    for (size_t i = 0; i < array.size(); i++) {
        array[i]->display();
    }

    try {
        cout << "\nПопытка доступа к несуществующему индексу:" << endl;
        array[10]->display();
    }
    catch (const out_of_range& e) {
        cout << "Поймано исключение: " << e.what() << endl;
    }

    try {
        cout << "\nПроверка переполнения:" << endl;
        int result = safeMultiply(1000000, 1000000);
        cout << "Результат: " << result << endl;
    }
    catch (const overflow_error& e) {
        cout << "Поймано исключение: " << e.what() << endl;
    }

    return 0;
}