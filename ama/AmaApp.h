/*===========================================================================\\
||                                AmaApp.h                                   ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   07/04/2019                                                        ||
\\===========================================================================*/
#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H

#include "iProduct.h"

namespace ama
{
	class AmaApp
	{
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;

		AmaApp(const AmaApp& other) = delete;
		AmaApp& operator=(const AmaApp& other) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		void deleteProductRecord(ama::iProduct* product);
		void sort();
		iProduct* find(const char* sku) const;
		void addQty(ama::iProduct* product);
		void addProduct(char tag);

	public:

		AmaApp(const char filename[]);
		~AmaApp();
		int run();
	};

	void clearKeyboard();
}
#endif



