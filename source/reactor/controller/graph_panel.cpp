#include "reactor/controller/graph_panel.hpp"

namespace reactor {
namespace controller {

GraphPanel::GraphPanel( model::GraphPanel& model ) : model_( model ) {}

void
GraphPanel::update( double delta_time, double energy, double number )
{
    static float time = 0.0f;

    model_.updateEnergyGraph( time, energy );
    model_.updateEnergyGraph( time, number );

    time += delta_time;
}

} // namespace controller
} // namespace reactor
