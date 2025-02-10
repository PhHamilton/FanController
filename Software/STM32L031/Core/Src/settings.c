#include "settings.h"

static controller_settings_t settings;

void set_default_parameters(void)
{
    settings.motor_parameters.R = 100;
    settings.motor_parameters.L = 100;
    settings.motor_parameters.J = 100;

    settings.max_ratings.voltage = 12;
    settings.max_ratings.current = 1;
}

void update_motor_parameters(motor_parameters_t *param)
{
    settings.motor_parameters.R = param->R;
    settings.motor_parameters.L = param->L;
    settings.motor_parameters.J = param->J;
}

void update_max_ratings(max_ratings_t *param)
{
    settings.max_ratings.voltage = param->voltage;
    settings.max_ratings.current = param->current;
}
controller_settings_t get_controller_settings(void)
{
    return settings;
}
