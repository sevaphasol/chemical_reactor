#pragma once

#include "gfx/core/font.hpp"
#include "gfx/ui/widget.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/text.hpp"
#include "reactor/config.hpp"

namespace reactor {
namespace view {

class Button : public gfx::ui::Widget {
  public:
    explicit Button(
        const gfx::core::Vector2f& pos  = { 0, 0 },
        const gfx::core::Vector2f& size = config::Reactor::ButtonPanel::Common::Parameters::Size );

    void
    setRelPos( const gfx::core::Vector2f& pos ) override;
    void
    setSize( const gfx::core::Vector2f& size ) override;

    void
    setLabelText( const std::string& text );
    void
    setLabelFont( const gfx::core::Font& font, size_t size );
    void
    setBackgroundColor( const gfx::core::Color& color );
    bool
    isPressed() const;

    bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;

  private:
    bool
    onMousePressSelf( const gfx::core::Event::MouseButtonEvent& event ) override;
    bool
    onMouseReleaseSelf( const gfx::core::Event::MouseButtonEvent& event ) override;
    bool
    onMouseMoveSelf( const gfx::core::Event::MouseMoveEvent& event ) override;
    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;
    void
    updateVisuals();

    gfx::core::RectangleShape background_;
    gfx::core::Font           font_;
    gfx::core::Text           label_;
};

} // namespace view
} // namespace reactor
