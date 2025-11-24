#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Car {
private:
	string mark;
	string model;
public:
	Car(string markc, string modelc) : mark(markc), model(modelc) {
	}
	~Car() {
		cout << "| MARK: " << mark << " | MODEL: " << model << endl;
	}
};

int main() {
	vector<Car> cars;
	cars.reserve(20); 
	ifstream file("aaa.txt");
	string mark, model;

	if (!file.is_open()) {
		cout << "err" << endl;
		return 1;
	}

	while (file >> mark >> model) {
		cars.emplace_back(mark, model);
	}
	file.close();
	

	return 0;
}