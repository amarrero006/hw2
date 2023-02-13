#include "product.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include <iostream>

using namespace std;

MyDataStore::~MyDataStore(){
    inventory_.clear();
    while(!users_.empty()) {
        delete users_.back();
        users_.pop_back();
    }
    carts_.clear();
}
void MyDataStore::addProduct(Product* p){
    inventory_.insert(make_pair(p, p->keywords()));
}
void MyDataStore::addUser(User *u) {
    users_.push_back(u);
    queue<Product*> prods;
    carts_.insert(make_pair(u, prods));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

    vector<Product*> result;
    set<string> query;
    set<string> temp1;


    if(terms.size() == 0){
        cout << "Invalid search.";
        return result;
    }


    for(int i = 0; i < terms.size(); i++){
        string temp = terms[i];
        query.insert(temp);
    }



    // OR search. This search looks for any product which contains any of the query terms
    // as a keyword. This is calculated by simply finding the intersection of the two 
    // sets. If the resultant set is not the empty set, then that product is added to the 
    // results. 
    if(type == 1){
        for(std::map<Product*, set<string> >::iterator it = inventory_.begin(); it != inventory_.end(); it++){
            set<string> temp2(setIntersection(query, it->second));
            if(temp2.size() > 0){
                result.push_back(it->first);
            }
            temp2.clear();
        }
    }

    // AND search. This search also uses the set intersection function. If the resultant
    // set is of the same cardinality as the intitial set, the two are equal and thus
    // the relevant product is added to the results.
    else{
        for(std::map<Product*, set<string> >::iterator it = inventory_.begin(); it != inventory_.end(); it++){
            set<string> temp2 (setIntersection(query, it->second));
            if(temp2.size() == query.size()){
                result.push_back(it->first);
            }
            temp2.clear();
        }

    }

    return result;
}

void MyDataStore::dump(std::ostream &ofile) {

    ofile << "<products>" << endl;
    for(map<Product*, set<string> >::iterator it = inventory_.begin(); it != inventory_.end(); it++){
        it->first->dump(ofile);
    }
    ofile << "</products>" << endl << "<users>" << endl;
    for(vector<User*>::iterator it = users_.begin(); it != users_.end(); it++){
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;



}

