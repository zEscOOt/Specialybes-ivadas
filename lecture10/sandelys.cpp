#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Product
{
    string name;
    double price;
    int amount;
    double weight;

    Product(string s, double p, int a, double w)
    {
        this->name = s;
        this->price = p;
        this->amount = a;
        this->weight = w;
    }

    void print()
    {
        cout << name << " " << price << " EUR " << amount << " " << weight << "kg" << endl;
    }
};

void list_print(vector<Product> list);
void list_add(vector<Product> &list);
void list_update(vector<Product> &list);
Product *list_find_heaviest(vector<Product> &list);
void list_print_avg_weight_price(vector<Product> list);
void list_sort_weight(vector<Product> &list);

vector<Product> list;

int main()
{
    ifstream data("products.csv");
    string line;
    getline(data, line); // this doesnt ignore the 1st line like it should
    while (getline(data, line)) {
        stringstream ss(line);
        string n;
        double p;
        int a;
        double w;

        getline(ss, n, ',');
        getline(ss, p, ',');
        getline(ss, a, ',');
        getline(ss, w);

        list.push_back({n, p, a, w});
    }

    data.close();

    const string menu =
        "1. Print products\n"
        "2. Add product\n"
        "3. Update product amount\n"
        "4. Find heaviest product\n"
        "5. Print average weight and price\n"
        "6. Sort products by weight\n"
        "7. Exit\n";
    int choice;
    do
    {
        cout << menu << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            list_print(list);
            break;
        case 2:
            list_add(list);
            break;
        case 3:
            list_update(list);
            break;
        case 4:
            list_find_heaviest(list);
            break;
        case 5:
            list_print_avg_weight_price(list);
            break;
        case 6:
            list_sort_weight(list);
            cout << "Products sorted by weight." << endl;
            break;
        case 7:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid option..." << endl;
        }
    } while (true);
    
    return 0;
}

void list_print(vector<Product> list)
{
    if (list.size() == 0)
    {
        cout << "List is empty..." << endl;
        return;
    }
    for (size_t i = 0; i < list.size(); i++)
    {
        cout << i << ": ";
        list.at(i).print();
    }
    cout << endl;
}

void list_add(vector<Product> &list)
{
    if (list.size() >= 15)
    {
        cout << "List is full..." << endl;
        return;
    }

    double price, weight;
    int amount;
    string name;

    do
    {
        cout << "Enter product (name, price, amount, weight): ";
        cin >> name >> price >> amount >> weight;
        if (name != "" || name != " " && price >= 0 && amount > 0 && weight > 0)
        {
            list.push_back(Product(name, price, amount, weight));
            return;
        }
        else
        {
            cout << "Invalid product..." << endl;
        }
    } while (true);
}

void list_update(vector<Product> &list){
    int pos, amount;
    do
    {
        cout << "Which item to update: ";
        cin >> pos;
        pos--;
        if(pos >=0 && pos < list.size()){
            do
            {
                cout << "What amount to add: ";
                cin >> amount;
                if(list.at(pos).amount - amount < 0){
                    cout << "The amount removed is too much..." << endl;
                } else {
                    list.at(pos).amount += amount;
                    cout << "Product amount has been updated." << endl << endl;
                    return;
                }
            } while (true);
        } else {
            cout << "This item doesn't exist..." << endl;
        }
    } while (true);
}


Product* list_find_heaviest(vector<Product> &list){
    if(list.size() == 0){
        cout << "List is empty..." << endl;
        return nullptr;
    }

    double maxWeight = 0;
    Product* pointer;
    for(Product p : list){
        if(p.weight > maxWeight){
            maxWeight = p.weight;
            pointer = &p;
        }
    }
    if(maxWeight > 0){
        cout << "Heaviest item is: " << maxWeight << "kg" << endl
             << endl;
        return pointer;
    } else {
        return nullptr;
    }
}


void list_print_avg_weight_price(vector<Product> list){
    double avgWeight = 0, avgPrice = 0;

    for (size_t i = 0; i < list.size(); i++)
    {
        Product p = list.at(i);
        avgWeight += p.weight * p.amount;
        avgPrice += p.price * p.amount;
    }
    avgWeight /= list.size();
    avgPrice  /= list.size();
    
    cout << "Average weight: " << avgWeight << "kg" << endl;
    cout << "Average price: " << avgPrice << " EUR" << endl;
}

struct {
    bool operator()(Product a, Product b) const {return a.weight < b.weight;}
}customProductLessWeight;

void list_sort_weight(vector<Product> &list){
    sort(list.begin(), list.end(), customProductLessWeight);
}