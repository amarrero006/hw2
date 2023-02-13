#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                hits.clear();
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                hits.clear();
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
                
                // ADD command will add search result index to users cart.
                // Hit Indexs are decremented to match up with vector indexing.

                else if (cmd == "ADD"){
                    string un; int index;
                    bool flag = false;
                    ss >> un >> index;
                    if(ss.fail()){
                        cout << "Invalid request" << endl;
                        ss.clear();
                    }
                    else{
                        if(index > hits.size() || index < 1){
                            cout << "Invalid request" << endl;
                        }
                        else{
                            for(map<User*, queue<Product*> >::iterator it = ds.carts_.begin(); it != ds.carts_.end(); it++){
                                if(un == it->first->getName()){
                                    flag = true;
                                    it->second.push(hits[index - 1]);
                                }
                            }
                            if(!flag){
                                cout <<"Invalid request" << endl;
                            }
                        }
                    }
                }

                // Viewing the cart requires a temporary queue so we may pop from the front
                // without affecting the acual cart. 

                else if(cmd == "VIEWCART"){
                    string un;
                    bool flag = false;
                    ss>>un;
                    if(ss.fail()){
                        cout << "Invalid username" << endl;
                    }
                    else{
                        int count = 1;
                        for(map<User*, queue<Product*> >::iterator it = ds.carts_.begin(); it!= ds.carts_.end(); it++){
                            if(un == it->first->getName()){
                                flag = true;
                                queue<Product*> temp = it->second;
                               int limit = temp.size();
                                for(int i = 0; i < limit; i++){
                                    //Product* temp2 = temp.front();
                                    cout <<"Item " << count << endl << temp.front() ->displayString() << endl;
                                    count++;
                                    temp.pop();
                                }
                            }
                        }
                        if(!flag){
                            cout <<"Invalid username" << endl;
                        }
                    }
                }

                else if( cmd == "BUYCART"){
                    string un;
                    bool flag = false;
                    ss>>un;
                    for(map<User*, queue<Product*> >::iterator it = ds.carts_.begin(); it!= ds.carts_.end(); it++){
                        if(un == it->first->getName()){
                            flag = true;
                            int size = it->second.size();
                            for(int i = 0; i < size; i++) {
                                if (it->first->getBalance() >= it->second.front()->getPrice() &&
                                    it->second.front()->getQty() > 0) {
                                    it->second.front()->subtractQty(1);
                                    it->first->deductAmount(it->second.front()->getPrice());
                                    it->second.pop();
                                }
                            }
                        }
                    }
                    if(!flag){
                        cout << "Invalid username" << endl;
                    }
                }



            else {
                cout << "Unknown command" << endl;
            }
        }

    }
  
    for(map<Product*, set<string> >::iterator it = ds.inventory_.begin(); it!=ds.inventory_.end(); it++){
        delete (it->first);
    } 

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        cout << "No results found!" << endl;
        return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
