#include <stdint.h>

int parse_instruction32(uint8_t *code) {

}

int parse_instruction16(uint8_t *code) {

}

int parse_instruction(uint8_t *code) {
    uint8_t op = code[1] >> 3;
    if (op >= 0x00 && op <= 0x0B) {
        parse_instruction32(code);
    }
}