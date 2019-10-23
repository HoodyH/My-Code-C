#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char rfid_data[14];

uint8_t * convert(int8_t from, int8_t to, uint8_t * data, int8_t len);
unsigned char reverse(unsigned char b);

int main(int argc, char **argv)
{
    uint8_t data[15] = {0,11,2,1,0,0,0,0,6,0,8,0,9,1,0};

    int8_t len = 14; //max dimension of the data
    int8_t data_offset = 5; // the start of badge significative value
    uint8_t format_data[10];

    int8_t i_format_data = 0;
    int8_t zero_counter = 0;
    int8_t jump_zero_at_start = 0;

    //read the product code of the badge
    rfid_data[0] = '0';
    rfid_data[1] = '0';

    /* 
    remove the 0s and invert the data array
    start from 5 where is the firs significative number of the badge id
    */
    for(int8_t i_data = data_offset; i_data <= len; i_data++){
        if(0 == data[i_data] && 0 == jump_zero_at_start){
            zero_counter++;
        } 
        else jump_zero_at_start = 1;
        if(1 == jump_zero_at_start){
            format_data[len - zero_counter - i_format_data++ - data_offset] = data[i_data];
        }
    }

    for(int8_t i = 0; i<i_format_data; i++){
        printf("%d", format_data[i]);
    }
    printf("\n");

    uint8_t * hex_string = convert(10, 16, format_data, i_format_data);
    int8_t hex_string_len = sizeof(hex_string)/sizeof(hex_string[0]);

    for(int8_t i_hex = 0; i_hex <= 6; i_hex += 2){
        //printf("ar %d, br %d\n", hex_string[i_hex], hex_string[i_hex+1]);
        uint8_t temp = hex_string[i_hex];
        hex_string[i_hex] = reverse(hex_string[i_hex+1]);
        hex_string[i_hex+1] = reverse(temp);
        //printf("ac %d, bc %d\n", hex_string[i_hex], hex_string[i_hex+1]);
    }

    for(int8_t i_hex = 0; i_hex < 10; i_hex++){
        printf("hex[%d] %d\n",i_hex, hex_string[i_hex]);
        if (hex_string[i_hex] < 10) { 
            rfid_data[i_hex+2] = (char)(hex_string[i_hex] + '0'); 
        }
        else { 
            rfid_data[i_hex+2] = (char)(hex_string[i_hex] + 'A'-10); 
        }
    }
    rfid_data[10] = '\0';

    free(hex_string);

    printf("hex data = %s\n", rfid_data);

    return 0;
}

unsigned char reverse(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    b = b >> 4;
    return b;
}

/*
you need to send as input a reversed int array and is len
*/
uint8_t * convert(int8_t from, int8_t to, uint8_t * data, int8_t len)
{
    
    //only do base 2 to base 36 (digit represented by characters 0-Z)"
    if (from < 2 || from > 36 || to < 2 || to > 36) { 
        return ""; 
    }

    uint8_t ol = len * (from / to+1);
    uint8_t ts[ol+10]; //assign accumulation array
    uint8_t cums[ol+10]; //assign the result array
    ts[0] = 1; //initialize array with number 1 
    
    //evaluate the output
    for (int8_t i = 0; i < len; i++) //for each input digit
    {
        for (int8_t j = 0; j < ol; j++) //add the input digit 
            // times (base:to from^i) to the output cumulator
        {
            cums[j] += ts[j] * data[i];
            uint8_t temp = cums[j];
            uint8_t rem = 0;
            uint8_t ip = j;
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
            uint8_t temp = ts[j];
            uint8_t rem = 0;
            uint8_t ip = j;
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
    uint8_t * out_data = malloc( sizeof(uint8_t) * ol);
    int8_t i_out_data = 0;
    int8_t jump_zero_at_start = 0;

    /*
    reverse the data without coverting it in a readable way
    */
    for (int8_t i_cums = ol ; i_cums >= 0; i_cums--)
    {   
        out_data[i_out_data++] = cums[i_cums];
    }
    out_data[i_out_data] = '\0';
    return out_data;
}
