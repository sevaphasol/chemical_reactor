#include "gfx/core/event.hpp"
#include "gfx/core/font.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "reactor/config.hpp"
#include "reactor/view/button_panel.hpp"
#include "reactor/controller/reactor.hpp"
#include "reactor/view/button.hpp"
#include "reactor/view/scroll_bar.hpp"

#include <memory>

namespace reactor {
namespace view {

ButtonPanel::ButtonPanel( std::unique_ptr<controller::Reactor>( controller ) )
    : controller_( std::move( controller ) )
{
    setDraggable( true );

    setPosition( config::Reactor::ButtonPanel::Position );
    setSize( config::Reactor::ButtonPanel::Size );

    border_.setSize( getSize() );
    border_.setFillColor( gfx::core::Color::Transparent );
    border_.setOutlineColor( gfx::core::Color::Red );
    border_.setOutlineThickness( 2.0f );

    loadFont();

    setupButton( config::Reactor::ButtonPanel::Buttons::AddMolecule::Position, "Add molecule" );

    setupButton( config::Reactor::ButtonPanel::Buttons::RemoveMolecule::Position,
                 "Remove molecule" );

    setupButton( config::Reactor::ButtonPanel::Buttons::MovePiston::Left::Position,
                 "Move piston left" );

    setupButton( config::Reactor::ButtonPanel::Buttons::MovePiston::Right::Position,
                 "Move piston right" );

    addChild( std::make_unique<view::ScrollBar>( config::Reactor::ScrollBar::Pos,
                                                 config::Reactor::ScrollBar::Size ) );
}

bool
ButtonPanel::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    if ( isPressed( ButtonCode::AddMolecule ) )
    {
        controller_->onAddMolecule();
    }

    if ( isPressed( ButtonCode::RmMolecule ) )
    {
        controller_->onRemoveMolecule();
    }

    if ( isPressed( ButtonCode::MovePistonLeft ) )
    {
        controller_->onMovePistonLeft();
    }

    if ( isPressed( ButtonCode::MovePistonRight ) )
    {
        controller_->onMovePistonRight();
    }

    if ( isScrolled( ButtonCode::ScrollBar ) )
    {
        controller_->onScroll(
            dynamic_cast<view::ScrollBar*>( children_[ButtonCode::ScrollBar].get() )
                ->getScrollFactor() );
    }

    return false;
}

void
ButtonPanel::loadFont()
{
    labels_font_.loadFromFile( config::Common::Font::Name );
}

bool
ButtonPanel::isPressed( ButtonCode code )
{
    return dynamic_cast<Button*>( children_[code].get() )->isPressed();
}

bool
ButtonPanel::isScrolled( ButtonCode code )
{
    return dynamic_cast<view::ScrollBar*>( children_[code].get() )->isScrolled();
}

void
ButtonPanel::setupButton( const gfx::core::Vector2f& pos, const char* label )
{
    auto button = std::make_unique<Button>();

    button->setBackgroundColor( config::Reactor::ButtonPanel::Common::Parameters::Color::Default );
    button->setLabelFont( labels_font_, config::Reactor::ButtonPanel::Common::Font::Size );
    button->setLabelText( label );
    button->setLabelText( label );
    button->setSize( config::Reactor::ButtonPanel::Common::Parameters::Size );
    button->setRelPos( pos );

    addChild( std::move( button ) );
}

void
ButtonPanel::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( border_, transform );
}

} // namespace view
} // namespace reactor
