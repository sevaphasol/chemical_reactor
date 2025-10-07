#include "gfx/core/event.hpp"
#include "gfx/core/mouse.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "reactor/view/button.hpp"
#include "reactor/config.hpp"

namespace reactor {
namespace view {

Button::Button( const gfx::core::Vector2f& pos, const gfx::core::Vector2f& size )
    : Widget( pos, size ), background_( size ),
      label_( "", font_, config::Reactor::ButtonPanel::Common::Font::Size )
{
    background_.setFillColor( config::Reactor::ButtonPanel::Common::Parameters::Color::Default );
    label_.setFillColor( config::Reactor::ButtonPanel::Common::Font::Color );
    label_.moveInCenterOfRect( size );
    updateVisuals();
}

void
Button::setRelPos( const gfx::core::Vector2f& pos )
{
    setPosition( pos );
    label_.moveInCenterOfRect( size_ );
}

void
Button::setSize( const gfx::core::Vector2f& size )
{
    size_ = size;
    background_.setSize( size );
    label_.moveInCenterOfRect( size );
}

void
Button::setLabelText( const std::string& text )
{
    label_.setString( text );
}

void
Button::setLabelFont( const gfx::core::Font& font, size_t size )
{
    label_.setFont( font );
    label_.setCharacterSize( size );
}

void
Button::setBackgroundColor( const gfx::core::Color& color )
{
    background_.setFillColor( color );
}

bool
Button::isPressed() const
{
    return is_pressed_;
}

bool
Button::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    return false;
}

bool
Button::onMousePressSelf( const gfx::core::Event::MouseButtonEvent& event )
{
    if ( isHoveredSelf() && event.button == gfx::core::Mouse::Left )
    {
        is_pressed_ = true;
        updateVisuals();
        return true;
    }

    return false;
}

bool
Button::onMouseReleaseSelf( const gfx::core::Event::MouseButtonEvent& event )
{
    is_pressed_ = false;
    updateVisuals();
    return isHoveredSelf();
}

bool
Button::onMouseMoveSelf( const gfx::core::Event::MouseMoveEvent& event )
{
    is_hovered_self_ = pointInside( gfx::core::Vector2f( event.x, event.y ) );

    if ( !is_hovered_self_ )
    {
        is_pressed_ = false;
    }

    updateVisuals();
    return isHoveredSelf();
}

void
Button::updateVisuals()
{
    if ( is_pressed_ )
    {
        background_.setFillColor(
            config::Reactor::ButtonPanel::Common::Parameters::Color::Pressed );
    } else if ( isHoveredSelf() )
    {
        background_.setFillColor( config::Reactor::ButtonPanel::Common::Parameters::Color::Hover );
    } else
    {
        background_.setFillColor(
            config::Reactor::ButtonPanel::Common::Parameters::Color::Default );
    }
}

void
Button::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( background_, transform );
    window.draw( label_, transform );
}

} // namespace view
} // namespace reactor
