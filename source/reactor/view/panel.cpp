#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "reactor/config.hpp"
#include "reactor/view/panel.hpp"
#include "reactor/controller/reactor.hpp"
#include "reactor/view/button.hpp"

#include <memory>

namespace reactor {
namespace view {

Panel::Panel( controller::Reactor& controller ) : controller_( controller )
{
    setDraggable( true );

    setPosition( config::Reactor::Panel::Position );
    setSize( config::Reactor::Panel::Size );

    border_.setSize( getSize() );
    border_.setFillColor( gfx::core::Color::Transparent );
    border_.setOutlineColor( gfx::core::Color::Red );
    border_.setOutlineThickness( 2.0f );

    loadFont();

    setupButton( config::Reactor::Panel::Buttons::AddMolecule::Position, "Add molecule" );

    setupButton( config::Reactor::Panel::Buttons::RemoveMolecule::Position, "Remove molecule" );

    setupButton( config::Reactor::Panel::Buttons::MovePiston::Left::Position, "Move piston left" );

    setupButton( config::Reactor::Panel::Buttons::MovePiston::Right::Position,
                 "Move piston right" );
}

bool
Panel::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    if ( isPressed( ButtonCode::AddMolecule ) )
    {
        controller_.onAddMolecule();
    }

    if ( isPressed( ButtonCode::RmMolecule ) )
    {
        controller_.onRemoveMolecule();
    }

    if ( isPressed( ButtonCode::MovePistonLeft ) )
    {
        controller_.onMovePistonLeft();
    }

    if ( isPressed( ButtonCode::MovePistonRight ) )
    {
        controller_.onMovePistonRight();
    }

    return false;
}

void
Panel::loadFont()
{
    labels_font_.loadFromFile( config::Common::Font::Name );
}

bool
Panel::isPressed( ButtonCode code )
{
    return dynamic_cast<Button*>( children_[code].get() )->isPressed();
}

void
Panel::setupButton( const gfx::core::Vector2f& pos, const char* label )
{
    auto button = std::make_unique<Button>();

    button->setBackgroundColor( config::Reactor::Panel::Common::Parameters::Color::Default );
    button->setLabelFont( labels_font_, config::Reactor::Panel::Common::Font::Size );
    button->setLabelText( label );
    button->setLabelText( label );
    button->setSize( config::Reactor::Panel::Common::Parameters::Size );
    button->setRelPos( pos );

    addChild( std::move( button ) );
}

void
Panel::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( border_, transform );
}

} // namespace view
} // namespace reactor
