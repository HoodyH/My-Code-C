#include <stdio.h>
#include <stdlib.h>


/*
Print a nice matrix on terminal with grid
For better reading
*/
void print_martix(int *matrix, int dim_x, int dim_y)
{
    int i, j, k, out; 
    for (i = 0; i < dim_y+1; i++){

        printf("\n");
        for (k = 0; k < dim_x; k++)
            printf("+----");
        printf("+\n");

        if(i==dim_y)
            break;
        
        printf("|");
        for (j = 0; j < dim_x; j++) {
            out = *((matrix+i*dim_x) + j);
            if(out < 10)
                printf(" %d  |", out); 
            else
                printf(" %d |", out);
        }  
    }
}



int main () {

    int r=5,c=3;
    int **m = malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++) m[i] = malloc(c*sizeof(int));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
        {
            m[i][j] = -1;
        }
        
    }
    

    int w_max = r*c;
    int w=0, i=0, j=0, num=0;

    while (1) {

        while (w < w_max && j<c && m[i][j] == -1) {
            m[i][j] = num;
            w++;
            num++;
            j++;
        }
        j--;
        i++;

        while (w < w_max && i<r && m[i][j] == -1) {
            m[i][j] = num;
            w++;
            num++;
            i++;
        }
        i--;
        j--;

        while (w < w_max && j>=0 && m[i][j] == -1) {
            m[i][j] = num;
            w++;
            num++;
            j--;
        }
        j++;
        i--;

        while (w < w_max && i>=0 && m[i][j] == -1) {
            m[i][j] = num;
            w++;
            num++;
            i--;
        }
        i++;
        j++;


        
        if (w >= w_max) break;
    }
    //print_martix((int *) m, r, c);
   
   for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    
}