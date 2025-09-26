#include <iostream>
#include <string>
using namespace std;

// Interface Discountable
class Discountable {
public:
    virtual double applyDiscount(double rate) = 0; // method
};

// Base class Product
class Product : public Discountable {
private:
    // Attributes
    int id;
    string name;
    double price;
    int stock;
public:
    Product() {
        id = 0;
        name = "";
        price = 0;
        stock = 0;
    }

    Product(int _id, string _name, double _price, int _stock) {
        id = _id;
        name = _name;
        price = _price;
        stock = _stock;
    }

    // Getter & Setter
    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getStock() {
        return stock;
    }

    void updateStock(int change) {
        stock = stock + change;
        if (stock < 0) {
            stock = 0;
        }
    }

    // Method
    void printInfo() {
        cout << "Product[" << id << "] " << name 
             << " | Price: " << price 
             << " | Stock: " << stock << endl;
    }

    double applyDiscount(double rate) {
        if (rate < 0 || rate > 1) {
            return price;
        } else {
            return price * (1 - rate);
        }
    }

    // Operator overload
    bool operator==(Product other) {
        if (id == other.getId()) {
            return true;
        } else {
            return false;
        }
    }
};

// Derived class Electronics
class Electronics : public Product {
private:
    // Attribute
    string brand;
public:
    Electronics() : Product() {
        brand = "";
    }

    Electronics(int _id, string _name, double _price, int _stock, string _brand)
        : Product(_id, _name, _price, _stock) {
        brand = _brand;
    }

    void updateStock(int change) {
        if (change > 0) {
            change = change + 1;
        }
        Product::updateStock(change);
    }

    void printInfo() {
        cout << "Electronics - ";
        Product::printInfo();
        cout << "   Brand: " << brand << endl;
    }
};

// Class InventoryList
class InventoryList {
private:
    // Attributes
    Product items[100];
    int count;
public:
    InventoryList() {
        count = 0;
    }

    // Method
    void add(Product item) {
        if (count < 100) {
            items[count] = item;
            count++;
        }
    }

    int size() {
        return count;
    }

    Product getAt(int i) {
        return items[i];
    }

    void printAll() {
        for (int i = 0; i < count; i++) {
            items[i].printInfo();
        }
    }
};

// Class ShoppingCart
class ShoppingCart : public Discountable {
private:
    // Attributes
    Product items[100];
    int count;
    double total;
public:
    ShoppingCart() {
        count = 0;
        total = 0;
    }

    // Operator overload add product
    ShoppingCart& operator+=(Product p) {
        if (p.getStock() > 0) {
            if (count < 100) {
                items[count] = p;
                count++;
                total = total + p.getPrice();
                cout << "Added " << p.getName() << " to cart.\n";
            }
        } else {
            cout << "Cannot add " << p.getName() << ", out of stock.\n";
        }
        return *this;
    }

    double applyDiscount(double rate) {
        if (rate < 0 || rate > 1) {
            return total;
        } else {
            return total * (1 - rate);
        }
    }

    void printCart() {
        cout << "Cart contents:\n";
        for (int i = 0; i < count; i++) {
            items[i].printInfo();
        }
        cout << "Total = " << total << endl;
    }
};

// Class Order
class Order {
private:
    // Attributes
    int orderId;
    string customer;
    double amount;
public:
    Order(int id, string cus, double money) {
        orderId = id;
        customer = cus;
        amount = money;
    }

    void printOrder() {
        cout << "Order #" << orderId 
             << " | Customer: " << customer 
             << " | Amount: " << amount << endl;
    }
};

// Main
int main() {
    cout << "E-commerce Demo\n";

    Product p1(1, "Notebook", 5.5, 10);
    Product p2(2, "Pencil", 1.2, 0);
    Electronics e1(3, "Headphone", 25.0, 5, "Sony");

    InventoryList inventory;
    inventory.add(p1);
    inventory.add(p2);
    inventory.add(e1);

    cout << "Inventory:\n";
    inventory.printAll();

    cout << "\nCompare products: ";
    if (p1 == p2) {
        cout << "Same\n";
    } else {
        cout << "Different\n";
    }

    ShoppingCart cart;
    cart += p1;   
    cart += p2;  
    cart += e1;  

    cout << "\nCart details:\n";
    cart.printCart();

    double newTotal = cart.applyDiscount(0.1);
    cout << "After discount: " << newTotal << endl;

    Order o1(101, "Ngo Quang Truong", newTotal);
    o1.printOrder();

    return 0;
}
