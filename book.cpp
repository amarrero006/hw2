#include "book.h"
#include "product.h"
#include "util.h"
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

Book::Book(std::string name, double price, int quantity_in_stock, std::string ISBN_, std::string author_)
    : Product("book", name, price, quantity_in_stock){
        ISBN = ISBN_;
        author = author_;
}

Book::~Book()
{
}

std::set<std::string> Book::keywords() const {
    std::set<std::string> result;
    string rawWords;
    rawWords = name_;
    rawWords+= " ";
    rawWords+= author;
    rawWords+= " ";
    result = parseStringToWords(rawWords);
    result.insert(ISBN);


    return result;
}

std::string Book::displayString() const {
    string result = name_;
        result += '\n';
        result += "Author: ";
        result += author;
        result += " ISBN: ";
        result += ISBN;
        result += '\n';
        stringstream ss1;
        string temp;
        ss1 << fixed << setprecision(2) << price_;
        ss1 >> temp;
        result += temp;
        result += "  ";
        result += to_string(qty_);
        result += " left.";

            return result;
}

void Book::dump(std::ostream &os) const {
    os << fixed << setprecision(2) << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN << "\n" << author << "\n";
}



