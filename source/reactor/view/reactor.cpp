#include "gfx/core/color.hpp"

#include "reactor/view/reactor.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/window.hpp"
#include "reactor/config.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/view/panel.hpp"
#include "reactor/view/molecule.hpp"
#include <memory>

namespace reactor {
namespace view {

Reactor::Reactor( model::Reactor& model, controller::Reactor& controller )
    : model_( model ), controller_( controller )
{
    setPosition( gfx::core::Vector2f( config::Reactor::Position.x, config::Reactor::Position.y ) );
    setSize( gfx::core::Vector2f( model_.getW(), model_.getH() ) );

    border_.setSize( getSize() );
    border_.setFillColor( gfx::core::Color::Transparent );
    border_.setOutlineColor( gfx::core::Color::Red );
    border_.setOutlineThickness( 2.0f );

    addChild( std::make_unique<Panel>( controller_ ) );
}

bool
Reactor::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    model_.update( event.delta_time );

    const auto&  molecules_ref = model_.getMolecules();
    const size_t molecule_size = model_.getMoleculesCount();

    molecule_views_.clear();
    molecule_views_.reserve( molecule_size );

    for ( const auto& model_mol : molecules_ref )
    {
        molecule_views_.push_back( std::make_unique<Molecule>( *model_mol ) );
    }

    border_.setSize( gfx::core::Vector2f( model_.getPistonPos(), model_.getH() ) );

    return false;
}

void
Reactor::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( border_, transform );

    for ( const auto& mol_view : molecule_views_ )
    {
        mol_view->draw( window, transform );
    }
}

} // namespace view
} // namespace reactor
