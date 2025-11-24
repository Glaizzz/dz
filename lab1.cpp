#include <iostream>
#include <string>
#include <vector>
#include <memory>   // для std::shared_ptr


using namespace std;

class Product {
public:
    string name;
    double price;

    Product(const string& p_name, double p_price) : name(p_name), price(p_price) {
        cout << "Создан товар: " << name << " (" << price << " руб.)" << endl;
    }

    ~Product() {
        cout << "Удалён товар: " << name << endl;
    }
};

class Shop {
private:
    string shop_name;
    vector<shared_ptr<Product>> stock; // склад товаров (умные указатели)

public:
    Shop() : shop_name("DNS") {
        cout << "Создан магазин без имени." << endl;
    }

    Shop(const string& name, const vector<shared_ptr<Product>> i_stock) : shop_name(name), stock(i_stock) {
        cout << "Магазин " << name << " открыт." << endl;
    }

    void addProduct(const string& name, double price) {
        stock.push_back(make_shared<Product>(name, price));
        cout << "Добавлен товар: " << name << "." << endl;
    }

    shared_ptr<Product> searchProduct(const string& name) {
        for (auto& p : stock) {
            if (p->name == name) {
                cout << "Товар найден: " << p->name << " — " << p->price << " руб." << endl;
                return p;
            }
        }
        cout << "Товар " << name << " не найден." << endl;
        return nullptr;
    }

    void deleteProduct(const string& name) {
        auto it = remove_if(stock.begin(), stock.end(), [&name](const shared_ptr<Product>& p) {return p->name == name; });
        if (it != stock.end()) {
            cout << "Удалён товар " << name << " из магазина." << endl;
            stock.erase(it, stock.end());
        }
        else {
            cout << "Товар " << name << " не найден для удаления." << endl;
        }
    }

    void listProducts() const {
        cout << "Список товаров магазина " << shop_name << ":" << endl;
        for (const auto& p : stock) {
            cout << " - " << p->name << " (" << p->price << " руб.)" << endl;
        }
    }

    ~Shop() {
        cout << "Магазин " << shop_name << " закрыт. Освобождение ресурсов..." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Shop shop("DNS", {});
    int choice;

    do {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Добавить товар" << endl;
        cout << "2. Найти товар" << endl;
        cout << "3. Удалить товар" << endl;
        cout << "4. Показать все товары" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода! Попробуйте снова." << endl;
            continue;
        }

        string name;
        double price;

        switch (choice) {
        case 1:
            cout << "Введите название товара: ";
            cin >> name;
            cout << "Введите цену: ";
            cin >> price;
            shop.addProduct(name, price);
            break;

        case 2:
            cout << "Введите название товара для поиска: ";
            cin >> name;
            shop.searchProduct(name);
            break;

        case 3:
            cout << "Введите название товара для удаления: ";
            cin >> name;
            shop.deleteProduct(name);
            break;

        case 4:
            shop.listProducts();
            break;

        case 0:
            cout << "Выход из программы..." << endl;
            break;

        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }

    } while (choice != 0);

    cout << "\nПрограмма завершена.\n";
    return 0;
}