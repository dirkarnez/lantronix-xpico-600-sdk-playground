#ifndef PSRAM_SECTIONS_H
#define PSRAM_SECTIONS_H

#define PSRAM_CACHE_START_ADDR             0x28800000U

#define __SECTION(type, bank)              __attribute__((section(".$" #bank "." #type)))
#define __NOINIT(bank)                     __SECTION(noinit, bank)
#define __BSS(bank)                        __SECTION(bss, bank)
#define __DATA(bank)                       __SECTION(data, bank)

#endif
