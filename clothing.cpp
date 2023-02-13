#include "clothing.h"
#include "product.h"
#include "util.h"
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

Clothing::Clothing(std::string name, double price, int quantity_in_stock, std::string size_, std::string brand_)
        : Product("clothing", name, price, quantity_in_stock){
    size = size_;
    brand = brand_;
}


Clothing::~Clothing()
{
}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> result;
    string rawWords;
    rawWords = name_;
    rawWords+= " ";
    rawWords+= brand;
    rawWords+= " ";
    result = parseStringToWords(rawWords);

    return result;
}

std::string Clothing::displayString() const {
    string result = name_;
    result += '\n';
    result += "Size: ";
    result += size;
    result += " Brand: ";
    result += brand;
    result += '\n';
    stringstream ss1;
    string temp;
    ss1.precision(2);
    ss1 << fixed <<  price_;
    ss1 >> temp;
    result += temp;
    result += "  ";
    result += to_string(qty_);
    result += " left.";

    return result;
}

void Clothing::dump(std::ostream &os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size << "\n" << brand << "\n";
}



