#include "reactor/controller/reactor.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/config.hpp"

#include <random>

namespace reactor {
namespace controller {

Reactor::Reactor( model::Reactor& model ) : model_ref_( model ) {}

void
Reactor::onAddMolecule()
{
    static std::random_device                     rd;
    static std::mt19937                           gen( rd() );
    static std::uniform_real_distribution<double> dis_pos_x( 0.0, model_ref_.getW() * 0.8 );
    static std::uniform_real_distribution<double> dis_pos_y( 0.0, model_ref_.getH() );
    static std::uniform_real_distribution<double> dis_vel( -100.0, 100.0 );

    double x  = dis_pos_x( gen );
    double y  = dis_pos_y( gen );
    double vx = dis_vel( gen );
    double vy = dis_vel( gen );

    model_ref_.addMolecule( std::make_unique<model::CircleMolecule>( 5.0, x, y, vx, vy, 1.0 ) );
}

void
Reactor::onRemoveMolecule()
{
    if ( model_ref_.getMoleculesCount() > 0 )
    {
        model_ref_.removeMolecule( model_ref_.getMoleculesCount() - 1 );
    }
}

void
Reactor::onMovePistonLeft()
{
    model_ref_.movePiston( -config::Reactor::Buttons::Specialization::MovePiston::MoveDistance );
}

void
Reactor::onMovePistonRight()
{
    model_ref_.movePiston( config::Reactor::Buttons::Specialization::MovePiston::MoveDistance );
}

} // namespace controller
} // namespace reactor
