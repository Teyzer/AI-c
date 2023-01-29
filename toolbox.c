#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "toolbox.h"

//=====================- GLOBAL VARIABLES ========================//
#define INIT_CAPACITY 1 // cf empty
#define EPSILON 1e-9




//========================= STRUCTURES ===========================//
//----------------------------------------------------------------//
//                              Math                              //
//----------------------------------------------------------------//

// Sigmoid function to be used with map
doublec sigmoid(doublec x){
    return (doublec)(1/(1 + exp(-x)));
}

//----------------------------------------------------------------//
//                              Vector                            //
//----------------------------------------------------------------//
/* Vectors are dynamic arrays with a size and capacity*/

// Map function to vector
void vector_map(vector* arr, doublec (*f)(doublec)) {
    for (int i = 0; i  < arr -> size; i++) {
        arr -> tab[i] = f(arr -> tab[i]);
    }
}

//Scalar add to vector
void vector_add(vector* arr, doublec x){
    for(int i= 0; i < arr->size; i++) {
        (arr -> tab)[i] = 1 + (arr -> tab)[i];
    }
}

//Scalar multiply to vector
void vector_times(vector* arr, doublec x){
    for(int i= 0; i < arr -> size; i++) {
        arr -> tab[i] = x * (arr -> tab)[i];
    }
}
// Dot product between two vectors
doublec vector_dot(vector* A, vector* B){
    doublec res = 0;
    assert(A->size == B->size);
    for(int i= 0; i < A->size; i++){
        res += A->tab[i] * B->tab[i];
    }
    return res;
}

// Return empty vector
vector* vector_null(){
    vector* arr = (vector*)malloc(sizeof(vector));
    arr -> size = 0;
    arr -> capacity = INIT_CAPACITY;
    arr -> tab = (doublec*)malloc(sizeof(doublec) * (arr->capacity));
    return arr;
}

// Append to vector
void append(vector* p, doublec element) {
    // Resize the vector if necessary
    if (p -> size == p -> capacity) {
        p -> capacity *= 2;
        p -> tab = (doublec*)realloc(p -> tab, sizeof(doublec*) * p -> capacity);
    }
    p->size++;
    (p->tab)[p->size] = element;
}

array* vector_to_array(vector* v){
    array* arr = (array*)malloc(sizeof(array));
    doublec* tab = (doublec*)malloc(sizeof(doublec) * v->size);
    for(int i = 0; i < v->size; i++){
        tab[i] = v -> tab[i];
    }
    arr-> tab = tab;
    arr-> len = v->size;
    return arr;
}

//----------------------------------------------------------------//
//                              Array                             //
//----------------------------------------------------------------//
/*Arrays is a struct with a doublec* and length*/

// Map function to array
void array_map(array* arr, doublec (*f)(doublec)) {
    for (int i = 0; i  < arr -> len; i++) {
        arr -> tab[i] = f(arr -> tab[i]);
    }
}

//Scalar add to array
void array_add(array* arr, doublec x){
    for(int i= 0; i < arr->len; i++) {
        (arr -> tab)[i] = 1 + (arr -> tab)[i];
    }
}

//Scalar multiply to array
void array_times(array* arr, doublec x){
    for(int i= 0; i < arr -> len; i++) {
        arr -> tab[i] = x * (arr -> tab)[i];
    }
}

// Dot product between two arrays
doublec array_dot(array* A, array* B){
    doublec res = 0;
    assert(A->len == B->len);
    for(int i= 0; i < A->len; i++){
        res += A->tab[i] * B->tab[i];
    }
    return res;
}

// Return empty array
array* array_null(intc size){
    array* arr = (array*)malloc(sizeof(array));
    arr -> len = size;
    arr -> tab = (doublec*)malloc(sizeof(doublec) * (arr -> len));
    for (int i = 0; i < arr -> len; i++) {
        arr -> tab[i] = 0;
    }
    return arr;
}

// Initialize array with given coefficients
array* array_init(intc size, doublec* tab){
    array* arr = (array*)malloc(sizeof(array));
    arr -> len = size;
    arr -> tab = tab;
    return arr;
}

