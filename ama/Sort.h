/*===========================================================================\\
||                                Sort.h                                     ||
|| Author: Royce Ayroso-Ong                                                  ||
|| Email:  rjayroso-ong@myseneca.ca                                          ||
|| ID:     115813180                                                         ||
|| Date:   06/04/2019                                                        ||
\\===========================================================================*/
#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict
{
	// sort() bubble sorts the data parameter in ascending order
	template <typename T>
	void sort(T* data, int size)
	{
		int i, j;
		T temp;

		for (i = size - 1; i > 0; i--)
			for (j = 0; j < i; j++) 
				if (*data[j] > *data[j + 1]) 
				{
					temp = data[j];
					data[j] = data[j + 1];
					data[j + 1] = temp;
				}
	}
}

#endif