#ifndef CLOTHING_H
#define CLOTHING_H
#include <set>
#include <iostream>
#include <string>
#include "product.h"

class Clothing : public Product {
public:
    Clothing(std::string name, double price, int quantity_in_stock, std::string size_, std::string brand_);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    ~Clothing();

protected:
    std::string size;
    std::string brand;

};



#endif