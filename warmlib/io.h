
#include <cstring>
#include <cinttypes>

volatile uint8_t* const scr_io = (uint8_t*)0x01FFFF00;
uint8_t warm_scr_ptr = 0;
void clear(){
    warm_scr_ptr = 0;
    for(std::size_t i=0; i<0x100; i++){
        scr_io[i] = 0x20;
    }
}
void print(const char* str, size_t size){
    for(std::size_t i=0; i<size; i++){
        if(str[i] == '\n' || str[i] == '\r'){
            warm_scr_ptr = (warm_scr_ptr + 0b00100000) & 0b11100000;
        }else{
            scr_io[warm_scr_ptr++] = str[i];
        }
    }
}
void print(const char* str){
    print(str, strlen(str));
}
void print(const char c){
    print(&c, 1);
}
void print(size_t num, size_t base = 10){
    int digits = 0;
    size_t n = num;
    do { n /= base; digits++; } while (n != 0);
    int d = digits - 1;
    do{
        size_t mod = num % base;
        if(mod >= 10) scr_io[warm_scr_ptr+d] = 'A' + (mod - 10);
        else scr_io[warm_scr_ptr+d] = '0' + mod;
        num /= base;
        d--;
    }while(num!=0);
    warm_scr_ptr += digits;
}

void print(long unsigned int num, size_t base = 10){
    print((size_t)num, base);
}