#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "toolbox.h"

// void f(intc n) {
//     for (int i = 0; i < n; i++) {
        
//     }
// }

doublec h(intc a, intc b) {
    return (b + 3 * a + 1);
}

doublec g(intc a, intc b) {
    return a + b + 1;
}

int main() {

    // Laisse toujours cette fonction
    Initialize();

    FILE *fp=NULL;
    fp=fopen("circle.txt","w");
    double r;
    double x,y,x0,y0;
    printf("Enter the radius of the circle to be plotted: ");
    scanf("%lf",&r);
    printf("Enter the x and y-coordinates of the center: ");
    scanf("%lf%lf",&x0,&y0);
    for(y=y0-r;y<=y0+r;y=y+0.1){
        x=sqrt(r*r-(y-y0)*(y-y0))+x0; 
        fprintf(fp,"%lf\t %lf\n",x,y);
    }
    for(y=y0+r;y>=y0-r;y=y-0.1){
        x=-sqrt(r*r-(y-y0)*(y-y0))+x0; 
        fprintf(fp,"%lf\t %lf\n",x,y);
    }
    


    // Laisse là toujours aussi
    Finish();

}

//================================================================//