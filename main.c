#include <stdint.h>

#define RCC_CR      (unsigned long *)0x40021000
#define RCC_CFGR    (unsigned long *)0x40021008
#define RCC_PLLCFGR (unsigned long *)0x4002100C
#define RCC_IOPENR  (unsigned long *)0x40021034

#define FLASH_ACR   (unsigned long *)0x40022000

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
    /* switch SYSCLK to HSICLK */
    uint32_t rcc_cfgr = *RCC_CFGR;
    rcc_cfgr &= ~0x00000007UL;
    *RCC_CFGR = rcc_cfgr;

    /* configure SYSCLK for 64MHz */

    /* disable PLL */
    *RCC_CR &= ~0x01000000UL;

    /* wait for RLLRDY to be cleared */
    while ( *RCC_CR & 0x02000000UL );

    /* configure PLL variables */
    /* N=8, M=1, R=2 */
//    *RCC_PLLCFGR &= ~0xE0007F70UL;
//    *RCC_PLLCFGR |= 0x20000800UL;
    *RCC_PLLCFGR &= ~0xF0007F73UL;
    *RCC_PLLCFGR |= 0x30000802UL;

    /* turn on PLL */
    *RCC_CR |= 0x01000000UL;

    /* wait for RLLRDY to be set */
    while ( !(*RCC_CR & 0x02000000UL) );

    /* turn on PLLR output */
//    *RCC_PLLCFGR |= 0x10000000UL;

    /* add wait states to FLASH */
    uint32_t flash_acr = *FLASH_ACR;
    flash_acr &= ~0x00000007UL;
    flash_acr |= 0x00000002UL;
    *FLASH_ACR = flash_acr;

    /* wait for latency bits to change */
    while( (*FLASH_ACR & 0x00000007UL) != 0x00000002UL );

    /* switch SYSCLK to PLLRCLK */
    rcc_cfgr = *RCC_CFGR;
    rcc_cfgr &= ~0x00000007UL;
    rcc_cfgr |= 0x00000002UL;
    *RCC_CFGR = rcc_cfgr;

    /* enable register clocks for GPIOA and GPIOC */
    *RCC_IOPENR |= 0x00000005UL;

    /* configure PA5 as output pin */
    *GPIOA_MODER &= ~0x00000C00UL;
    *GPIOA_MODER |= 0x00000400UL;

    /* configure PC13 as input pin */
    *GPIOC_MODER &= ~0x0C000000UL;

    while(1)
    {
        /* turn LED ON (PA5) */
        *GPIOA_ODR |= 0x20UL;

        for(uint32_t i=0; i<1000000; i++);

        /* turn LED OFF (PA5) */
        *GPIOA_ODR &= ~0x20UL;

        for(uint32_t i=0; i<1000000; i++);
    }
}
