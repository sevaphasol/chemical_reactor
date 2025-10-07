#include "reactor/model/graph_panel.hpp"

namespace reactor {
namespace model {

void
GraphPanel::updateEnergyGraph( double x, double y )
{
    energy_graph_.addPoint( x, y );
}

void
GraphPanel::updateNumberGraph( double x, double y )
{
    number_graph_.addPoint( x, y );
}

Graph&
GraphPanel::getEnergyModel()
{
    return energy_graph_;
}

Graph&
GraphPanel::getNumberModel()
{
    return number_graph_;
}

} // namespace model
} // namespace reactor
