#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "klasesDarbas.h"

int get_user_choice(int &main_choice)
{
    std::cout << "\n========================================\n";
    std::cout << "               MAIN MENU                \n";
    std::cout << "========================================\n";
    std::cout << "1. New order\n";
    std::cout << "2. Daily summary\n";
    std::cout << "3. Exit\n";
    
    while (true)
    {
        std::cout << "Choose (1-3): ";
        if (!(std::cin >> main_choice))
        {
            if (std::cin.eof())
            {
                std::exit(0);
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }
        if (main_choice < 1 || main_choice > 3)
        {
            std::cout << "Please enter a number between 1 and 3.\n";
            continue;
        }
        break;
    }

    std::cin.ignore(10000, '\n');

    return main_choice;
}

void new_order_customer(std::string &customer_name)
{
    std::cout << "Customer name: ";
    std::getline(std::cin, customer_name);
    if (customer_name == "")
    {
        customer_name = "Guest";
    }
}

// the return valuue indicates if the parent loop needs to continue in case of an order with no items
bool new_order_items(const std::string &name1, const double price1, const std::string &name2, const double price2, const std::string &name3, const double price3, int &qty1, int &qty2, int &qty3, double &subtotal)
{
    bool retFlag = false; // return flag
    bool ordering = true;
    while (ordering)
    {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. " << std::left << std::setw(12) << name1
                  << std::right << std::setw(5) << price1 << " EUR\n";
        std::cout << "2. " << std::left << std::setw(12) << name2
                  << std::right << std::setw(5) << price2 << " EUR\n";
        std::cout << "3. " << std::left << std::setw(12) << name3
                  << std::right << std::setw(5) << price3 << " EUR\n";
        std::cout << "0. Finish order\n";

        int item_choice = 0;
        while (true)
        {
            std::cout << "Item (0-3): ";
            if (!(std::cin >> item_choice))
            {
                if (std::cin.eof())
                {
                    std::exit(-1);
                }
                std::cin.clear();
                std::cin.ignore(9999, '\n');
                std::cout << "Invalid input, please enter a number.\n";
                continue;
            }
            if (item_choice < 0 || item_choice > 3)
            {
                std::cout << "Please enter a number between 0 and 3.\n";
                continue;
            }
            break;
        }

        if (item_choice == 0)
        {
            ordering = false;
        }
        else
        {
            int quantity = -1;
            while (true)
            {
                std::cout << "Quantity (0-20): ";
                if (!(std::cin >> quantity))
                {
                    if (std::cin.eof())
                    {
                        std::exit(-1);
                    }
                    std::cin.clear();
                    std::cin.ignore(9999, '\n');
                    std::cout << "Invalid input, please enter a number.\n";
                    continue;
                }
                if (quantity < 0 || quantity > 20)
                {
                    std::cout << "Please enter a number between 0 and 20.\n";
                    continue;
                }
                break;
            }

            if (item_choice == 1)
            {
                qty1 += quantity;
            }
            else if (item_choice == 2)
            {
                qty2 += quantity;
            }
            else
            {
                qty3 += quantity;
            }

            subtotal = qty1 * price1 + qty2 * price2 + qty3 * price3;
            std::cout << "Added. Current subtotal: " << subtotal << " EUR\n";
        }
    }

    if (subtotal == -1)
    {
        std::cout << "Empty order, nothing to pay.\n";
        {
            retFlag = true;
        };
    }
    return retFlag;
}

void get_loyalty_card(char &has_card){
    while (true)
    {
        std::cout << "Loyalty card? (y/n): ";
        std::cin >> has_card;
        if (has_card == 'y' || has_card == 'n')
        {
            break;
        }
        std::cout << "Please type y or n.\n";
    }
}

void calculate_discount_tax(int &discount_percent, double &subtotal, char has_card, double &discount_amount,double &discounted, double &tax){
    
    if (subtotal >= 100)
    {
        discount_percent = 15;
    }
    else if (subtotal >= 50)
    {
        discount_percent = 10;
    }
    else if (subtotal >= 25)
    {
        discount_percent = 5;
    }
    if (has_card == 'y')
    {
        discount_percent += 5;
    }
    discount_amount = subtotal * discount_percent / 100;
    discounted = subtotal - discount_amount;
    tax = discounted * 0.21;
}

void apply_tip(double &tip, double &discounted){
    std::cout << "\nTip: 1) none  2) 5%  3) 10%  4) 15%\n";
    int tip_choice = 0;
    while (true)
    {
        std::cout << "Choose (1-4): ";
        if (!(std::cin >> tip_choice))
        {
            if (std::cin.eof())
            {
                std::exit(0);
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }
        if (tip_choice < 1 || tip_choice > 4)
        {
            std::cout << "Please enter a number between 1 and 4.\n";
            continue;
        }
        break;
    }

    if (tip_choice == 2)
    {
        tip = discounted * 0.05;
    }
    else if (tip_choice == 3)
    {
        tip = discounted * 0.10;
    }
    else if (tip_choice == 4)
    {
        tip = discounted * 0.15;
    }
}

double split_bill(double &total, int &people){ 
    while (true)
    {
        std::cout << "Split between how many people (1-10): ";
        if (!(std::cin >> people))
        {
            if (std::cin.eof())
            {
                std::exit(0);
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }
        if (people < 1 || people > 10)
        {
            std::cout << "Please enter a number between 1 and 10.\n";
            continue;
        }
        break;
    }
    return total / people;
}

int main()
{
    // ---------- menu data ----------
    const std::string name1 = "Espresso";
    const std::string name2 = "Croissant";
    const std::string name3 = "Sandwich";
    const double price1 = 2.20;
    const double price2 = 2.80;
    const double price3 = 5.90;

    // ---------- statistics for the whole day ----------
    int sold1 = 0;
    int sold2 = 0;
    int sold3 = 0;
    int order_count = 0;
    double total_revenue = 0;
    double biggest_order_total = 0;
    std::string biggest_order_customer = "";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "========================================\n";
    std::cout << "          WELCOME TO CAFE CODE          \n";
    std::cout << "========================================\n";

    bool running = true;
    while (running)
    {
        // ---------- main menu ----------
        int main_choice = 0;
        get_user_choice(main_choice); 

        if (main_choice == 1)
        {
            // ---------- new order: customer ----------
            std::string customer_name;
            new_order_customer(customer_name);

            // ---------- new order: choosing items ----------
            int qty1 = 0;
            int qty2 = 0;
            int qty3 = 0;
            double subtotal = -1;

            if(new_order_items(name1, price1, name2, price2, name3, price3, qty1, qty2, qty3, subtotal))  continue; // will go back to main menu if new cusmomer ordered nothing

            // ---------- loyalty card ----------
            char has_card = 'n';
            get_loyalty_card(has_card);

            // ---------- discount and tax ----------
            int discount_percent = 0;
            double discounted = 0;
            double discount_amount;
            double tax = 0;
            calculate_discount_tax(discount_percent, subtotal, has_card, discount_amount, discounted, tax);

            // ---------- tip ----------
            double tip = 0;
            apply_tip(tip, discounted);

            // ---------- total (rounded to whole cents) ----------
            double total = discounted + tax + tip;
            total = static_cast<int>(total * 100 + 0.5) / 100.0;

            // ---------- splitting the bill ----------
            int people = 1;
            double per_person = split_bill(total, people);
    
            // ---------- payment ----------
            std::cout << "Payment: 1) cash  2) card\n";
            int payment_method = 0;
            while (true)
            {
                std::cout << "Choose (1-2): ";
                if (!(std::cin >> payment_method))
                {
                    if (std::cin.eof())
                    {
                        std::exit(0);
                    }
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid input, please enter a number.\n";
                    continue;
                }
                if (payment_method < 1 || payment_method > 2)
                {
                    std::cout << "Please enter a number between 1 and 2.\n";
                    continue;
                }
                break;
            }

            double cash_given = 0;
            double change = 0;
            int notes20 = 0;
            int notes10 = 0;
            int notes5 = 0;
            int coins2 = 0;
            int coins1 = 0;
            int leftover_cents = 0;

            if (payment_method == 1)
            {
                while (true)
                {
                    std::cout << "Cash given in EUR: ";
                    if (!(std::cin >> cash_given))
                    {
                        if (std::cin.eof())
                        {
                            std::exit(0);
                        }
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid input, please enter a number.\n";
                        continue;
                    }
                    if (cash_given < total)
                    {
                        std::cout << "Not enough, the total is " << total << " EUR.\n";
                        continue;
                    }
                    break;
                }
                change = cash_given - total;

                // whole euros are split into notes and coins, largest first
                int change_cents = static_cast<int>(change * 100 + 0.5);
                int whole_euros = change_cents / 100;
                leftover_cents = change_cents % 100;
                notes20 = whole_euros / 20;
                whole_euros = whole_euros % 20;
                notes10 = whole_euros / 10;
                whole_euros = whole_euros % 10;
                notes5 = whole_euros / 5;
                whole_euros = whole_euros % 5;
                coins2 = whole_euros / 2;
                coins1 = whole_euros % 2;
            }

            // ---------- receipt ----------
            print_receipt(customer_name, qty1, name1, price1, qty2, name2, price2, qty3, name3, price3, subtotal, discount_percent, discount_amount, tax, tip, total, people, per_person, payment_method, cash_given, change, notes20, notes10, notes5, coins2, coins1, leftover_cents, sold1, sold2, sold3, order_count, total_revenue, biggest_order_total, biggest_order_customer);
        }
        else if (main_choice == 2)
        {
            // ---------- daily summary ----------
            int retFlag;
            print_daily_summary(order_count, name1, sold1, sold2, name2, sold3, name3, total_revenue, biggest_order_total, biggest_order_customer, retFlag);
            if (retFlag == 3)
                continue;
        }
        else
        {
            running = false;
        }
    }

    std::cout << "\n========================================\n";
    std::cout << "        CAFE CODE IS NOW CLOSED         \n";
    std::cout << "========================================\n";
    return 0;
}

void print_daily_summary(int order_count, const std::string &name1, int sold1, int sold2, const std::string &name2, int sold3, const std::string &name3, double total_revenue, double biggest_order_total, std::string &biggest_order_customer, int &retFlag)
{
    retFlag = 1;
    std::cout << "\n========================================\n";
    std::cout << "              DAILY SUMMARY             \n";
    std::cout << "========================================\n";

    if (order_count == 0)
    {
        std::cout << "No orders yet today.\n";
        {
            retFlag = 3;
            return;
        };
    }

    std::string best_name = name1;
    int best_count = sold1;
    if (sold2 > best_count)
    {
        best_name = name2;
        best_count = sold2;
    }
    if (sold3 > best_count)
    {
        best_name = name3;
        best_count = sold3;
    }

    std::cout << "Orders:            " << order_count << "\n";
    std::cout << "Items sold:        " << sold1 + sold2 + sold3 << "\n";
    std::cout << "Revenue:           " << total_revenue << " EUR\n";
    std::cout << "Average order:     " << total_revenue / order_count << " EUR\n";
    std::cout << "Biggest order:     " << biggest_order_total << " EUR (" << biggest_order_customer << ")\n";
    std::cout << "Best seller:       " << best_name << " (" << best_count << ")\n";
    std::cout << "\nSold per item:\n";
    std::cout << "  " << std::left << std::setw(12) << name1 << std::right << std::setw(4) << sold1 << "\n";
    std::cout << "  " << std::left << std::setw(12) << name2 << std::right << std::setw(4) << sold2 << "\n";
    std::cout << "  " << std::left << std::setw(12) << name3 << std::right << std::setw(4) << sold3 << "\n";
    std::cout << "========================================\n";
}

void print_receipt(std::string &customer_name, int qty1, const std::string &name1, const double price1, int qty2, const std::string &name2, const double price2, int qty3, const std::string &name3, const double price3, double subtotal, int discount_percent, double discount_amount, double tax, double tip, double total, int people, double per_person, int payment_method, double cash_given, double change, int notes20, int notes10, int notes5, int coins2, int coins1, int leftover_cents, int &sold1, int &sold2, int &sold3, int &order_count, double &total_revenue, double &biggest_order_total, std::string &biggest_order_customer)
{
std::cout << "\n========================================\n";
            std::cout << "                RECEIPT                 \n";
            std::cout << "========================================\n";
            std::cout << "Customer: " << customer_name << "\n";
            std::cout << "----------------------------------------\n";
            if (qty1 > 0)
            {
                std::cout << std::left << std::setw(12) << name1
                          << std::right << std::setw(3) << qty1 << " x "
                          << std::setw(5) << price1 << " = "
                          << std::setw(7) << qty1 * price1 << "\n";
            }
            if (qty2 > 0)
            {
                std::cout << std::left << std::setw(12) << name2
                          << std::right << std::setw(3) << qty2 << " x "
                          << std::setw(5) << price2 << " = "
                          << std::setw(7) << qty2 * price2 << "\n";
            }
            if (qty3 > 0)
            {
                std::cout << std::left << std::setw(12) << name3
                          << std::right << std::setw(3) << qty3 << " x "
                          << std::setw(5) << price3 << " = "
                          << std::setw(7) << qty3 * price3 << "\n";
            }
            std::cout << "----------------------------------------\n";
            std::cout << std::left << std::setw(26) << "Subtotal:"
                      << std::right << std::setw(10) << subtotal << " EUR\n";
            if (discount_percent > 0)
            {
                std::cout << std::left << std::setw(26) << "Discount (" + std::to_string(discount_percent) + "%):"
                          << std::right << std::setw(10) << -discount_amount << " EUR\n";
            }
            std::cout << std::left << std::setw(26) << "Tax (21%):"
                      << std::right << std::setw(10) << tax << " EUR\n";
            if (tip > 0)
            {
                std::cout << std::left << std::setw(26) << "Tip:"
                          << std::right << std::setw(10) << tip << " EUR\n";
            }
            std::cout << "----------------------------------------\n";
            std::cout << std::left << std::setw(26) << "TOTAL:"
                      << std::right << std::setw(10) << total << " EUR\n";
            if (people > 1)
            {
                std::cout << std::left << std::setw(26) << "Per person (" + std::to_string(people) + "):"
                          << std::right << std::setw(10) << per_person << " EUR\n";
            }
            if (payment_method == 1)
            {
                std::cout << std::left << std::setw(26) << "Cash given:"
                          << std::right << std::setw(10) << cash_given << " EUR\n";
                std::cout << std::left << std::setw(26) << "Change:"
                          << std::right << std::setw(10) << change << " EUR\n";
                if (notes20 > 0)
                {
                    std::cout << "  " << notes20 << " x 20 EUR note\n";
                }
                if (notes10 > 0)
                {
                    std::cout << "  " << notes10 << " x 10 EUR note\n";
                }
                if (notes5 > 0)
                {
                    std::cout << "  " << notes5 << " x 5 EUR note\n";
                }
                if (coins2 > 0)
                {
                    std::cout << "  " << coins2 << " x 2 EUR coin\n";
                }
                if (coins1 > 0)
                {
                    std::cout << "  " << coins1 << " x 1 EUR coin\n";
                }
                if (leftover_cents > 0)
                {
                    std::cout << "  + " << leftover_cents << " cents\n";
                }
            }
            else
            {
                std::cout << "Paid by card, approved.\n";
            }
            std::cout << "========================================\n";
            std::cout << "          THANK YOU, " << customer_name << "!\n";
            std::cout << "========================================\n";

            // ---------- update the daily statistics ----------
            sold1 += qty1;
            sold2 += qty2;
            sold3 += qty3;
            order_count++;
            total_revenue += total;
            if (total > biggest_order_total)
            {
                biggest_order_total = total;
                biggest_order_customer = customer_name;
            }
}
