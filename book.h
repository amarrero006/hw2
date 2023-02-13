#ifndef BOOK_H
#define BOOK_H
#include <set>
#include <iostream>
#include <string>
#include "product.h"

class Book : public Product {
public:
    Book(std::string name, double price, int quantity_in_stock, std::string ISBN_, std::string author_);
    std::set<std::string>keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    ~Book();

protected:
    std::string ISBN;
    std::string author;

};



#endif