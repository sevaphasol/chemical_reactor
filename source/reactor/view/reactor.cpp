#include "gfx/core/color.hpp"

#include "reactor/view/reactor.hpp"
#include "gfx/core/window.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/view/molecule.hpp"

namespace reactor {
namespace view {

Reactor::Reactor( model::Reactor& model ) : model_ref_( model )
{
    setSize( gfx::core::Vector2f( model_ref_.getW(), model_ref_.getH() ) );

    border_.setSize( gfx::core::Vector2f( model_ref_.getW(), model_ref_.getH() ) );
    border_.setFillColor( gfx::core::Color::Transparent );
    border_.setOutlineColor( gfx::core::Color::Red );
    border_.setOutlineThickness( 2.0f );
}

void
Reactor::update()
{
    const auto&  molecules_ref = model_ref_.getMolecules();
    const size_t molecule_size = model_ref_.getMoleculesCount();

    molecule_views_.clear();
    molecule_views_.reserve( molecule_size );

    for ( const auto& model_mol : molecules_ref )
    {
        molecule_views_.push_back( std::make_unique<Molecule>( *model_mol ) );
    }

    border_.setSize( gfx::core::Vector2f( model_ref_.getPistonPos(), model_ref_.getH() ) );
}

void
Reactor::onIdle( const gfx::core::Event& event )
{
    if ( event.type == gfx::core::Event::Idle )
    {
        update();
    }
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
