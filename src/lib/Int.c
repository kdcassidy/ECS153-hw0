#include "Int.h"
#include <stdint.h>

void *new_Int(char *string) {
	// Allocate for this Int struct
	Int *int_obj = malloc(sizeof(Int));
	if (int_obj == NULL) {
		fprintf(stderr, "Error: Couldn't create Int struct\n");
		return NULL;
	}

	// Allocate for contained GenericTraits struct
    int_obj->impl = malloc(sizeof(GenericTraits));
    if (int_obj->impl == NULL) {
        fprintf(stderr, "Error: Couldn't create GenericTraits struct\n");
        free(int_obj);
        return NULL;
    }

    // Initialize the GenericTraits struct with Int's functions
    int_obj->impl->new = new_Int;
    int_obj->impl->dump = dump_Int;
    int_obj->impl->cmp = cmp_Int;
    int_obj->impl->drop = drop_Int;

	// Initialize actual int
	int_obj->i = (uint32_t)atoi(string);
	return int_obj;
}

void dump_Int(void *self, FILE *fp) {
	Int *this = (Int *)self;
	fprintf(fp, "0x%X\n", this->i);
}

int cmp_Int(void *self, void *other) {
	Int *int_self = (Int *)self;
	Int *int_other = (Int *)other;
	return int_self->i - int_other->i; // Negative if R > L
}

void drop_Int(void *self) {
	// Must cast (void *) into (Int *)
	Int *int_self = (Int *)self;
	free(int_self->impl);
	free(int_self);
}

// To be called at start of program
// Struct type must be added to registry of ctors, dtors
void register_Int() {
    add_ctor_dtor("Int", new_Int, drop_Int);
}