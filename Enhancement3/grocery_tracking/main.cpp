#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

//Grocery Program class
class GroceryProgram {
private:
    mongocxx::client client{mongocxx::uri{"mongodb://127.0.0.1:27017"}};
    mongocxx::database db = client["grocerydb"];
    mongocxx::collection collection = db["items"];

public:

    //takes the user's input word and searches through the database for the item and counts each time that specific item is in the database
	void GrocerySearch(const string& searchWord) {
		document filter{};
        filter << "item" << searchWord; 

        int count = static_cast<int>(collection.count_documents(filter.view()));
        cout << searchWord << " " << count << endl;
    }

	//function to output the entire list and each word's frequency
	void GroceryOutput() {
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
            cout << pair.first << " " << pair.second << endl;
        }
    }

	//function to create the histogram
	void GroceryHistogram() {
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
};

//main function 
int main() {
    mongocxx::instance inst{};

	GroceryProgram program;
	string searchWord;
	unsigned int menuChoice;

	//prints the menu
	cout << ("Menu Options:\n");
	cout << ("-------------\n");
	cout << ("Option 1: Search for a specific product and return the frequency.\n");
	cout << ("Option 2: Print the frequency of all items purchased.\n");
	cout << ("Option 3: Will display a frequency histogram for all items purchased.\n");
	cout << ("Option 4: Exits the program.\n");
	cout << ("Please select the numerical option menu you would like to display.\n");
	cin >> menuChoice;

	//menu loop 
	if (0 < menuChoice <= 4) {
		while (menuChoice != 4) {
			//Menu Option One
			if (menuChoice == 1) {
				cout << "Enter a grocery item to search\n" << endl;
				cin.ignore(); //ignores the newline
				cin >> searchWord;
				program.GrocerySearch(searchWord);
			}

			//Menu Option Two
			else if (menuChoice == 2) {
				program.GroceryOutput();
			}
			//Menu Option Three
			else if (menuChoice == 3) {
				program.GroceryHistogram();
			}
			else {
				cout << "That is not a valid choice.\n";
			}

			cout << "\nEnter a new menu choice\n";
			cin >> menuChoice;
		}
		//Menu Option Four
		cout << "Exiting. Thank you.";

    }
}


