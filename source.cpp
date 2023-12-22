/*Name: Ethan Johnson
Date: December 10, 2023
Project Name: Final Project
Project Description: This program is an online christmas shopping market. It starts by having the user create a username and password. 
Then, it asks the user to enter which person they are shopping for. The respective wishlist will be shown.
It lists items to purchase and allows for multiple items to be purchased. The items will be added to a cart via a file, and displayed after the order is complete.
A receipt will be shown at the end with the opportunity to win a discount.*/

#include<string>
#include<cmath>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<vector>
#include<ctype.h>

using namespace std;

double taxFunction(double);
double totalFunction(double, double);
double discountFunction(int, double);

const int ROWS = 3, COLS = 3;

int main() {

	char upgradeChoice1, upgradeChoice2, extraItem;
	int itemChoice, discountGuess;
	string gameType, username, password, item1 = "Shirt", item2 = "Video Game", item3 = "Candle", shirtSize, word, personChoice,
		listNames[ROWS] = { "Brother", "Sister", "Friend" },
		shoppingList[ROWS][COLS] = {
	{"XL Shirt", "Deluxe Video Game", "candle"},
	{"S Shirt", "Standard Video Game", "candle"},
	{"M Shirt", "Collector's Video Game", "candle"} };
	double item1Price = 34.99, item2Price = 59.99, item3Price = 24.99, deluxePrice = 79.99, collectorsPrice = 99.99, subtotal = 0, taxAmount = 0, total = 0, discountedTotal = 0;
	ifstream cartI("cart.txt");
	ofstream cartO("cart.txt");


	cout << "Welcome to MarketOnline! Here for all of your online Christmas shopping needs.";
	cout << "\n\nFirst, you must create an account. Please enter a username: ";
	getline(cin, username);
	
	for (int i = 0; i < username.length(); i++) {
		while (isspace(username[i]) != 0) {
			cout << "\nPlease enter a new username without spaces. Username: ";
			getline(cin, username);
		}
	}

	cout << "\nThank you!";
	cout << "\n\nNow, please enter a password: ";
	getline(cin, password);

	for (int i = 0; i < password.length(); i++) {
		while (isspace(password[i]) != 0) {
			cout << "\nPlease enter a new password without spaces. Password: ";
			getline(cin, password);
		}
	}

	cout << "\nThank you. Your account is created.";

	cartO << "Cart:";

	cout << "\n\nEnter the person you are shopping for (Brother, Sister, or Friend): ";
	cin >> personChoice;

		if (personChoice == "Brother" || personChoice == "brother") {
			cout << "\nShopping List: ";
			for (int i = 0; i < COLS; i++) {
				cout << ' ' << shoppingList[0][i] << endl;
			}
		}
		else if (personChoice == "Sister" || personChoice == "sister") {
			cout << "\nShopping List: ";
			for (int i = 0; i < COLS; i++) {
				cout << ' ' << shoppingList[1][i] << endl;
			}
		}
		else if (personChoice == "Friend" || personChoice == "friend") {
			cout << "\nShopping List: ";
			for (int i = 0; i < COLS; i++) {
				cout << ' ' << shoppingList[2][i] << endl;
			}
		}
		else {
			cout << "\nSorry, you entered an invalid person.";
		}

		cout << "\nItems for sale are listed below:" << fixed << setprecision(2);
		cout << "\n\n1. " << item1 << setw(31) << '$' << item1Price;
		cout << "\n2. " << item2 << setw(26) << '$' << item2Price;
		cout << "\n3. " << item3 << setw(30) << '$' << item3Price;

		do {
			cout << "\n\nEnter the number of the item you'd like to add to your cart: ";
			cin >> itemChoice;

			switch (itemChoice) {
			case 1: // shirt
				cout << "\nPlease enter your shirt size (XS, S, M, L, XL, XXL): ";
				cin >> shirtSize;
				cout << endl << shirtSize << " Shirt added to cart.";
				cartO << endl << shirtSize << " shirt" << endl;
				subtotal += item1Price;
				break;
			case 2: // video game
				cout << "\nWould you like to upgrade your game version? Enter \"Y\" for yes or \"N\" for no: ";
				cin >> upgradeChoice1;
				if (upgradeChoice1 == 'Y' || upgradeChoice1 == 'y') {
					cout << "\nThe deluxe version is $" << deluxePrice << " and includes the DLC season pass. Would you like to upgrade to the collector's addition for a total of $" << collectorsPrice << " which includes a limited edition collectible figure? Enter \"Y\" for yes or \"N\" for no: ";
					cin >> upgradeChoice2;
					if (upgradeChoice2 == 'Y' || upgradeChoice2 == 'y') {
						subtotal += collectorsPrice;
						gameType = "Collector's";
					}
					else {
						subtotal += deluxePrice;
						gameType = "Deluxe";
					}
				}
				else {
					subtotal += item2Price;
					gameType = "Standard";
				}
				cout << endl << gameType << " edition video game added to cart.";
				cartO << endl << gameType << " edition video game" << endl;
				break;
			case 3: // candle
				cout << "\nCandle added to cart.";
				cartO << endl << "Candle" << endl;
				subtotal += item3Price;
				break;
			default: // invalid
				cout << "\nYou entered an invalid item number. Please enter a valid number that corresponds to the items listed above: ";
				cin >> itemChoice;
			}
			cout << "\n\nWould you like to purchase another item? Enter \"Y\" for yes or \"N\" for no: ";
			cin >> extraItem;

		} while (extraItem == 'Y' || extraItem == 'y');

		taxAmount = taxFunction(subtotal);
		total = totalFunction(subtotal, taxAmount);

		cout << endl;
			while (cartI >> word) {
				cout << word << ' ';
			}

		cout << "\n\n~*~*~ Receipt ~*~*~";
		cout << "\nSubtotal: " << setw(29) << '$' << subtotal;
		cout << "\nTax: " << setw(34) << '$' << taxAmount;
		cout << "\nTotal: " << setw(32) << '$' << total;

		cout << "\n\nEnter the answer to 2+2 for 10% off: ";
		cin >> discountGuess;

		discountedTotal = discountFunction(discountGuess, total);

		cartO.close();
		cartI.close();

	cout << endl << endl;
	system("pause");
	return 0;
}

double taxFunction(double subtotal) {
	double taxAmount;
	
	taxAmount = subtotal * .07;

	return taxAmount;
}

double totalFunction(double subtotal, double taxAmount) {
	double total;

	total = subtotal + taxAmount;

	return total;
}

double discountFunction(int discountGuess, double total) {
	double discountedTotal;

	if (discountGuess == 4) {
		discountedTotal = total * .90;
		cout << "\nCorrect! Your new total is $" << discountedTotal;
	}
	else {
		discountedTotal = total;
		cout << "\nIncorrect. Your total will remain at $" << total;
	}

	return discountedTotal;
}