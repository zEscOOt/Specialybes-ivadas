#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Product{
public:
    string name;
    double price;
    int stock;

    Product(string n, double p, int s){
        this->name = n;
        this->price = p;
        this->stock = s;
    }
};

class Cart_Product: public Product{
public:
    int amount;
    int stock = -1; // I would like to make this a pointer to the original product's stock but don't know how to super an attribute and don't need to so -1

    Cart_Product(const Product& p, int a)
        : Product(p.name, p.price, p.stock),
          amount(a)
    {
    }

    double subTotal(){
        return this->price * this->amount;
    }
};

vector<Product> products{
    Product("Duona", 1.49, 7),
    Product("Pienas", 1.29, 4),
    Product("Obuoliai", 2.19, 10),
    Product("Bulves", 0.89, 0),
    Product("Suris", 3.79, 5),
    Product("Kiausiniai", 2.49, 8)
};

void print_product_list();
void cart_print(vector<Cart_Product> cart);
void cart_add_product(vector<Cart_Product>& cart);
void cart_remove_product(vector<Cart_Product>& cart);
void cart_pay(vector<Cart_Product>& cart); // According to the task only when this is called should products stock values be updated but I implamented that in cart_add_product();

int main(){
    vector<Cart_Product> cart{
        // testing data
        // Cart_Product(products[0], 2),
        // Cart_Product(products[1], 5),
        // Cart_Product(products[2], 1),
        // Cart_Product(products[4], 8),
    };
    
    int userInput;
    cout << "1. Rodyti parduotuve 2. Deti i krepseli 3. Salinti is krepselio \n4. Rodyti krepseli 5. Apmoketi 6. Iseiti " << endl;
    while (true)
    {
        
        cout << "Pasirinkite (1-6): ";
        cin >> userInput;

        switch (userInput)
        {
            case 1:
                print_product_list();
                break;
            case 2:
                cart_add_product(cart);
                break;
            case 3:
                cart_remove_product(cart);
                break;
            case 4:
                cart_print(cart);
                break;
            case 5:
                cart_pay(cart);
                break;
            case 6:
            // because product stock is calculated by cart_add_product and cart_remove_product this unintentionally means that the user can steal from the store if there cart has any items in it
                return 0;
            default:
                cout << "Netinkamas pasirinkimas..." << endl << endl;
                break;
        }
    }

    return 0;
}

void print_product_list(){
    for (size_t i = 0; i < products.size(); i++)
    {
        Product p = products.at(i);
        cout << i + 1 << ": " << left << setw(15) << p.name << fixed << setprecision(2) << p.price << " EUR ";
        if(p.stock != 0){
            cout << "(liko: " << p.stock << ")" << endl;
        } else {
            cout << "(ISPARDUOTA)" << endl;
        }
    }
    cout << endl;
}

void cart_print(vector<Cart_Product> cart){
    double final_sum = 0;

    if(cart.size() == 0){
        cout << "Cart is empty..." << endl;
        return;
    }

    for(size_t i = 0; i < cart.size(); i++){
        Cart_Product p = cart.at(i);
        cout << i + 1 << ": " << left << setw(15) << p.name 
             << fixed << setprecision(2) << p.amount 
             << " x " << p.price << " = " << p.subTotal() << endl;

        final_sum += p.subTotal();
    }
    cout << "Is viso: " << final_sum << " EUR" << endl << endl;
}

void cart_add_product(vector<Cart_Product>& cart){
    if(cart.size() > 10) {
        cout << "Cart is already full..." << endl;
        return;
    }

    int pIndex, pAmount;
    do { // Which product to add to the cart
        cout << "Norimos prekes numeris: ";
        cin >> pIndex;
        pIndex--;
        if (pIndex < 0 || pIndex > products.size() - 1){
            cout << "Norimos prekes nera..." << endl;
        } else {
            break;
        }
    } while (true);
    
    Product &product = products.at(pIndex);
    int &availableStock = product.stock;

    if(availableStock == 0){ 
        cout << "Preke isparduota..." << endl;
        return;
    }

    do { // How many of said product to add to cart
        cout << "Norimas kiekis: ";
        cin >> pAmount;
        
        if (pAmount < 1)
        {
            cout << "Netinkamas kiekis..." << endl;
        }
        else if (pAmount > availableStock)
        {
            cout << "Nepakanka sandelyje, galite paimti " << availableStock << endl;
        }
        else
        {
            break;
        }
    } while (true);

    // Check if product already exists in cart
    bool isProductPresent = false;
    int productIndex = -1;
    for(size_t i = 0; i < cart.size(); i++){
        string name = cart.at(i).name;
        string searchString = product.name;
        if(name == searchString) {
            isProductPresent = true;
            productIndex = i;
            break;
        }
    }

    // Add/Update cart product
    availableStock -= pAmount;
    if(!isProductPresent){
        Cart_Product item(product, pAmount);
        cart.push_back(item);
    } else {
        cart.at(productIndex).amount += pAmount;
    }
    cout << "Preke prideta." << endl << endl;
}

void cart_remove_product(vector<Cart_Product>& cart){
    int pos;
    do
    {
        cout << "Kuria preke salinti: ";
        cin >> pos;
        pos--;
        if(pos < 0 || pos > cart.size()-1){
            cout << "Sitos prekes nera..." << endl;
        } else break;
    } while (true);
    
    // readd the removed stock
    Cart_Product item = cart.at(pos);
    for(size_t i = 0; i < products.size(); i++)
    {
        Product& p = products.at(i);
        if(p.name == item.name){
            p.stock += item.amount;
        }
    }
    
    cart.erase(cart.begin() + pos);
    cout << "Preke isimta. " << endl << endl;
}

void cart_pay(vector<Cart_Product>& cart){
    if (cart.size() == 0)
    {
        cout << "Cart is empty..." << endl;
        return;
    }

    cart_print(cart);
    cart.clear();
    cout << "Aciu, kad pirkote!" << endl << endl;
    exit(0);
}