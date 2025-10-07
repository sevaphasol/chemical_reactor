#pragma once

#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/ui/widget.hpp"

namespace reactor {

namespace controller {

class Reactor;

} // namespace controller

namespace view {

class Panel : public gfx::ui::Widget {
  public:
    explicit Panel( controller::Reactor& controller );

    virtual bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;

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

    virtual void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    controller::Reactor& controller_;

    gfx::core::RectangleShape border_;

    gfx::core::Font labels_font_;
};

} // namespace view
} // namespace reactor
