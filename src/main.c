#include "GenericTraits.h"
#include "quick_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int main(int argc, char const *argv[]) {

  // Open the input and output files, use stdin and stdout if not configured.
  FILE *output = NULL;
  int outputGiven = (argc >= 3);
  if (!outputGiven)
    output = stdout;
  else
    output = fopen(argv[2], "w");

  FILE *input = NULL;
  int inputGiven = (argc >= 2);
  if (!inputGiven)
    input = stdin;
  else
    input = fopen(argv[1], "r");

  // Read the type of the object.
  char type[MAX_LEN];
  memset(type, 0, MAX_LEN);
  (void)!fscanf(input, "%s\n", type);

  // read the number of objects.
  int n = 0;
  (void)!fscanf(input, "%d\n", &n);

  // Get the constructor of the object.
  Constructor ctor = get_constructor(type);

  

  // Read the following n objects from the input.
  // Initialize them using prototype.
  GenericTraits **array[n];
  char tmp[MAX_LEN];
  for (int i = 0; i < n; i++) {
    memset(tmp, 0, MAX_LEN);
    (void)!fgets(tmp, MAX_LEN, input);
	// VERIFY that tmp is expected
	// must be ** in an element
	// ctor returns Int* which is analogous to GT** upon creation
	array[i] = ctor(tmp);
  }

  // Sort n objects.
  quick_sort(array, n);

  // Print n objects to output using dump.
  for (int i = 0; i < n; i++) {
	(*(array[i]))->dump(array[i], output);
  }

  /* Your code here to de-allocate the memories we have allocated. */
  for (int i = 0; i < n; i++) {
	(*(array[i]))->drop(array[i]);
  }


  // Close the files we opened.
  if (outputGiven)
    fclose(output);
  if (inputGiven)
    fclose(input);
  return 0;
}
