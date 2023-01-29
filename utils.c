#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include "toolbox.h"
#include "utils.h"


//=====================- GLOBAL VARIABLES ========================//
#define default_precision 0

clock_t starting_time;
clock_t checkpoint_time;

const char detection_char = ':';

const char* color_black = "\033[30m";
const char* color_red = "\033[31m";
const char* color_green = "\033[32m";
const char* color_yellow = "\033[33m";
const char* color_blue = "\033[34m";
const char* color_purple = "\033[35m";
const char* color_cyan = "\033[36m";
const char* color_white = "\033[37m";

const intc temp_int = 0;
const doublec temp_double = 0.0;
const char* temp_string = "";
const char temp_char = '0';

//========================= FUNCTIONS ===========================//
//Start timer
void Initialize() {
    starting_time = clock();
}

void Finish() {
    clock_t now = clock();
    printf("The program took %f seconds to execute\n", (double)(now - starting_time) / CLOCKS_PER_SEC);
}

//Measure time passed since intialize
double measure_interval(char* element) {
    printf("%s\n", element);
}

// Print the matrix
void print_matrix(matrix* M) {

    for (int i = 0; i < M->height; i++) {
        
        if (i == 0) {
            printf("[[");
        } else {
            printf(" [");
        }

        for (int j = 0; j < M->width; j++) {

            printf("%.*f", default_precision, M->tab[i][j]);

            if (j != M->width - 1) {
                printf(", ");
            }

        }

        if (i == M->height - 1) {
            printf("]]\n");
        } else {
            printf("]\n");
        }
    }

}

void print_array(array* arr) {
    printf("[");
    for (int i = 0; i < arr -> len; i++) {
        printf("%.*f", default_precision, (arr -> tab)[i]);
        if (i != arr -> len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void print(const char* format, ...)
{
    int length = strlen(format);
    
    va_list args;
    va_start(args, format);

    for (int i = 0; i < length; i++) {
        
        char current_char = format[i];

        if (current_char == detection_char && i != length - 1) {
            
            char next_char = format[i + 1];
            i = i + 1;
            
            switch (next_char) {
                case 'b':
                    printf("%s", color_black);
                    break;
                case 'r':
                    printf("%s", color_red);
                    break;
                case 'g':
                    printf("%s", color_green);
                    break;
                case 'y':
                    printf("%s", color_yellow);
                    break;
                case 'B':
                    printf("%s", color_blue);
                    break;
                case 'p':
                    printf("%s", color_purple);
                    break;
                case 'c':
                    printf("%s", color_cyan);
                    break;
                case 'w':
                    printf("%s", color_white);
                    break;
            }

        } else if (current_char == '%' && i != length - 1) {

            char selector = format[i + 1];
            i = i + 1;

            switch (selector) {
                case 'd':
                    printf("%d", (intc)va_arg(args, intc));
                    break;
                case 'f':
                    printf("%.*f", default_precision, (doublec)va_arg(args, doublec));
                    break;
                case 's':
                    printf("%s", (char*)va_arg(args, char*));
                    break;
                case 'c':
                    printf("%c", (char)va_arg(args, int)); // le va_arg(args,int) est bien voulu
                    break;
            }

        } else if (current_char == '\0') {
            break;
        } else {

            printf("%c", current_char);

        }
        
    }

    printf("\n");

}

// Print the dimensions of the matrix
void dimension(matrix* m){
    printf("Dim : (%d, %d)\n", m->width, m->height);
}

//================================================================//