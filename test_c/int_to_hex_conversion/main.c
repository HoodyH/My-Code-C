#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


char * convert(int8_t from, int8_t to, int16_t * data, int8_t len);
int8_t b2_shift(int8_t val);

int main(int argc, char **argv)
{
    int8_t data[10] = {0,0,0,6,0,8,0,9,1,0};
    int16_t format_data[10];

    int8_t len = sizeof(data)/sizeof(data[0]);
    int8_t i_format_data = 0;
    int8_t zero_counter = 0;
    int8_t jump_zero_at_start = 0;

    for(int8_t i_data = 0; i_data <= len; i_data++){
        if(0 == data[i_data] && 0 == jump_zero_at_start){
            zero_counter++;
        } 
        else jump_zero_at_start = 1;
        if(1 == jump_zero_at_start){
            format_data[len - zero_counter - i_format_data++ - 1] = (int16_t)data[i_data];
        }
    }
    i_format_data--; //remove the last post increment

    convert(10, 16, format_data, i_format_data);

    return 0;
}

/*
you need to send as input a reversed int array and is len
*/
char * convert(int8_t from, int8_t to, int16_t * data, int8_t len)
{
    
    //only do base 2 to base 36 (digit represented by characters 0-Z)"
    if (from < 2 || from > 36 || to < 2 || to > 36) { 
        return ""; 
    }

    int16_t ol = len * (from / to+1);
    int16_t ts[ol+10]; //assign accumulation array
    int16_t cums[ol+10]; //assign the result array
    ts[0] = 1; //initialize array with number 1 
    
    //evaluate the output
    for (int8_t i = 0; i < len; i++) //for each input digit
    {
        for (int8_t j = 0; j < ol; j++) //add the input digit 
            // times (base:to from^i) to the output cumulator
        {
            cums[j] += ts[j] * data[i];
            int16_t temp = cums[j];
            int16_t rem = 0;
            int16_t ip = j;
            do // fix up any remainders in base:to
            {
                rem = temp / to;
                cums[ip] = temp-rem*to; ip++;
                cums[ip] += rem;
                temp = cums[ip];
            }
            while (temp >=to);
        }
        
        //calculate the next power from^i) in base:to format
        for (int8_t j = 0; j < ol; j++)
        {
            ts[j] = ts[j] * from;
        } 
        for(int8_t j=0;j<ol;j++) //check for any remainders
        {
            int16_t temp = ts[j];
            int16_t rem = 0;
            int16_t ip = j;
            do  //fix up any remainders
            {
                rem = temp / to;
                ts[ip] = temp - rem * to; ip++;
                ts[ip] += rem;
                temp = ts[ip];
            }
            while (temp >= to);
        }
    }
    
    //convert the output to string format (digits 0, to-1 converted to 0-Z characters) 
    char * out_data = malloc( sizeof(char) * ol);
    int8_t i_out_data = 0;
    int8_t jump_zero_at_start = 0;

    for (int8_t i_cums = ol ; i_cums >= 0; i_cums--)
    {   
        printf("cums %d\n", cums[i_cums]);
        if(0 != cums[i_cums] || 1 == jump_zero_at_start){
            jump_zero_at_start = 1;
            if (cums[i_cums] < 10) { 
                out_data[i_out_data++] = (char)(cums[i_cums] + '0'); 
            }
            else { 
                out_data[i_out_data++] = (char)(cums[i_cums] + 'A'-10); 
            }
        }
    }
    out_data[i_out_data] = '\0';
    printf("hex data = %s\n", out_data);
    return out_data;
}

int8_t b2_shift(int8_t val){
    int8_t shifted_val = (val & 1) << 7 | 
        (val & 2) << 5 | 
        (val & 4) << 3 | 
        (val & 8) << 1 | 
        (val & 16) >> 1 | 
        (val & 32) >> 3 | 
        (val & 64) >> 5 | 
        (val & 128) >> 7;

    return shifted_val;
}
