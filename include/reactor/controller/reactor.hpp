#pragma once

#include "reactor/model/reactor.hpp"
#include "reactor/view/panel.hpp"

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

  private:
    model::Reactor& model_ref_;
};

} // namespace controller
} // namespace reactor
