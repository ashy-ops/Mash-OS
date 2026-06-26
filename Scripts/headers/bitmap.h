#pragma once

#include <stdint.h>
#include <stdbool.h>


#define WORD_SIZE uint64_t
#define PAGE_SIZE 4096
#define BPW (sizeof(WORD_SIZE) * 8) //bits per word

typedef struct
{
    WORD_SIZE *map;
    uint32_t word_cnt;

} BITMAP;

bool bitmap_bit_free(BITMAP *bmp, uint32_t bit);
void bitmap_set(BITMAP *bmp, uint32_t bit);

//returns the starting page number of the contiguous memory asked for 
bool bitmap_set_range(BITMAP *bmp, uint32_t page_cnt, uint32_t *page_strt);

//initializes bitmap and reserves space for itself
void bitmap_init(BITMAP *bmp, WORD_SIZE base_addr, WORD_SIZE free_ram_bits);
