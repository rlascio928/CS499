#pragma once

#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>

using namespace std;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

//Grocery Program class
class GroceryProgram {
private:
    mongocxx::client client{mongocxx::uri{"mongodb://127.0.0.1:27017"}};
    mongocxx::database db = client["grocerydb"];
    mongocxx::collection collection = db["items"];
    std::pair<int, double> GetItemSalesData(const std::string& searchWordRaw);

public:
    void GrocerySearch(const string& searchWordRaw);
    void GroceryOutput();
    void GroceryHistogram();
    void GrocerySales();
};