#ifndef __MODE_HANDLER_H__
#define __MODE_HANDLER_H__

typedef enum
{
    CONTROLLER_MODE_OFF,
    CONTROLLER_MODE_MEASURING,
    CONTROLLER_MODE_CONFIG
}controller_modes_t;

controller_modes_t get_controller_mode(void);
void set_controller_mode(controller_modes_t mode);

#endif //__MODE_HANDLER_H__
