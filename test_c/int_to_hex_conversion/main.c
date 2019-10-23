#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void convert(int16_t from, int16_t to, char * s);
int16_t b2_shift(int16_t val);

int main(int argc, char **argv)
{
    uint16_t data[10] = {0,0,0,6,0,8,0,9,1,0};
    char str_data[12];

    int16_t len = sizeof(data)/sizeof(data[0]);
    int16_t i_str_data = 0;
    int16_t jump_zero_at_start = 0;
    printf("len = %d\n", len);

    for(int16_t i_data = 0; i_data <= len-1; i_data++){
        if(0 != data[i_data] || 1 == jump_zero_at_start){
            jump_zero_at_start = 1;
            str_data[i_str_data] = (char)(data[i_data] + '0');
            i_str_data++;
        }
    }
    str_data[i_str_data] = '\0';
    
    printf("str data = %s\n", str_data);
    convert(10, 16, str_data);

    return 0;
}

void convert(int16_t from, int16_t to, char * s)
{
    
    //only do base 2 to base 36 (digit represented by characters 0-Z)"
    if (from < 2 || from > 36 || to < 2 || to > 36) { 
        return; 
    }
    
    //convert string to an array of integer digits representing number in base:from
    int16_t static il = sizeof(s)/sizeof(s[0]) - 1; // remove the \0 in the counting

    int16_t fs[il];
    int16_t k = 0;
    for (int16_t i = il - 1; i >= 0; i--)
    {   
        printf("c %c\n", s[i]);
        if (s[i] >= '0' && s[i] <= '9') {
            fs[k++] = (int16_t)(s[i] - '0');
        }
        else
        {
            if (s[i] >= 'A' && s[i] <= 'Z') { 
                fs[k++] = 10 + (int16_t)(s[i] - 'A'); 
            }
            else return; //only allow 0-9 A-Z characters
        }
    }

    int16_t ol = il * (from / to+1);
    int16_t ts[ol+10]; //assign accumulation array
    int16_t cums[ol+10]; //assign the result array
    ts[0] = 1; //initialize array with number 1 
    
    //evaluate the output
    for (int16_t i = 0; i < il; i++) //for each input digit
    {
        for (int16_t j = 0; j < ol; j++) //add the input digit 
            // times (base:to from^i) to the output cumulator
        {
            cums[j] += ts[j] * fs[i];
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
        for (int16_t i = il - 1; i >= 0; i--)
        {   
            printf("cums %d\n", cums[i]);
        }
        printf("cums----------\n");
        
        //calculate the next power from^i) in base:to format
        for (int16_t j = 0; j < ol; j++)
        {
            ts[j] = ts[j] * from;
        } 
        for(int16_t j=0;j<ol;j++) //check for any remainders
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
    
    for (int16_t i = il - 1; i >= 0; i--)
    {   
        printf("cums %d\n", cums[i]);
    }
    
    //convert the output to string format (digits 0,to-1 converted to 0-Z characters) 
    char sout[8] = "/0";
    int16_t first = 0; //leading zero flag
    for (int i = ol ; i >= 0; i--)
    {
        if (cums[i] != 0) { first = 1; }
        if (!first) { continue; }
        if (cums[i] < 10) { 
            sout[i] = (char)(cums[i] + '0'); 
        }
        else { 
            sout[i] = (char)(cums[i] + 'A'-10); 
        }
    }
    printf("hex data = %s\n", sout);
}

int16_t b2_shift(int16_t val){
    int16_t shifted_val = (val & 1) << 7 | 
        (val & 2) << 5 | 
        (val & 4) << 3 | 
        (val & 8) << 1 | 
        (val & 16) >> 1 | 
        (val & 32) >> 3 | 
        (val & 64) >> 5 | 
        (val & 128) >> 7;

    return shifted_val;
}
