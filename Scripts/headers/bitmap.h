#pragma once

#include <stdint.h>
#include <stdbool.h>


#define WORD_SIZE uint64_t //in bytes
#define PAGE_SIZE 4096
#define BPW (sizeof(WORD_SIZE) * 8) //bits per word

typedef struct
{
    WORD_SIZE *map;      // Pointer to bitmap storage
    uint32_t word_cnt;   // Number of 64-bit words allocated for bitmap
    uint32_t total_pages;   // Actual number of physical pages managed
    uint32_t free_page;     //The latest free page position (to prevent it from scanning from the start)
} BITMAP;

bool bitmap_bit_free(BITMAP *bmp, uint32_t page_num);


void bitmap_set(BITMAP *bmp, uint32_t page_num);
void bitmap_unset(BITMAP *bmp, uint32_t page_num);
//returns the starting page number of the contiguous memory asked for 
bool bitmap_set_range(BITMAP *bmp, uint32_t page_cnt, uint32_t *page_strt);
void bitmap_unset_range(BITMAP *bmp, uint32_t page_start,uint32_t page_cnt);

//initializes bitmap and reserves space for itself
void bitmap_init(BITMAP *bmp, WORD_SIZE base_addr, WORD_SIZE free_ram_bits);
