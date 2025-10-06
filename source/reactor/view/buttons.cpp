#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/vector2.hpp"
#include "reactor/config.hpp"
#include "gfx/ui/button.hpp"
#include "gfx/ui/widget.hpp"

#include "reactor/view/buttons.hpp"
#include "reactor/controller/reactor.hpp"
#include "reactor/view/button.hpp"

#include <iostream>
#include <memory>

namespace reactor {
namespace view {

ReactorButtons::ReactorButtons( gfx::core::Vector2f pos, gfx::core::Vector2f size )
{
    setPosition( pos );
    setSize( size );

    loadFont();

    setupButton( config::Reactor::Buttons::Specialization::AddMolecule::Position, "Add molecule" );

    setupButton( config::Reactor::Buttons::Specialization::RemoveMolecule::Position,
                 "Remove molecule" );

    setupButton( config::Reactor::Buttons::Specialization::MovePiston::Left::Position,
                 "Move piston left" );

    setupButton( config::Reactor::Buttons::Specialization::MovePiston::Right::Position,
                 "Move piston right" );
}

void
ReactorButtons::onIdle( const gfx::core::Event& event )
{
    if ( isPressed( AddMolecule ) )
    {
        controller_->onAddMolecule();
    }

    if ( isPressed( RmMolecule ) )
    {
        controller_->onRemoveMolecule();
    }

    if ( isPressed( MovePistonLeft ) )
    {
        controller_->onMovePistonLeft();
    }

    if ( isPressed( MovePistonRight ) )
    {
        controller_->onMovePistonRight();
    }
}

void
ReactorButtons::loadFont()
{
    labels_font_.loadFromFile( config::Common::Font::Name );
}

bool
ReactorButtons::isPressed( ButtonCode code )
{
    return dynamic_cast<Button*>( children_[code].get() )->isPressed();
}

void
ReactorButtons::setupButton( const gfx::core::Vector2f& pos, const char* label )
{
    auto button = std::make_unique<Button>();

    button->setBackgroundColor( config::Reactor::Buttons::Common::Parameters::Color::Default );
    button->setLabelFont( labels_font_, config::Reactor::Buttons::Common::Font::Size );
    button->setLabelText( label );
    button->setLabelText( label );
    button->setSize( config::Reactor::Buttons::Common::Parameters::Size );
    button->setRelPos( pos );

    addChild( std::move( button ) );
}

} // namespace view
} // namespace reactor
