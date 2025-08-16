#include <iostream>
#include <string>
#include <limits>
#include "GroceryProgram.hpp"

using namespace std;

//main function 
int main() {
    mongocxx::instance inst{};
	GroceryProgram program;

	string searchWord;
	int menuChoice = 0;

	//prints the menu
	while(true) {
		cout << ("Menu Options:\n");
		cout << ("-------------\n");
		cout << ("Option 1: Search for a specific product and return the frequency.\n");
		cout << ("Option 2: Print the frequency of all items purchased.\n");
		cout << ("Option 3: Will display a frequency histogram for all items purchased.\n");
		cout << ("Option 4: Display total grocery sales.\n");
		cout << ("Option 5: Exits the program.\n");
		cout << ("\nPlease enter the numerical option menu you would like to display.\n");
		
		if(!(cin >> menuChoice)) {
			cout << "That is not a valid choice. Please try again.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	//menu loop 
	
		//Menu Option One
		if (menuChoice == 1) {
			cout << "Enter a grocery item to search" << endl;
			cout << "Type 'back' to return to the menu.\n";
			cin.ignore(); //ignores the newline
			while (true) {
				cout << "\nSerach for:";
				getline(cin, searchWord);

				if (searchWord == "back") {
					break;
				}
				program.GrocerySearch(searchWord);
			}
		}

		//Menu Option Two
		else if (menuChoice == 2) {
			program.GroceryOutput();
		}
		//Menu Option Three
		else if (menuChoice == 3) {
			program.GroceryHistogram();
		}
		else if (menuChoice == 4) {
			program.GrocerySales();
		}
		else if (menuChoice == 5) {
			cout << "Exiting. Thank you" << endl;
			break;
		}
		else {
			cout << "That is not a valid choice. Please enter a valid option\n";
		}

    }

	return 0;
}


