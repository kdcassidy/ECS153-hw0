#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "GenericTraits.h"

/// Use `DECLARE_STRUCT` to declare the struct in less than 5 lines.
DECLARE_STRUCT(Rectangle, {
	GenericTraits *impl;
	int height;
	int width;
})


#endif