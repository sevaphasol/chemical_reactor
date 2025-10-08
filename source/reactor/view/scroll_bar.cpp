#include "reactor/view/scroll_bar.hpp"
#include "gfx/core/color.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/primitive_type.hpp"
#include "gfx/core/rectangle_shape.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/vertex.hpp"
#include "gfx/core/window.hpp"
#include "gfx/ui/widget.hpp"
#include "reactor/config.hpp"

#include <algorithm>
#include <cassert>
#include <memory>

namespace reactor {
namespace view {

Thumb::Thumb( ScrollBar* owner, const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size )
    : gfx::ui::Widget( pos, size ), owner_( owner )
{
    setDraggable( true );

    rect_.setSize( size );
    rect_.setFillColor( config::Reactor::ScrollBar::Thumb::Color::Default );
}

bool
Thumb::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    updateVisuals();

    return false;
}

bool
Thumb::onMousePressSelf( const gfx::core::Event::MouseButtonEvent& event )
{
    if ( isHoveredSelf() && event.button == gfx::core::Mouse::Left )
    {
        is_pressed_  = true;
        is_dragging_ = true;
        gfx::core::Vector2f mouse_pos( event.x, event.y );
        drag_offset_ = mouse_pos - getAbsPos();

        return true;
    }

    return false;
}

bool
Thumb::onMouseMoveSelf( const gfx::core::Event::MouseMoveEvent& event )
{
    gfx::core::Vector2f mouse_pos( event.x, event.y );
    is_hovered_self_ = pointInside( mouse_pos );

    if ( !is_hovered_self_ )
    {
        is_pressed_ = false;
    }

    if ( is_dragging_ )
    {
        auto new_pos = owner_->clampThumbPosition( mouse_pos - getParentAbsPos() - drag_offset_ );
        owner_->onThumbMove( new_pos.y - getRelPos().y );
    }

    return is_hovered_self_;
}

bool
Thumb::onMouseReleaseSelf( const gfx::core::Event::MouseButtonEvent& event )
{
    return Widget::onMouseReleaseSelf( event );
}

void
Thumb::updateVisuals()
{
    if ( is_pressed_ )
    {
        rect_.setFillColor( config::Reactor::ScrollBar::Thumb::Color::Pressed );
    } else if ( isHoveredSelf() )
    {
        rect_.setFillColor( config::Reactor::ScrollBar::Thumb::Color::Hover );
    } else
    {
        rect_.setFillColor( config::Reactor::ScrollBar::Thumb::Color::Default );
    }
}

void
Thumb::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( rect_, transform );
}

Arrow::Arrow( ScrollBar*                 owner,
              const gfx::core::Vector2f& pos,
              const gfx::core::Vector2f& size,
              bool                       is_up )
    : gfx::ui::Widget( pos, size ), is_up_( is_up ), owner_( owner )
{
    rect_.setSize( size );
    rect_.setFillColor( config::Reactor::ScrollBar::ArrowField::Color::Default );

    setUpTriangle();
}

bool
Arrow::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    updateVisuals();

    return false;
}

void
Arrow::setUpTriangle()
{
    updateTriangleColor( config::Reactor::ScrollBar::ArrowField::Triangle::Color::Default );
    updateTrianglePosition();
}

bool
Arrow::onMousePressSelf( const gfx::core::Event::MouseButtonEvent& event )
{
    if ( isHoveredSelf() && event.button == gfx::core::Mouse::Left )
    {
        is_pressed_ = true;

        owner_->onArrowClick( is_up_ );
        return true;
    }

    return false;
}

bool
Arrow::onMouseMoveSelf( const gfx::core::Event::MouseMoveEvent& event )
{
    return Widget::onMouseMoveSelf( event );
}

bool
Arrow::onMouseReleaseSelf( const gfx::core::Event::MouseButtonEvent& event )
{
    return Widget::onMouseReleaseSelf( event );
}

void
Arrow::updateTriangleColor( const gfx::core::Color& color )
{
    for ( auto& vertex : triangle_ )
    {
        vertex.color = color;
    }
}

