#include "virtual_marker.h"

SideSensorState virtual_marker_state, virtual_marker_state_volatile;

void virtual_marker_init()
{
    sidesensor_init();
}

void virtual_marker_start()
{
    sidesensor_start();
    virtual_marker_set();
}

void virtual_marker_main()
{
    /* virtual_main */
    sidesensor_main();
    virtual_marker_set();
}

void virtual_marker_stop()
{
    sidesensor_stop();
}

void virtual_marker_set()
{
    virtual_marker_state = sidesensor_read_markerstate();
    virtual_marker_state_volatile = sidesensor_read_markerstate_volatile();
}

SideSensorState virtual_marker_read_markerstate()
{
    return virtual_marker_state;
}

SideSensorState virtual_marker_read_markerstate_volatile()
{
    /*
    if(course_read_section_degree() / course_read_sampling_count() >= THRESHOLD_YAW_CURVE_OR_STRAIGHT)
    {
        virtual_marker_state_volatile = curve;
    }
    */
    return virtual_marker_state_volatile;
}

void virtual_marker_d_print()
{

}
