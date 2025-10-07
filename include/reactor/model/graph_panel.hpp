#pragma once

#include "reactor/model/graph.hpp"

namespace reactor {
namespace model {

class GraphPanel {
  public:
    explicit GraphPanel() = default;

    void
    updateEnergyGraph( double x, double y );

    void
    updateNumberGraph( double x, double y );

    Graph&
    getEnergyModel();

    Graph&
    getNumberModel();

  private:
    Graph energy_graph_;
    Graph number_graph_;
};

} // namespace model
} // namespace reactor
