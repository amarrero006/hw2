#include "movie.h"
#include "product.h"
#include "util.h"
#include "sstream"
#include <iomanip>
#include <iostream>

using namespace std;

Movie::Movie(std::string name, double price, int quantity_in_stock, std::string genre_, std::string rating_)
        : Product("movie", name, price, quantity_in_stock){
    genre = genre_;
    rating = rating_;
}


Movie::~Movie()
{
}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> result;
    string rawWords;
    rawWords = name_;
    rawWords+= " ";
    rawWords+= genre;
    result = parseStringToWords(rawWords);
    

    return result;
}

std::string Movie::displayString() const {
    string result = name_;
    result += '\n';
    result += "Genre: ";
    result += genre;
    result += " Rating: ";
    result += rating;
    result += '\n';
    stringstream ss1;
    string temp;
    ss1.precision(2);
    ss1 << fixed << price_;
    ss1 >> temp;
    result += temp;
    result += "  ";
    result += to_string(qty_);
    result += " left.";

    return result;
}

void Movie::dump(std::ostream &os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre << "\n" << rating << "\n";
}



