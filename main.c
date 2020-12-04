#include <stdint.h>

#define RCC_CR      (unsigned long *)0x40021000
#define RCC_CFGR    (unsigned long *)0x40021008
#define RCC_PLLCFGR (unsigned long *)0x4002100C
#define RCC_IOPENR  (unsigned long *)0x40021034

#define EXTI        (unsigned long *)0x40021800
#define EXTI_FTSR1   (unsigned long *)0x40021804
#define EXTI_FPR1    (unsigned long *)0x40021810
#define EXTI_EXTICR1 (unsigned long *)0x40021860
#define EXTI_EXTICR2 (unsigned long *)0x40021864
#define EXTI_EXTICR3 (unsigned long *)0x40021868
#define EXTI_EXTICR4 (unsigned long *)0x4002186C
#define EXTI_IMR1    (unsigned long *)0x40021880

#define FLASH_ACR   (unsigned long *)0x40022000

#define GPIOA_MODER (unsigned long *)0x50000000
#define GPIOA_ODR   (unsigned long *)0x50000014

#define GPIOC_MODER (unsigned long *)0x50000800
#define GPIOC_IDR   (unsigned long *)0x50000810

#define STK_CSR     (unsigned long *)0xE000E010
#define STK_RVR     (unsigned long *)0xE000E014
#define STK_CVR     (unsigned long *)0xE000E018

#define NVIC_ISER   (unsigned long *)0xE000E100
#define NVIC_ICER   (unsigned long *)0xE000E180
#define NVIC_ISPR   (unsigned long *)0xE000E200
#define NVIC_ICPR   (unsigned long *)0xE000E280


uint8_t num = 0x55;
uint8_t num2;

extern void _print_ch(char *ptr);

void print_ch(char ch)
{
    _print_ch(&ch);
}

uint32_t ticks;
void systick_handler()
{
    ticks++;
}

void exti4_15_handler()
{
    /* clear the pending interrupt */
    *EXTI_FPR1 |= 0x00002000UL;

    /* toggle LED ON/OFF (PA5) */
    *GPIOA_ODR ^= 0x20UL;
}

uint32_t millis()
{
    return ticks;
}

void delay(int ms)
{
    while (ms > 0)
        if (*STK_CSR & 0x10000UL) ms--;
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

    /* configure SysTick Timer for 1ms */
    *STK_RVR = 63999UL;
    *STK_CVR = 0UL;
    *STK_CSR |= 0x00000007UL;

    /* enable register clocks for GPIOA and GPIOC */
    *RCC_IOPENR |= 0x00000005UL;

    /* configure PA5 as output pin */
    *GPIOA_MODER &= ~0x00000C00UL;
    *GPIOA_MODER |= 0x00000400UL;

    /* configure PC13 as input pin */
    *GPIOC_MODER &= ~0x0C000000UL;

    /* configure PC13 as external interrupt */
    *EXTI_EXTICR4 &= ~0x0000FF00UL;
    *EXTI_EXTICR4 |= 0x00000200UL;

    /* configure EXTI13 to trigger on falling edge */
    *EXTI_FTSR1 |= 0x00002000UL;

    /* unmask the EXTI13 interrupt */
    *EXTI_IMR1 |= 0x00002000UL;

    /* enabling EXTI4-15 interrupt in the NVIC */
    *NVIC_ISER = 0x00000080UL;

    uint32_t last_tick = millis();
    while(1)
    {
        if ((millis() - last_tick) > 1000) {
            /* toggle LED ON/OFF (PA5) */
            //*GPIOA_ODR ^= 0x20UL;
            last_tick = millis();
        }

    }
}
