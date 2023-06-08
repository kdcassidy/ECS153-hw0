#include "quick_sort.h"
#include "GenericTraits.h"


int partition(GenericTraits **array, int low, int high) {
	GenericTraits *pivot = array[high];
	int i = low;

	for (int j = low; j < high; j++) {
		if (array[j]->cmp(array[j], pivot) > 0) { // TEST FOR DESCENDING!!!
			GenericTraits *tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;			
		}
	}

	GenericTraits *tmp = array[i];
	array[i] = array[high];
	array[high] = tmp;
	return i;
}

void quick_sort_recursive(GenericTraits **array, int low, int high) {
	if (low < high) {
		int p = partition(array, low, high);
		quick_sort_recursive(array, low, p - 1);
		quick_sort_recursive(array, p + 1, high);
	}
}

void quick_sort(GenericTraits **array[], int n) { //wrapper
	quick_sort_recursive(*array, 0, n-1);
}
