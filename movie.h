#ifndef MOVIE_H
#define MOVIE_H
#include <set>
#include <iostream>
#include <string>
#include "product.h"

class Movie : public Product {
public:
    Movie(std::string name, double price, int quantity_in_stock, std::string genre_, std::string rating_);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    ~Movie();

protected:
    std::string genre;
    std::string rating;

};



#endif