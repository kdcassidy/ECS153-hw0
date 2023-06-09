#ifndef HUMAN_H
#define HUMAN_H

#include "GenericTraits.h"
#include <stdint.h>
#include <stdlib.h>

DECLARE_STRUCT(Human, {		
	GenericTraits *impl;	
	char name[256];		
})							

#endif