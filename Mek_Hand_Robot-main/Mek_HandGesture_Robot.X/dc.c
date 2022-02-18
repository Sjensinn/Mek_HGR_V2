#include <xc.h>
void DC_stop(){
    LATB &= 0b11100001;           
}
void DC_move(uint8_t direction) {
    //Add PCA code for speed
    switch (direction) {
        case 0: //forward
            LATB &= 0b11110100;
            LATB |= 0b00010100;
            break;
        case 1: //backwards
            LATB &= 0b11101010;
            LATB |= 0b00001010;
            break;
        case 2: //turn left
            LATB &= 0b11110010;
            LATB |= 0b00010010;
            break;
        case 3: //turn right
            LATB &= 0b11101100;
            LATB |= 0b00001100;
            break;
        default:
            LATB &= 0b11100000;
            LATB |= 0b00000000;
            
    }
    //RB0,1,2,3
}