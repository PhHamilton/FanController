#include "timer.h"

volatile user_timer_t timer;

uint8_t init_timers(void)
{
    for(uint8_t i = 0; i < N_USER_TIMERS; i++)
    {
        timer.parameters[i].timer_value = 0;
        timer.parameters[i].timer_enabled = 0;
        timer.parameters[i].timer_ready = 0;
        timer.parameters[i].timer_ticks = 0;
    }
    return 0;
}

uint8_t enable_timer(timers_t timer_number)
{
    if (timer_number >= N_USER_TIMERS) return 1; // Skydda mot ogiltiga index
    timer.parameters[timer_number].timer_enabled = 1;
    return 0;
}

uint8_t timer_enabled(timers_t timer_number)
{
    return timer.parameters[timer_number].timer_enabled;
}

uint8_t disable_timer(timers_t timer_number)
{
    if (timer_number >= N_USER_TIMERS) return 1;
    timer.parameters[timer_number].timer_enabled = 0;
    return 0;
}

uint8_t timer_ready(timers_t timer_number)
{
    if (timer_number >= N_USER_TIMERS) return 0;
    if (timer.parameters[timer_number].timer_ready == 1)
    {
        timer.parameters[timer_number].timer_ready = 0;
        timer.parameters[timer_number].timer_ticks = 0;
        return 1;
    }
    return 0;
}

uint8_t reset_timer(timers_t timer_number)
{
    if (timer_number >= N_USER_TIMERS) return 1;
    timer.parameters[timer_number].timer_value = 0;
    timer.parameters[timer_number].timer_enabled = 0;
    timer.parameters[timer_number].timer_ready = 0;
    timer.parameters[timer_number].timer_ticks = 0;
    return 0;
}

uint8_t configure_timer(timers_t timer_number, uint16_t time_ms)
{
    if (timer_number >= N_USER_TIMERS) return 1;
    timer.parameters[timer_number].timer_value = time_ms;
    timer.parameters[timer_number].timer_ticks = 0;
    return 0;
}

void timer_handler(void)
{
    for(uint8_t i = 0; i < N_USER_TIMERS; i++)
    {
        if (timer.parameters[i].timer_enabled)
        {
            timer.parameters[i].timer_ticks++;
            if (timer.parameters[i].timer_ticks >= timer.parameters[i].timer_value)
            {
                timer.parameters[i].timer_ready = 1;
                timer.parameters[i].timer_ticks = 0;
            }
        }
    }
}
