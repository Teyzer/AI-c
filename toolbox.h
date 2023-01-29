#ifndef TOOLBOX
#define TOOLBOX

#include <stdlib.h>
#include <string.h>
#include <math.h>

//===================== STRUCTURES ========================//
typedef int intc;
typedef double doublec;

struct Vector {intc size; intc capacity; doublec* tab;};
typedef struct Vector vector;
struct Array {intc len; doublec* tab;};
typedef struct Array array;
struct Matrix {intc height; intc width; doublec** tab;}; 
typedef struct Matrix matrix;

//======================= HEADER ==========================//
//----------------------------------------------------------------//
//                              Math                              //
//----------------------------------------------------------------//

doublec sigmoid(doublec x);

//----------------------------------------------------------------//
//                              Vector                            //
//----------------------------------------------------------------//

void vector_map(vector* arr, doublec (*f)(doublec));
void vector_add(vector* arr, doublec x);
void vector_times(vector* arr, doublec x);
doublec vector_dot(vector* A, vector* B);
vector* vector_null();
void append(vector* p, doublec element);
array* vector_to_array(vector* v);

//----------------------------------------------------------------//
//                              Array                             //
//----------------------------------------------------------------//

void array_map(array* arr, doublec (*f)(doublec));
void array_add(array* arr, doublec x);
void array_times(array* arr, doublec x);
doublec array_dot(array* A, array* B);
array* array_null(intc size);
array* array_init(intc size, doublec* tab);

//----------------------------------------------------------------//
//                              Matrix                            //
//----------------------------------------------------------------//

matrix* matrix_init(doublec** arr, intc height, intc width);
matrix* matrix_null(intc height, intc width);
matrix* matrix_map_init(intc height, intc width, doublec (*f)(intc, intc));
matrix* matrix_identity(intc size);
matrix* matrix_product(matrix* A, matrix* B);
matrix* matrix_addition(matrix* A, matrix* B);
void matrix_map(matrix* m, doublec (*f)(doublec));
void matrix_transpose(matrix* m);
matrix* matrix_copy(matrix* m);

//================================================================//

#endif