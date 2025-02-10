#include "mode_handler.h"

volatile controller_modes_t controller_mode = CONTROLLER_MODE_CONFIG;

controller_modes_t get_controller_mode(void)
{
    return controller_mode;
}

void set_controller_mode(controller_modes_t mode)
{
    controller_mode = mode;
}
