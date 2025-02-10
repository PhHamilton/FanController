#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <stdint.h>
typedef struct
{
    uint16_t R;
    uint16_t L;
    uint16_t J;
}motor_parameters_t;

typedef struct
{
    uint16_t voltage;
    uint16_t current;
}max_ratings_t;

typedef struct
{
    motor_parameters_t motor_parameters;
    max_ratings_t max_ratings;
}controller_settings_t;

void set_default_parameters(void);
void update_motor_parameters(motor_parameters_t *param);
void update_max_ratings(max_ratings_t *param);
controller_settings_t get_controller_settings(void);

#endif
