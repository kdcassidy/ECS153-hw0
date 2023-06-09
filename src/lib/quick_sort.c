#include "quick_sort.h"
#include "GenericTraits.h"


int partition(GenericTraits **array[], int left, int right) {
	GenericTraits **pivot = array[left];
	int i = left;

	for (int j = left + 1; j <= right; j++) {
		if ((*(array[j]))->cmp(array[j], pivot) > 0) { // Swap if L > R (for descending ?)
			i++;
			GenericTraits **tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;			
		}
	}

	GenericTraits **tmp = array[i];
	array[i] = array[left];
	array[left] = tmp;
	return i;
}

void quick_sort_recursive(GenericTraits **array[], int left, int right) {
	if (left < right) {
		int p = partition(array, left, right);
		quick_sort_recursive(array, left, p);
		quick_sort_recursive(array, p + 1, right);
	}
}

void quick_sort(GenericTraits **array[], int n) { //wrapper
	quick_sort_recursive(array, 0, n-1);
}
