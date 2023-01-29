#ifndef UTILS
#define UTILS

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "toolbox.h"

//====================== HEADER =========================//

void Initialize();
void Finish();
double measure_interval(char* element);
void print_matrix(matrix* M);
void print_array(array* arr);
void print (const char* format, ...);
void dimension(matrix* m);

//=======================================================//
#endif