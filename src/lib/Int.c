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
	int_obj->i = (int32_t)atoi(string);
	return int_obj;
}

void dump_Int(void *self, FILE *fp) {
	Int *this = (Int *)self;
	fprintf(fp, "0x%x\n", this->i);
}

int cmp_Int(void *self, void *other) {
	Int *int_self = (Int *)self;
	Int *int_other = (Int *)other;
	if (int_self->i < int_other->i) {
		return -1;
	} else if (int_self->i > int_other->i) {
		return 1;
	} else {
		return 0;
	}
}

void drop_Int(void *self) {
	// Must cast (void *) into (Int *)
	Int *int_self = (Int *)self;
	free(int_self->impl);
	free(int_self);
}

// Struct type must be added to registry of ctors, dtors
void __attribute__((constructor)) register_Int() {
    add_ctor_dtor("Int", new_Int, drop_Int);
}