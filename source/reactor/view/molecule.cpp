#include "gfx/core/window.hpp"

#include "reactor/view/molecule.hpp"
#include "reactor/model/molecule.hpp"
#include "reactor/config.hpp"

namespace reactor {
namespace view {

Molecule::Molecule( const model::Molecule& model )
    : model_ref_( model ), circle_shape_( model.getR() ),
      rect_shape_( gfx::core::Vector2f( model.getR() * 2, model.getR() * 2 ) )
{
    if ( model.getType() == model::Molecule::Circle )
    {
        circle_shape_.setFillColor( config::Reactor::Physics::Molecule::Circle::Color );
        current_shape_ = &circle_shape_;
    } else if ( model.getType() == model::Molecule::Square )
    {
        rect_shape_.setFillColor( config::Reactor::Physics::Molecule::Square::Color );
        current_shape_ = &rect_shape_;
    }

    updateFromModel( model );
}

void
Molecule::updateFromModel( const model::Molecule& model )
{
    if ( current_shape_ == &circle_shape_ )
    {
        circle_shape_.setPosition( model.getX(), model.getY() );
    } else if ( current_shape_ == &rect_shape_ )
    {
        rect_shape_.setPosition( model.getX(), model.getY() );
    }
}

void
Molecule::draw( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    if ( current_shape_ != nullptr )
    {
        window.draw( *current_shape_, transform );
    }
}

} // namespace view
} // namespace reactor
