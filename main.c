#include <stdint.h>

#define RCC_CR      (unsigned long *)0x40021000
#define RCC_PLLCFGR (unsigned long *)0x4002100C
#define RCC_IOPENR  (unsigned long *)0x40021034

#define GPIOA_MODER (unsigned long *)0x50000000
#define GPIOA_ODR   (unsigned long *)0x50000014

#define GPIOC_MODER (unsigned long *)0x50000800
#define GPIOC_IDR   (unsigned long *)0x50000810

uint8_t num = 0x55;
uint8_t num2;

extern void _print_ch(char *ptr);

void print_ch(char ch)
{
    _print_ch(&ch);
}

void main()
{
    /* configure SYSCLK for 64MHz */
#if 0
    /* disable PLL */
    *RCC_CR &= ~0x01000000UL;

    /* wait for RLLRDY to be cleared */
    while ( *RCC_CR & 0x02000000UL );

    /* configure PLL variables */
    /* N=8, M=1, R=2 */
    *RCC_PLLCFGR &= ~0xE0007F70UL;
    *RCC_PLLCFGR |= 0x20000800UL;

    /* turn on PLL */
    *RCC_CR |= 0x01000000UL;

    /* wait for RLLRDY to be set */
    while ( !(*RCC_CR & 0x02000000UL) );

    /* turn on PLLR output */
    *RCC_PLLCFGR |= 0x10000000UL;
#endif

    /* enable register clocks for GPIOA and GPIOC */
    *RCC_IOPENR |= 0x00000005UL;

    /* configure PA5 as output pin */
    *GPIOA_MODER &= ~0x00000C00UL;
    *GPIOA_MODER |= 0x00000400UL;

    /* configure PC13 as input pin */
    *GPIOC_MODER &= ~0x0C000000UL;

    while(1)
    {
        /* check for user button to be pressed */
        if( (*GPIOC_IDR & 0x2000UL) == 0) {
            /* turn LED ON (PA5) */
            *GPIOA_ODR |= 0x20UL;
        } else {
            /* turn LED OFF (PA5) */
            *GPIOA_ODR &= ~0x20UL;
        }

#ifndef NDEBUG
        print_ch('X');
#endif
    }
}
