
#include "xorshift_random.h"

// Seed for the pseudo random number generator
unsigned int random_state = 1804289383; 

unsigned int get_random_U32_number(){
    unsigned int number = random_state;

    //XOR shift algorithm
    number ^= number <<13;
    number ^= number >>17;
    number ^= number <<5;
    
    // Update the state number;
    random_state = number;
    return number;
}

uint64_t get_random_U64_number(){
    uint64_t n1, n2, n3, n4;
    n1 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
    n2 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
    n3 = (uint64_t)(get_random_U32_number()) & 0xFFFF;
    n4 = (uint64_t)(get_random_U32_number()) & 0xFFFF;

    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}