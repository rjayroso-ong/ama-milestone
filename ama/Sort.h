#ifndef SICT_SORT_H
#define SICT_SORT_H

namespace sict
{
	template <typename T>
	void sort(T* data, int size)
	{
		int i, j;
		T temp;

		for (i = size - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {
				if (data[j] > data[j + 1]) {
					temp = data[j];
					data[j] = data[j + 1];
					data[j + 1] = temp;
				}
			}
		}
	}
}

#endif