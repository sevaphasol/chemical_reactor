#pragma once

#include "gfx/core/event.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/widget.hpp"

namespace reactor {
namespace view {

class ScrollBar : public gfx::ui::Widget {
  public:
    ScrollBar( const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size );

    gfx::core::Vector2f
    clampThumbPosition( const gfx::core::Vector2f& vector );

    void
    onThumbMove( float vertical_delta );
    void
    onArrowClick( bool is_up );

    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

    double
    getScrollFactor() const;

  private:
    void
    updateThumbPosition();

  private:
    enum PartCode {
        Thumb     = 0,
        UpArrow   = 1,
        DownArrow = 2,
    };

    gfx::core::RectangleShape border_;

    gfx::core::Vector2f thumb_size_;
    gfx::core::Vector2f arrow_size_;

    double scroll_factor_ = 0.0;
};

class Thumb : public gfx::ui::Widget {
  public:
    Thumb( ScrollBar* owner, const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size );

    bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;
    bool
    onMousePressSelf( const gfx::core::Event::MouseButtonEvent& event ) override;
    bool
    onMouseMoveSelf( const gfx::core::Event::MouseMoveEvent& event ) override;
    bool
    onMouseReleaseSelf( const gfx::core::Event::MouseButtonEvent& event ) override;

    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    void
    updateVisuals();

  private:
    ScrollBar* owner_;

    gfx::core::RectangleShape rect_;
};

class Arrow : public gfx::ui::Widget {
  public:
    Arrow( ScrollBar*                 owner,
           const gfx::core::Vector2f& pos,
           const gfx::core::Vector2f& size,
           bool                       is_up );

    bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;
    bool
    onMousePressSelf( const gfx::core::Event::MouseButtonEvent& event ) override;
    bool
    onMouseMoveSelf( const gfx::core::Event::MouseMoveEvent& event ) override;
    bool
    onMouseReleaseSelf( const gfx::core::Event::MouseButtonEvent& event ) override;

    void
    setUpTriangle();

    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    void
    updateTriangleColor( const gfx::core::Color& color );
    void
    updateTrianglePosition( const gfx::core::Vector2f vertices[3] );
    void
    updateVisuals();

  private:
    ScrollBar* owner_;

    bool is_up_;

    gfx::core::RectangleShape rect_;
    gfx::core::Vertex         triangle_[3];
};

} // namespace view
} // namespace reactor
