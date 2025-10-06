#pragma once

#include "gfx/ui/widget.hpp"

#include "reactor/model/reactor.hpp"
#include "reactor/view/molecule.hpp"

#include <vector>
#include <memory>

namespace reactor {
namespace view {

class Reactor : public gfx::ui::Widget {
  public:
    explicit Reactor( model::Reactor& model );
    virtual ~Reactor() = default;

    void
    update() override;
    void
    onIdle( const gfx::core::Event& event ) override;

  private:
    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    model::Reactor&                        model_ref_;
    std::vector<std::unique_ptr<Molecule>> molecule_views_;
    gfx::core::RectangleShape              border_;
};

} // namespace view
} // namespace reactor
