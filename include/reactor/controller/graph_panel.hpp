#pragma once

#include "reactor/model/graph_panel.hpp"

namespace reactor {
namespace controller {

class GraphPanel {
  public:
    explicit GraphPanel( model::GraphPanel& model );

    void
    update( double delta_time, double energy, double number );

  private:
    model::GraphPanel& model_;
};

} // namespace controller
} // namespace reactor
