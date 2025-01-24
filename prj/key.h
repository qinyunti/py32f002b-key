#ifndef KEY_H
#define KEY_H

#ifdef __cplusplus
    extern "C"{
#endif

#include <stdint.h>

void key_init(void);
void key_deinit(void);
int key_write(uint8_t val);
int key_read(uint8_t* val);

#ifdef __cplusplus
    }
#endif

#endif