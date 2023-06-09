#include "GenericTraits.h"
#include <string.h>

#define MAX_TYPES 256
static char *type_names[MAX_TYPES];
static void *(*constructors[MAX_TYPES])(char *);
static void (*destructors[MAX_TYPES])(void *);
static int num_types = 0;

// Return a "constructing function" from a list, specific to desired type
Constructor get_constructor(char *type_name) {
	for (int i = 0; i < num_types; i++) {
		if (!strcmp(type_names[i], type_name)) {
			return constructors[i];
		}
	}
	return NULL;
}
Destructor get_destructor(char *type_name) {
	for (int i = 0; i < num_types; i++) {
		if (!strcmp(type_names[i], type_name)) {
			return destructors[i];
		}
	}
	return NULL;
}

void add_ctor_dtor(char *type_name, Constructor ctor, Destructor dtor) {
	// Error handling
	if (num_types >= MAX_TYPES) {
		fprintf(stderr, "Error: Max num_types exceeded\n");
		return;
	}
	char *type_name_copy = strdup(type_name); // on HEAP, TODO must be freed
	if (type_name_copy == NULL) {
		fprintf(stderr, "Error: No space for type name\n");
		return;
	}

	type_names[num_types] = type_name_copy;
	constructors[num_types] = ctor;
	destructors[num_types] = dtor;

	num_types++;
}
