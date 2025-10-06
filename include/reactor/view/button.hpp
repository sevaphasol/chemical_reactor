#pragma once
#include "gfx/ui/button.hpp"
#include "reactor/config.hpp"

namespace reactor {
namespace view {

class Button : public gfx::ui::Button {
  public:
    explicit Button(
        const gfx::core::Vector2f& pos  = { 0, 0 },
        const gfx::core::Vector2f& size = config::Reactor::Buttons::Common::Parameters::Size );

  protected:
    void
    updateVisuals() override;
};

} // namespace view
} // namespace reactor
