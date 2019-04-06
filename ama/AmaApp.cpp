#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "AmaApp.h"
#include "iProduct.h"
#include "Utilities.h"
#include "Sort.h"

using namespace std;

namespace ama
{
	AmaApp::AmaApp(const char filename[])
	{
		strncpy(m_filename, filename, 256);
		for (int i = 0; i < 100; i++) // set all m_product elements to null
			m_products[i] = nullptr;
		m_noOfProducts = 0;
		loadProductRecords();
	}

	AmaApp::~AmaApp()
	{
		for (int i = 0; i < 100; i++) // delete all m_product elements
			delete m_products[i];
	}

	void clearKeyboard(void) {
		while (getchar() != '\n'); // empty execution code block on purpose
	}

	// pause() waits for the user to hit enter before anything else can be executed
	void AmaApp::pause() const
	{
		cout << "Press Enter to continue..." << endl;
		clearKeyboard();
	}

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

	void AmaApp::loadProductRecords()
	{
		// delete all products from the array (if any)
		for (int i = 0; i < 100; i++)
			if (m_products[i] != nullptr)
				delete m_products[i];

		int readIndex = 0;
		ifstream fin(m_filename);
		fin.open(m_filename);

		if (fin.is_open())
		{
			while (!fin.bad() && !fin.eof())
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
			fin.close();
		}
	}

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
			<< "------------------------------------------------------------------------------------------------" << endl;

		AmaApp::pause();
	}

	void AmaApp::deleteProductRecord(iProduct* product)
	{
		ofstream fout(m_filename);

		if (fout.is_open())
			for (int i = 0; i < m_noOfProducts; i++)
			{
				if (m_products[i] != product)
				{
					m_products[i]->write(fout, write_condensed);
					fout << endl;
				}
			}
	}

	void AmaApp::sort()
	{
		sict::sort(m_products, m_noOfProducts);
	}

	iProduct* AmaApp::find(const char* sku) const
	{
		for (int i = 0; i < m_noOfProducts; i++)
		{
			if (m_products[i]->operator==(sku)) // if there is a match
				return m_products[i];
		}

		return nullptr;                         // if there is no match
	}

	void AmaApp::addQty(iProduct* product)
	{
		int userAns;

		product->write(cout, write_human);
		cout << endl << endl;

		cout << "Please enter the number of purchased items: ";
		cin >> userAns;
		if (cin.fail())
		{
			cin.clear();
			cout << "Invalid quantity value!" << endl;
		}
		else
		{
			int amountRequired = (product->qtyNeeded() - product->qtyAvailable());
			if (userAns <= amountRequired)
				product += userAns;
			else
			{
				cout << "Too many items; only " << amountRequired
					<< "is needed. Please return the extra "
					<< (userAns - amountRequired) << " items." << endl;
			}
		}

		saveProductRecords();
		cout << endl << "Updated!" << endl;
		clearKeyboard();
	}

	void AmaApp::addProduct(char tag)
	{
		m_products[m_noOfProducts] = createInstance(tag);

		if (m_products[m_noOfProducts] != nullptr)           // sucessfully created
		{
			m_products[m_noOfProducts]->read(cin, true);
			if (cin.fail())                                  // unsuccessfully read
			{
				cin.clear();
				cout << endl << m_products[m_noOfProducts] << endl << endl;
			}
			else                                             // successfully read
			{
				saveProductRecords();
				cout << endl << "Success!" << endl << endl;
			}
		}
	}

	int AmaApp::run()
	{
		bool flag = true;

		while (flag)
		{
			int userSelection = menu();
			iProduct* tempProduct = nullptr;
			char userAns[ama::max_length_sku];

			switch (userSelection)
			{
			case (1):
				listProducts();
				break;

			case (2):
				cout << "Please enter the product SKU: ";
				tempProduct = find(userAns);
				if (tempProduct != nullptr)
					tempProduct->write(cout, write_human);
				else
					cout << "No such product!" << endl;

				pause();
				break;

			case (3):
				addProduct('N');
				loadProductRecords();

			case (4):
				addProduct('P');
				loadProductRecords();

			case (5):
				cout << "Please enter the product SKU: ";
				tempProduct = find(userAns);
				if (tempProduct != nullptr)
					addQty(tempProduct);
				else
					cout << "No such product!" << endl << endl;

			case (6):
				cout << "Please enter the product SKU: ";
				tempProduct = find(userAns);
				if (tempProduct != nullptr)
				{
					deleteProductRecord(tempProduct);
					loadProductRecords();
					cout << "Deleted!" << endl;
				}
				else
					cout << "No such product!" << endl;

			case (7):
				sort();
				saveProductRecords();
				cout << "Sorted!" << endl << endl;

			case (0):
				cout << "Goodbye!" << endl;
				return 0;
			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
				break;
			}
		}
	}
}
// TODO: make helper function to read sku
