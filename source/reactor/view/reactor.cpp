#include "gfx/core/color.hpp"

#include "reactor/view/reactor.hpp"
#include "gfx/core/event.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "reactor/config.hpp"
#include "reactor/controller/graph_panel.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/view/graph_panel.hpp"
#include "reactor/view/button_panel.hpp"
#include "reactor/view/molecule.hpp"
#include "reactor/controller/reactor.hpp"
#include "reactor/view/scroll_bar.hpp"
#include <memory>

namespace reactor {
namespace view {

Reactor::Reactor()
    : model_( config::Reactor::Size.x, config::Reactor::Size.y ), graph_controller_( graph_model_ )
{
    setPosition( gfx::core::Vector2f( config::Reactor::Position.x, config::Reactor::Position.y ) );
    setSize( gfx::core::Vector2f( model_.getW(), model_.getH() ) );

    border_.setSize( getSize() );
    border_.setFillColor( gfx::core::Color::Transparent );
    border_.setOutlineColor( gfx::core::Color::Red );
    border_.setOutlineThickness( 2.0f );

    addChild( std::make_unique<GraphPanel>( graph_model_ ) );
    addChild( std::make_unique<ButtonPanel>( std::make_unique<controller::Reactor>( model_ ) ) );
    addChild( std::make_unique<ScrollBar>( gfx::core::Vector2f( 1300.0f, 100.0f ),
                                           gfx::core::Vector2f( 50.0f, 500.0f ) ) );
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
        molecule_views_.push_back( std::make_unique<view::Molecule>( *model_mol ) );
    }

    border_.setSize( gfx::core::Vector2f( model_.getPistonPos(), model_.getH() ) );

    graph_controller_.update( event.delta_time,
                              model_.getTotalEnergy(),
                              model_.getMoleculesCount() );

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
