#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int main(int argc, char **argv)
{
    uint8_t data[10] = {0,0,0,6,0,8,0,9,1,0};
    char str_data[12];

    int8_t len = sizeof(data)/sizeof(data[0]);
    int8_t i_str_data = 0;
    int8_t jump_zero_at_start = 0;
    printf("len = %d\n", len);

    for(int8_t i_data = 0; i_data <= len-1; i_data++){
        if(0 != data[i_data] || 1 == jump_zero_at_start){
            jump_zero_at_start = 1;
            printf("data[%d] = %d\n", i_data, data[i_data]);
            str_data[i_str_data] = (char)data[i_data];
            i_str_data++;
        }
    }
    str_data[i_str_data] = '\0';

    
    printf("str data = %s\n", str_data);

    return 0;
}

void convert(int from, int to, char * s)
    {
        
        //only do base 2 to base 36 (digit represented by characters 0-Z)"
        if (from < 2 || from > 36 || to < 2 || to > 36) { 
            return; 
        }
        
        //convert string to an array of integer digits representing number in base:from
        uint8_t static il = sizeof(s)/sizeof(s[0]);
        uint8_t fs[il];
        uint8_t k = 0;
        for (uint8_t i = il - 1; i >= 0; i--)
        {
            if (s[i] >= '0' && s[i] <= '9') { fs[k++] = (int)(s[i] - '0'); }
            else
            {
                if (s[i] >= 'A' && s[i] <= 'Z') { fs[k++] = 10 + (int)(s[i] - 'A'); }
                else
                { return ("Error: Input string must only contain any of 
			0-9 or A-Z"); } //only allow 0-9 A-Z characters
            }
        }
        
        //check the input for digits that exceed the allowable for base:from
        foreach(int i in fs)
        {
            if (i >= from) { return ("Error: Not a valid number for this input base"); }
        }
        
        //find how many digits the output needs
        int ol = il * (from / to+1);
        int[] ts = new int[ol+10]; //assign accumulation array
        int[] cums = new int[ol+10]; //assign the result array
        ts[0] = 1; //initialize array with number 1 
        
        //evaluate the output
        for (int i = 0; i < il; i++) //for each input digit
        {
            for (int j = 0; j < ol; j++) //add the input digit 
				// times (base:to from^i) to the output cumulator
            {
                cums[j] += ts[j] * fs[i];
                int temp = cums[j];
                int rem = 0;
                int ip = j;
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
            for (int j = 0; j < ol; j++)
            {
                ts[j] = ts[j] * from;
            } 
            for(int j=0;j<ol;j++) //check for any remainders
            {
                int temp = ts[j];
                int rem = 0;
                int ip = j;
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
        
        //convert the output to string format (digits 0,to-1 converted to 0-Z characters) 
        String sout = String.Empty; //initialize output string
        bool first = false; //leading zero flag
        for (int i = ol ; i >= 0; i--)
        {
            if (cums[i] != 0) { first = true; }
            if (!first) { continue; }
            if (cums[i] < 10) { sout += (char)(cums[i] + '0'); }
            else { sout += (char)(cums[i] + 'A'-10); }
        }
    }