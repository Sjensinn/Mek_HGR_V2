#include <xc.h>
void DC_stop(){
    LATB &= 0b11110000;           
}
void DC_move(uint8_t direction) {
    //Add PCA code for speed
    switch (direction) {
        case 0: //forward
            LATB &= 0b11111010;
            LATB |= 0b00001010;
            break;
        case 1: //backwards
            LATB &= 0b11110101;
            LATB |= 0b00000101;
            break;
        case 2: //turn left
            LATB &= 0b11111001;
            LATB |= 0b00001001;
            break;
        case 3: //turn right
            LATB &= 0b11110110;
            LATB |= 0b00000110;
            break;
        default:
            LATB &= 0b11110000;
            LATB |= 0b00000000;
            
    }
    //RB0,1,2,3
}