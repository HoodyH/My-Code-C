#include <stdio.h>
#include <stdlib.h>


/*
Init the matrix with all 0
Is not usefull un production but only in development
*/
void init_martix(int *matrix, int dim_x, int dim_y)
{
    int i, j; 
    for (i = 0; i < dim_y; i++)
        for (j = 0; j < dim_x; j++) 
            *((matrix+i*dim_x) + j) = 0; 
}


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


/*
Example

+-------------------+
| 1  | 2  | 3  | 4  |
+-------------------+
| 12 | 13 | 14 | 5  |
+-------------------+
| 11 | 16 | 15 | 6  |
+-------------------+
| 10 | 9  | 8  | 7  |
+-------------------+

Easy way to do what is described above.

*/
void fill_matrix(int dim_x, int dim_y)
{
    /*
    Counter to take track of the concentric rute 
    Every cicle step in by one
    */
    int concentric_position_counter = 0;

    int matrix[dim_x][dim_y];
    init_martix((int *)matrix, dim_x, dim_y);
    int num_counter = 1;

    int i = 0; //indice di spostamento
    int fix_pos;
    
    /*
    Needed to out early the loop in case of a odd matrix
    Normalize the out condition based on the num_counter starting point
    */

    int num_counter_limit = (dim_x*dim_y)+num_counter;
    
    while (1)
    {
        /* 
        move right up to right border - concentric_position_counter
        */
        i = concentric_position_counter;
        fix_pos = concentric_position_counter;
        while(i != dim_x-concentric_position_counter-1)
        {   
            matrix[fix_pos][i] = num_counter;
            i++;
            num_counter++;
        }
        if(num_counter >= num_counter_limit) break;

        /* 
        move down up to bottom border - concentric_position_counter
        */
        i = concentric_position_counter;
        fix_pos = dim_x-concentric_position_counter-1;
        while(i != dim_y-concentric_position_counter-1)
        {
            matrix[i][fix_pos] = num_counter;
            i++;
            num_counter++;
        }
        if(num_counter >= num_counter_limit) break;

        /* 
        move left up to left border - concentric_position_counter
        */
        i = (dim_x-1) - concentric_position_counter;
        fix_pos = (dim_y-1) - concentric_position_counter;
        while(i+1 != concentric_position_counter+1)
        {
            matrix[fix_pos][i] = num_counter;
            i--;
            num_counter++;
        }
        if(num_counter >= num_counter_limit) break;
        
        /* 
        move left up to left border - concentric_position_counter
        */
        i = (dim_y-1)-concentric_position_counter;
        fix_pos = concentric_position_counter;
        while(i+1 != concentric_position_counter+1)
        {
            matrix[i][fix_pos] = num_counter;
            i--;
            num_counter++;
        }
        if(num_counter >= num_counter_limit) break;

        concentric_position_counter++;
    }
    print_martix((int *)matrix, dim_x, dim_y);
}


int main(int argc, char **argv)
{   
    //printf("%d\n", atoi(argv[1]));
    fill_matrix(5, 5);
    return 0;
}