void
Arrow::updateTrianglePosition()
{
    if ( is_up_ )
    {
        triangle_[0].position = gfx::core::Vector2f( size_.x / 2, size_.y / 3 );
        triangle_[1].position = gfx::core::Vector2f( size_.x / 3, 2 * size_.y / 3 );
        triangle_[2].position = gfx::core::Vector2f( 2 * size_.x / 3, 2 * size_.y / 3 );
    } else
    {
        triangle_[0].position = gfx::core::Vector2f( size_.x / 2, 2 * size_.y / 3 );
        triangle_[1].position = gfx::core::Vector2f( size_.x / 3, size_.y / 3 );
        triangle_[2].position = gfx::core::Vector2f( 2 * size_.x / 3, size_.y / 3 );
    }
}

void
Arrow::updateVisuals()
{
    if ( is_pressed_ )
    {
        rect_.setFillColor( config::Reactor::ScrollBar::ArrowField::Color::Pressed );
        updateTriangleColor( config::Reactor::ScrollBar::ArrowField::Triangle::Color::Pressed );
    } else if ( isHoveredSelf() )
    {
        rect_.setFillColor( config::Reactor::ScrollBar::ArrowField::Color::Hover );
        updateTriangleColor( config::Reactor::ScrollBar::ArrowField::Triangle::Color::Hover );
    } else
    {
        rect_.setFillColor( config::Reactor::ScrollBar::ArrowField::Color::Default );
        updateTriangleColor( config::Reactor::ScrollBar::ArrowField::Triangle::Color::Default );
    }
}

void
Arrow::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( rect_, transform );
    window.draw( triangle_, 3, gfx::core::PrimitiveType::Triangles, transform );
}

ScrollBar::ScrollBar( const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size )
    : gfx::ui::Widget( pos, size ),
      thumb_size_( size.x, size.y * config::Reactor::ScrollBar::Thumb::SizeCoef ),
      arrow_size_( size.x, size.y * config::Reactor::ScrollBar::ArrowField::SizeCoef )

{
    addChild( std::make_unique<view::Thumb>( this,
                                             config::Reactor::ScrollBar::Thumb::StartPos,
                                             thumb_size_ ) );
    addChild( std::make_unique<view::Arrow>( this,
                                             gfx::core::Vector2f( 0.0f, 0.0f ),
                                             arrow_size_,
                                             true ) );
    addChild( std::make_unique<view::Arrow>(
        this,
        gfx::core::Vector2f( 0.0f,
                             size.y * ( 1 - config::Reactor::ScrollBar::ArrowField::SizeCoef ) ),
        arrow_size_,
        false ) );

    border_.setSize( getSize() );
    border_.setFillColor( gfx::core::Color( 64, 64, 64, 128 ) );
    border_.setOutlineColor( gfx::core::Color( 32, 32, 32 ) );
    border_.setOutlineThickness( 4.0f );
}

double
ScrollBar::getScrollFactor() const
{
    return scroll_factor_;
}

bool
ScrollBar::isScrolled()
{
    if ( is_scrolled_ )
    {
        is_scrolled_ = false;
        return true;
    }

    return false;
}

gfx::core::Vector2f
ScrollBar::clampThumbPosition( const gfx::core::Vector2f& vector )
{
    return { std::clamp( vector.x, 0.0f, size_.x - thumb_size_.x ),
             std::clamp( vector.y, arrow_size_.y, size_.y - thumb_size_.y - arrow_size_.y ) };
}

void
ScrollBar::onThumbMove( float vertical_delta )
{
    float norm_delta = vertical_delta / ( size_.y - thumb_size_.y - 2 * arrow_size_.y );

    scroll_factor_ = std::clamp( scroll_factor_ - norm_delta, 0.0, 1.0 );

    is_scrolled_ = true;

    updateThumbPosition();
}

void
ScrollBar::onArrowClick( bool is_up )
{
    scroll_factor_ = std::clamp( scroll_factor_ + ( is_up ? 0.1 : -0.1 ), 0.0, 1.0 );

    is_scrolled_ = true;

    updateThumbPosition();
}

void
ScrollBar::updateThumbPosition()
{
    float thumb_y =
        arrow_size_.y + ( 1 - scroll_factor_ ) * ( size_.y - thumb_size_.y - 2 * arrow_size_.y );

    children_[PartCode::Thumb]->setRelPos( gfx::core::Vector2f( 0.0, thumb_y ) );
}

void
ScrollBar::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( border_, transform );
}

} // namespace view
} // namespace reactor