//----------------------------------------------------------------//
//                              Matrix                            //
//----------------------------------------------------------------//
/*Matrix is a struct with doublec** and stores width and height ex :
    [[1 2 3 4]
     [1 2 3 4]
     [1 2 3 4]]
  height = 3, width = 4                                           */

// Return a matrix with the given coefficients
matrix* matrix_init(doublec** arr, intc height, intc width) {
    
    matrix* m = (matrix*)malloc(sizeof(matrix));
    
    m -> height = height;
    m -> width = width;
    m -> tab = arr;

    return m;

}

// Return an empty matrix of size "height * width"
matrix* matrix_null(intc height, intc width) {

    doublec** arr = (doublec**)malloc(sizeof(doublec*) * height);

    for (int i = 0; i < height; i++) {
        arr[i] = (doublec*)malloc(sizeof(doublec) * width); 
        for (int j = 0; j < height; j++) {
            arr[i][j] = 0.0;
        } 
    }
    
    return matrix_init(arr, height, width);
    
}

// Initalize a matrix with every every being the result of f(i, j) (i, j) being the coordinates
matrix* matrix_map_init(intc height, intc width, doublec (*f)(intc, intc)) {

    doublec** arr = (doublec**)malloc(sizeof(doublec*) * height);

    for (int i = 0; i < height; i++) {
        arr[i] = (doublec*)malloc(sizeof(doublec) * width);
        for (int j = 0; j < width; j++) {
            arr[i][j] = f(i, j);
        }
    }

    return matrix_init(arr, height, width);

}

// Return the identity matrix with dimension "size * size"
matrix* matrix_identity(intc size) {

    doublec** arr = (doublec**)malloc(sizeof(doublec*) * size);

    for (int i = 0; i < size; i++) {
        arr[i] = (doublec*)malloc(sizeof(doublec) * size); 
        for (int j = 0; j < size; j++) {
            arr[i][j] = (i == j ? 1.0 : 0.0);
        } 
    }
    
    return matrix_init(arr, size, size);

}

//Product of two matrices
matrix* matrix_product(matrix* A, matrix* B){

    matrix* m = matrix_null(A -> height, B -> width);

    for (int i = 0; i < A -> height; i++) {
        for (int j = 0; j < B -> width; j++) {

            if (abs(A -> tab[i][j]) > EPSILON) {
                for (int k = 0; k < B -> height; k++) {
                    m -> tab[i][j] += A -> tab[i][k] * B -> tab[k][j];
                }
            }

        }
    }

    return m;

}

matrix* matrix_addition(matrix* A, matrix* B) {

    matrix* m = matrix_null(A -> height, A -> width);

    for (int i = 0; i < A -> height; i++) {
        for (int j = 0; j < A -> width; j++) {
            m -> tab[i][j] = A -> tab[i][j] + B -> tab[i][j];
        }
    }

    return m;

}

// Apply a function on every element of the matrix
void matrix_map(matrix* m, doublec (*f)(doublec)) {

    for (int i = 0; i < m -> height; i++) {
        for (int j = 0; j < m -> width; j++) {
            m -> tab[i][j] = f(m -> tab[i][j]);
        }
    }

}

//Transposes the matrix
void matrix_transpose(matrix* m){

    //Allocate memory
    doublec** transposed = (doublec**)malloc(sizeof(doublec*) * m->width);

    for (int i = 0; i < m->width; i++) {
        transposed[i] = (doublec*)malloc(sizeof(doublec) * m->height);
    }

    //Copy
    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++) {
            transposed[j][i] = m->tab[i][j];
        }
    }
    
    //Put in tab
    free(m->tab);
    int temp = m->height;
    m->height = m->width;
    m->width = temp;
    m->tab = transposed;
}

matrix* matrix_copy(matrix* m) {
    
    doublec** copy = (doublec**)malloc(sizeof(doublec*) * (m -> height));

    for (int i = 0; i < m->height; i++) {
        
        copy[i] = (doublec*)malloc(sizeof(doublec) * (m -> width));
        
        for (int j = 0; j < m->width; j++) {
            copy[i][j] = m -> tab[i][j];
        }

    }

    return matrix_init(copy, m -> height, m -> width);

}

//================================================================//