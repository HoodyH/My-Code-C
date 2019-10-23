#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


uint8_t * convert(int8_t from, int8_t to, int16_t * data, int8_t len);
unsigned char reverse(unsigned char b);
unsigned char reverse_byte(unsigned char x);
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

    uint8_t * hex_string = convert(10, 16, format_data, i_format_data);
    int8_t hex_string_len = sizeof(hex_string)/sizeof(hex_string[0]);

    for(int8_t i_hex = 0; i_hex <= 6; i_hex += 2){
        //printf("ar %d, br %d\n", hex_string[i_hex], hex_string[i_hex+1]);
        uint8_t temp = hex_string[i_hex];
        hex_string[i_hex] = reverse(hex_string[i_hex+1]);
        hex_string[i_hex+1] = reverse(temp);
        //printf("ac %d, bc %d\n", hex_string[i_hex], hex_string[i_hex+1]);
    }

    char out[10];
    for(int8_t i_hex = 0; i_hex < 8; i_hex++){

        if (hex_string[i_hex] < 10) { 
            out[i_hex] = (char)(hex_string[i_hex] + '0'); 
        }
        else { 
            out[i_hex] = (char)(hex_string[i_hex] + 'A'-10); 
        }
    }

     printf("hex data = %s\n", out);

    return 0;
}

unsigned char reverse(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    b = b >> 4;
    return b;
}

unsigned char reverse_byte(unsigned char x)
{
    static const unsigned char table[] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
    };
    return table[x];
}

/*
you need to send as input a reversed int array and is len
*/
uint8_t * convert(int8_t from, int8_t to, int16_t * data, int8_t len)
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
