
#include "Rectangle.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Fix definitions - ported from Human without altering

void *new_Rectangle(char *string) { // TODO proper new
	// Allocate for this Int struct
	Rectangle *rectangle_obj = malloc(sizeof(Rectangle));
	if (rectangle_obj == NULL) {
		fprintf(stderr, "Error: Couldn't create Rectangle struct\n");
		return NULL;
	}

	printf("%s\n", string);

	// Allocate for contained GenericTraits struct
    rectangle_obj->impl = malloc(sizeof(GenericTraits));
    if (rectangle_obj->impl == NULL) {
        fprintf(stderr, "Error: Couldn't create GenericTraits struct\n");
        free(rectangle_obj);
        return NULL;
    }

    // Initialize the GenericTraits struct with Int's functions
    rectangle_obj->impl->new = new_Rectangle;
    rectangle_obj->impl->dump = dump_Rectangle;
    rectangle_obj->impl->cmp = cmp_Rectangle;
    rectangle_obj->impl->drop = drop_Rectangle;

	// Initialize actual rectangle
	return rectangle_obj;
}

void dump_Rectangle(void *self, FILE *fp) { // TODO Proper name dump
	Rectangle *this = (Rectangle *)self;
	fprintf(fp, "%d\n", this->width);
}

int cmp_Rectangle(void *self, void *other) { // TODO Proper comparison
	Rectangle *rectangle_self = (Rectangle *)self;
	Rectangle *rectangle_other = (Rectangle *)other;

	int result = rectangle_other->height + rectangle_self->height;

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	} else {
		return 0;
	}
}



DEFINE_STRUCT(Rectangle)