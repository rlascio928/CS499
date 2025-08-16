#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//Grocery Program class
class GroceryProgram {
private:
	vector<string> groceryProduct; //private member to hold the list

public:
	//Functions 
	//This function opens the input file and creates the list
	void GroceryTracking() {
		ifstream productsFS;
		string groceryItem;

		productsFS.open("CS210_Project_Three_Input_File.txt");

		if (!productsFS.is_open()) {
			cout << "Could not open the file" << endl;
		}
		else {
			getline(productsFS, groceryItem);
			while (!productsFS.fail()) {
				groceryProduct.push_back(groceryItem);
				getline(productsFS, groceryItem);
			}

			productsFS.close();
		}

	}
	//function to create the backup list with frquencies
	void GroceryBackup() {
		ofstream productsOS("frequency.dat");

		if (!productsOS) {
			cout << "Could not open the backup file" << endl;
			return;
		}

		unordered_map<string, int> frequency;

		for (const string& word : groceryProduct) {
			frequency[word]++;
		}
		for (const string& word : groceryProduct) {
			productsOS << word << " " << frequency[word] << endl;
		}

		productsOS.close();

	}
	//function to output the entire list and each word's frequency
	void GroceryOutput() {
		unordered_map<string, int> frequency;

		for (const string& word : groceryProduct) {
			frequency[word]++;
		}
		for (const string& word : groceryProduct) {
			cout << word << " " << frequency[word] << endl;
		}
	}
	//function to output the user's word and it's frequency
	void GrocerySearch(const string& searchWord) const {
		int num_list = 0;
		for (const string& product : groceryProduct) {
			if (product == searchWord) {
				num_list += 1;
			}
		}
		cout << searchWord << " " << num_list << endl;
	}

	//function to create the histogram
	void GroceryHistogram() {
		unordered_map<string, int> frequency;

		for (const string& word : groceryProduct) {
			frequency[word]++;
		}
		for (const string& word : groceryProduct) {
			cout << word << " " << frequency[word] << " ";
			cout << string(frequency[word], '$') << endl;
		}
	}
};

//main function 
int main() {
	GroceryProgram program;
	string searchWord;
	unsigned int menuChoice;

	program.GroceryTracking();
	program.GroceryBackup();

	//prints the menu
	cout << ("Menu Options:\n");
	cout << ("-------------\n");
	cout << ("Option 1: Alllows you to search for a specific product and return the frequency.\n");
	cout << ("Option 2: Allow you to print the frequency of all items purchased.\n");
	cout << ("Option 3: Will diplay a frequency histogram for all items purchased.\n");
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
