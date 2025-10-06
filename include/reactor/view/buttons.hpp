#pragma once

#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/ui/widget.hpp"

#include "reactor/view/button.hpp"

namespace reactor {

namespace controller {

class Reactor;

} // namespace controller

namespace view {

class ReactorButtons : public gfx::ui::Widget {
  public:
    explicit ReactorButtons( gfx::core::Vector2f pos, gfx::core::Vector2f size );

    virtual void
    onIdle( const gfx::core::Event& event ) override;

  private:
    enum ButtonCode {
        AddMolecule     = 0,
        RmMolecule      = 1,
        MovePistonLeft  = 2,
        MovePistonRight = 3,
    };

    void
    loadFont();

    bool
    isPressed( ButtonCode code );

    void
    setupButton( const gfx::core::Vector2f& pos, const char* label );

  private:
    controller::Reactor* controller_;

    gfx::core::Font labels_font_;
};

} // namespace view
} // namespace reactor
