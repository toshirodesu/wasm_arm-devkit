
#include <cstring>
#include <cinttypes>

volatile uint8_t* const scr_buffer = (uint8_t*)0x001FF00;
uint8_t warm_scr_ptr = 0;
void clear(){
    warm_scr_ptr = 0;
    for(std::size_t i=0; i<0x100; i++){
        scr_buffer[i] = 0x20;
    }
}
void print(const char* str, size_t size){
    for(std::size_t i=0; i<size; i++){
        if(str[i] == '\n' || str[i] == '\r'){
            warm_scr_ptr = (warm_scr_ptr + 0b00100000) & 0b11100000;
        }else{
            scr_buffer[warm_scr_ptr++] = str[i];
        }
    }
}
void print(const char* str){
    print(str, strlen(str));
}