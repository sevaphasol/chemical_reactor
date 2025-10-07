#include "reactor/controller/reactor.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/config.hpp"

#include <random>

namespace reactor {
namespace controller {

Reactor::Reactor( model::Reactor& model ) : model_( model ) {}

void
Reactor::onAddMolecule()
{
    static std::random_device                     rd;
    static std::mt19937                           gen( rd() );
    static std::uniform_real_distribution<double> dis_x( 0.0, model_.getW() );
    static std::uniform_real_distribution<double> dis_y( 0.0, model_.getH() );
    static std::uniform_real_distribution<double> dis_v(
        0.0,
        config::Reactor::Physics::Molecule::StartVelocityMax );

    double x  = dis_x( gen );
    double y  = dis_y( gen );
    double vx = dis_v( gen );
    double vy = dis_v( gen );

    model_.addMolecule( std::make_unique<model::CircleMolecule>( 5.0, x, y, vx, vy, 1.0 ) );
}

void
Reactor::onRemoveMolecule()
{
    if ( model_.getMoleculesCount() > 0 )
    {
        model_.removeMolecule( model_.getMoleculesCount() - 1 );
    }
}

void
Reactor::onMovePistonLeft()
{
    model_.movePiston( -config::Reactor::ButtonPanel::Buttons::MovePiston::MoveDistance );
}

void
Reactor::onMovePistonRight()
{
    model_.movePiston( config::Reactor::ButtonPanel::Buttons::MovePiston::MoveDistance );
}

} // namespace controller
} // namespace reactor
