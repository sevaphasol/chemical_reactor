#pragma once

namespace application {

struct ReactorState
{
    ReactorState() : elapsed_time( 0 ), full_energy( 0 ), n_molecules( 0 ) {};

    float elapsed_time;
    float full_energy;
    float n_molecules;
};

} // namespace application
