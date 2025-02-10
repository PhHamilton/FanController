#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#define N_USER_TIMERS 2

typedef struct
{
    uint16_t timer_value;
    uint8_t  timer_enabled;
    uint8_t  timer_ready;
    uint32_t timer_ticks;
} user_timer_param_t;

typedef struct
{
    user_timer_param_t parameters[N_USER_TIMERS];
} user_timer_t;

typedef enum
{
    UART_TIMER,
    CONFIG_LED_TIMER
} timers_t;

uint8_t init_timers(void);
uint8_t enable_timer(timers_t timer_number);
uint8_t timer_enabled(timers_t timer_number);
uint8_t disable_timer(timers_t timer_number);
uint8_t timer_ready(timers_t timer_number);
uint8_t reset_timer(timers_t timer_number);
uint8_t configure_timer(timers_t timer_number, uint16_t time_ms);
void timer_handler(void);

#endif //__TIMER_H__
