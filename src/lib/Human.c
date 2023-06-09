
#include "Human.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *new_Human(char *string) {
	// Allocate for this Int struct
	Human *human_obj = malloc(sizeof(Human));
	if (human_obj == NULL) {
		fprintf(stderr, "Error: Couldn't create Human struct\n");
		return NULL;
	}

	// Allocate for contained GenericTraits struct
    human_obj->impl = malloc(sizeof(GenericTraits));
    if (human_obj->impl == NULL) {
        fprintf(stderr, "Error: Couldn't create GenericTraits struct\n");
        free(human_obj);
        return NULL;
    }

    // Initialize the GenericTraits struct with Int's functions
    human_obj->impl->new = new_Human;
    human_obj->impl->dump = dump_Human;
    human_obj->impl->cmp = cmp_Human;
    human_obj->impl->drop = drop_Human;

	// Initialize actual human
	strcpy(human_obj->name, string);
	int i;
	for (i = 0; i < 255; i++) {
		if (human_obj->name[i] == ' ' || human_obj->name[i] == '\n')
			break;
	}
	human_obj->name[i] = '\0';
	human_obj->name[255] = '\0';
	return human_obj;
}

void dump_Human(void *self, FILE *fp) {
	Human *this = (Human *)self;
	fprintf(fp, "%s\n", this->name);
}

int cmp_Human(void *self, void *other) {
	Human *human_self = (Human *)self;
	Human *human_other = (Human *)other;
	
	int result = strcmp(human_self->name, human_other->name);

	if (result < 0) {
		return -1;
	} else if (result > 0) {
		return 1;
	} else {
		return 0;
	}
}

DEFINE_STRUCT(Human)