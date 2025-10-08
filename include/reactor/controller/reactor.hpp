#pragma once

#include "reactor/model/reactor.hpp"
#include "reactor/view/button_panel.hpp"

namespace reactor {
namespace controller {

class Reactor {
  public:
    explicit Reactor( model::Reactor& model );
    ~Reactor() = default;

    void
    onAddMolecule();
    void
    onRemoveMolecule();
    void
    onMovePistonLeft();
    void
    onMovePistonRight();
    void
    onScroll( double scroll_factor );

  private:
    model::Reactor& model_;
};

} // namespace controller
} // namespace reactor
