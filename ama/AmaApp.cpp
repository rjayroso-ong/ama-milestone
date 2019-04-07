/*===========================================================================\\
||                             AmaApp.cpp                                    ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   07/04/2019                                                        ||
\\===========================================================================*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "AmaApp.h"
#include "Utilities.h"
#include "Sort.h"

using namespace std;

namespace ama
{
	AmaApp::AmaApp(const char filename[])
	{
		strncpy(m_filename, filename, 256);
		for (int i = 0; i < 100; i++)     // set all m_product elements to null
			m_products[i] = nullptr;
		m_noOfProducts = 0;
		loadProductRecords();
	}

	AmaApp::~AmaApp()
	{
		for (int i = 0; i < 100; i++)     // delete all m_product elements
			delete m_products[i];
	}

	// pause() waits for the user to hit enter before anything else can be executed
	void AmaApp::pause() const
	{
		cout << "Press Enter to continue..." << endl;
		clearKeyboard();
	}

	// menu() displays the menu and returns the user's input slection as an int
	int AmaApp::menu() const
	{
		int userAns;

		cout << "Disaster Aid Supply Management Program" << endl
			<< "--------------------------------------" << endl
			<< "1- List products" << endl
			<< "2- Search product" << endl
			<< "3- Add non-perishable product" << endl
			<< "4- Add perishable product" << endl
			<< "5- Add to product quantity" << endl
			<< "6- Delete product" << endl
			<< "7- Sort products" << endl
			<< "0- Exit program" << endl
			<< "> ";

		cin >> userAns;
		clearKeyboard();
		if (userAns >= 0 && userAns <= 7)
			return userAns;
		else
			return -1; // selection is invalid
	}

	// loadProductRecords() opens a file for reading and stores the data into m_products
	void AmaApp::loadProductRecords()
	{
		// delete all products from the array (if any)
		for (int i = 0; i < 100; i++)
			if (m_products[i] != nullptr)
			{
				delete m_products[i]; 
				m_products[i] = nullptr;
			}
				
		int readIndex = 0;
		ifstream fin;
		fin.open(m_filename);

		if (fin.is_open())
		{
			while (fin.good())
			{
				// read the product tag
				char productTag = fin.get();

				// create an iProduct instance (determined by the productTag)
				iProduct* newProduct = createInstance(productTag);
				if (newProduct != nullptr)
				{
					m_products[readIndex] = newProduct;
					fin.ignore();
					newProduct->read(fin, false); // read the product from the file (non-interactive mode)
					readIndex++;
				}
			}

			m_noOfProducts = readIndex;
		}

		fin.close();
	}

	// saveProductRecords() const loops through m_products and writes them to a file
	void AmaApp::saveProductRecords() const
	{
		ofstream fout(m_filename);

		if (fout.is_open())
			for (int i = 0; i < m_noOfProducts; i++)
			{
				m_products[i]->write(fout, write_condensed);
				fout << endl;
			}
	}

	// listProducts() loops through m_products and displays them in table form
	void AmaApp::listProducts() const
	{
		double total = 0;

		cout << "------------------------------------------------------------------------------------------------" << endl
			 << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl
			 << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;

		for (int i = 0; i < m_noOfProducts; i++)
		{
			cout << "|";
			cout.width(4);
			cout << right << (i + 1) << " |";
			m_products[i]->write(cout, write_table);
			cout << endl;
			total += m_products[i]->total_cost();
		}

		cout << "------------------------------------------------------------------------------------------------" << endl
			 << "|                                                      Total cost of support ($): | ";
		cout.width(10);
		cout << right << fixed << setprecision(2) << total << " |" << endl
			 << "------------------------------------------------------------------------------------------------" << endl
			 << endl;

		pause(); // before the list ends, pause for user <enter> input
	}

	/* deleteProductRecord() finds the parameter product in m_products, and 
	   deletes it by excluding it from being saved to the file              */
	void AmaApp::deleteProductRecord(iProduct* product)
	{
		ofstream fout(m_filename);

		if (fout.is_open())
			for (int i = 0; i < m_noOfProducts; i++)
				if (m_products[i] != product)
				{
					m_products[i]->write(fout, write_condensed);
					fout << endl;
				}
	}

	// sort() calls upon sict::sort to bubble sort m_products in ascending order
	void AmaApp::sort()
	{
		sict::sort(m_products, m_noOfProducts);
	}

	/* find() loops through m_products and returns a product if it matches the 
	   parameter sku, otherwise returns nullptr                                */
	iProduct* AmaApp::find(const char* sku) const
	{
		for (int i = 0; i < m_noOfProducts; i++)
		{
			if (m_products[i]->operator==(sku)) // if there is a match
				return m_products[i];
		}

		return nullptr;                         // if there is no match
	}

	// addQty() updates the quantity on hand for the iProduct paramater product
	void AmaApp::addQty(iProduct* product)
	{
		int userAns;

		// display the parameter product in human readable form
		product->write(cout, write_human);
		cout << endl << endl;

		cout << "Please enter the number of purchased items: ";
		cin >> userAns;
		if (cin.fail()) // if userAns is INVALID
		{
			cin.clear();
			cout << "Invalid quantity value!" << endl << endl;
		}
		else            // if userAns is valid
		{
			int amountRequired = (product->qtyNeeded() - product->qtyAvailable());
			if (userAns <= amountRequired)
			{
				*product += userAns; 
			}
			else        // if userAns is more than the required amount of items
			{
				*product += amountRequired;
				cout << "Too many items; only " << amountRequired
					<< " is needed. Please return the extra "
					<< (userAns - amountRequired) << " items." << endl;
			}
			cout << endl << "Updated!" << endl << endl;
		}

		saveProductRecords();
		clearKeyboard();
	}

	// addProduct() adds a new product at the end of the array
	void AmaApp::addProduct(char tag)
	{
		m_products[m_noOfProducts] = createInstance(tag);

		if (m_products[m_noOfProducts] != nullptr)           // sucessfully created
		{
			m_products[m_noOfProducts]->read(cin, true);
			if (cin.fail())                                  // unsuccessfully read
			{
				cin.clear();
				clearKeyboard();
				cout << endl << *m_products[m_noOfProducts] << endl << endl;
				m_products[m_noOfProducts] = nullptr;
			}
			else                                             // successfully read
			{
				m_noOfProducts++;
				saveProductRecords();
				cout << endl << "Success!" << endl << endl;
			}
		}
	}

	// run() displays the menu, and calls functions based on the user's input
	int AmaApp::run()
	{
		bool flag = true;

		while (flag)
		{
			int userSelection = menu();
			iProduct* tempProduct = nullptr;
			char userAns[max_length_sku];

			switch (userSelection)
			{
			case (1):
				listProducts();
				break;

			case (2):
				cout << "Please enter the product SKU: ";
				cin >> userAns;
				clearKeyboard();
				tempProduct = find(userAns);
				cout << endl;
				if (tempProduct != nullptr)
				{
					tempProduct->write(cout, write_human);
					cout << endl;
				}
				else
					cout << "No such product!" << endl;

				pause();
				break;

			case (3):
				addProduct('N');
				loadProductRecords();
				break;

			case (4):
				addProduct('P');
				loadProductRecords();
				break;

			case (5):
				cout << "Please enter the product SKU: ";
				cin >> userAns;
				clearKeyboard();
				tempProduct = find(userAns);
				cout << endl;
				if (tempProduct != nullptr)
					addQty(tempProduct);
				else
					cout << "No such product!" << endl << endl;
				break;


			case (6):
				cout << "Please enter the product SKU: ";
				cin >> userAns;
				tempProduct = find(userAns);
				clearKeyboard();
				cout << endl;
				if (tempProduct != nullptr)
				{
					deleteProductRecord(tempProduct);
					loadProductRecords();
					cout << "Deleted!" << endl;
				}
				else
					cout << "No such product!" << endl;

				break;

			case (7):
				sort();
				saveProductRecords();
				cout << "Sorted!" << endl << endl;
				break;

			case (0):
				cout << "Goodbye!" << endl;
				return 0; // sucessful exit

			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
				break;
			}
		}

		return 1;         // unsucessful exit
	}

	// clearKeyboard() clears the user input from any newlines
	void clearKeyboard()
	{
		while (getchar() != '\n');
	}
}