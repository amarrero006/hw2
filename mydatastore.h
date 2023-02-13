#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include <queue>
#include <map>

class MyDataStore : public DataStore {
public:
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);


public:
    std::map<User*, std::queue<Product*> > carts_;
    std::map<Product*, std::set<std::string> > inventory_;
    std::vector<User*> users_;

};




#endif