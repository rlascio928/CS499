#include "GroceryProgram.hpp"
#include <iomanip>
#include <limits>

std::pair<int,double> GroceryProgram::GetItemSalesData(const std::string& searchWordRaw) {
	string searchWord = searchWordRaw;

	//convert to lower case
	transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);

	//removes spaces
	searchWord.erase(remove_if(searchWord.begin(), searchWord.end(), ::isspace), searchWord.end());
	
	//removes plurals
	string regexPattern = "^" + searchWord + "(es|s)?$";

	//MongoDB filter usinig case-insensitive regex
	bsoncxx::builder::stream::document filter{};
	filter << "item" << bsoncxx::builder::stream::open_document
			<< "$regex" << regexPattern
			<< "$options" << "i"
			<< bsoncxx::builder::stream::close_document;

    auto cursor = collection.find(filter.view());

    int count = 0;
    double cost = 0.0;
    bool foundCost = false;

    for (auto&& doc: cursor) {
        count++;
        if (!foundCost && doc["cost"]) {
            if(doc["cost"].type() == bsoncxx::type::k_double) {
                cost = doc["cost"].get_double().value;
                foundCost = true;
            }
            else if (doc["cost"].type() == bsoncxx::type::k_int32) {
                cost = static_cast<double>(doc["cost"].get_int32().value);
                foundCost = true;
            }
            else if (doc["cost"].type() == bsoncxx::type::k_int64) {
                cost = static_cast<double>(doc["cost"].get_int64().value);
                foundCost = true;
            }
        }
    }
    return {count, cost};
    }
    void GroceryProgram::GrocerySearch(const string& searchWordRaw) {
        auto [count, _] = GetItemSalesData(searchWordRaw);
        cout << searchWordRaw << " " << count << endl;
    }
    
	//function to output the entire list and each word's frequency
	void GroceryProgram::GroceryOutput(SortOption sortOption) {
		unordered_map<string, int> frequency;

        auto cursor = collection.find({});

        for (auto&& doc : cursor) {
            if(doc["item"] && doc["item"].type() == bsoncxx::type::k_string) {
                auto view = doc["item"].get_string().value;
                string product(view.data(), view.size());
                frequency[product]++;
            }
        }

        //Sortable Vector 
        vector<pair<string, int>> items(frequency.begin(), frequency.end());

        //Sorts based on the option selected
        switch (sortOption) {
            case SortOption::FrequencyDesc:
                sort(items.begin(), items.end(),
                    [] (const auto& a, const auto& b) {
                        return a.second > b.second;
                    });
                break;
            case SortOption::FrequencyAsc:
                sort(items.begin(), items.end(),
                    [] (const auto& a, const auto& b) {
                        return a.second < b.second;
                    });
                break;
            case SortOption::Alphabetical:
                sort(items.begin(), items.end(),
                    [](const auto& a, const auto& b) {
                        return a.first < b.first;
                    });
                break;
        }

        for (const auto& pair : items) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

	//function to create the histogram
	void GroceryProgram::GroceryHistogram() {
        unordered_map<string, int> frequency;

        auto cursor = collection.find({});
        for (auto&& doc : cursor) {
            if(doc["item"] && doc["item"].type() == bsoncxx::type::k_string) {
                auto view = doc["item"].get_string().value;
                string product(view.data(), view.size());
                frequency[product]++;
            }
        }
        for (const auto& pair : frequency) {
            cout << pair.first << " " << pair.second << " ";
            cout << string(pair.second, '$') << endl;
        }
    }

    void GroceryProgram::GrocerySales() {
        string searchWordRaw;
        cout << "\nEnter an item to calculate the total sales:\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin,searchWordRaw);

        auto [count, cost] = GetItemSalesData(searchWordRaw);
        double totalSales = count * cost;

        cout << fixed << setprecision(2);
        cout << count << " sold at $" << cost << " each\n";
        cout << "Total Sales: $" << totalSales << endl << endl;
    }	