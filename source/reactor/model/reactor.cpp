#include "reactor/config.hpp"
#include "reactor/model/reactor.hpp"
#include "reactor/controller/reactor.hpp"
#include "reactor/model/molecule.hpp"

#include <functional>
#include <memory>
#include <random>
#include <sys/types.h>

namespace reactor {
namespace model {

Reactor::Reactor( double w, double h ) : w_( w ), h_( h ), piston_pos_( w )
{
    controller::Reactor controller( *this );
    for ( int i = 0; i < config::Reactor::Physics::Molecule::StartMoleculesCount; i++ )
    {
        controller.onAddMolecule();
    }
}

double
Reactor::getW() const
{
    return w_;
}

double
Reactor::getH() const
{
    return h_;
}

double
Reactor::getPistonPos() const
{
    return piston_pos_;
}

const std::vector<std::unique_ptr<Molecule>>&
Reactor::getMolecules() const
{
    return molecules_;
}

void
Reactor::update( double dt )
{
    handleMoleculesCollisions();
    moveMolecules( dt );
    handleWallCollisions();
}

void
Reactor::addMolecule( std::unique_ptr<Molecule> mol )
{
    molecules_.push_back( std::move( mol ) );
}

void
Reactor::removeMolecule( size_t index )
{
    if ( index < molecules_.size() )
    {
        molecules_.erase( molecules_.begin() + index );
    }
}

void
Reactor::setWallTemperature( double factor )
{
    wall_templ_ = factor * config::Reactor::Physics::MaxWallTemperature;
}

void
Reactor::movePiston( double dist )
{
    double new_piston_pos = piston_pos_ + dist;

    if ( w_ * 0.1 <= new_piston_pos && new_piston_pos <= w_ )
    {
        piston_pos_ = new_piston_pos;
    }
}

size_t
Reactor::getMoleculesCount() const
{
    return molecules_.size();
}

double
Reactor::getElapsedTime() const
{
    return elapsed_time_;
}

double
Reactor::getTotalEnergy() const
{
    double energy = 0;

    for ( const auto& mol : molecules_ )
    {
        energy += mol->getFullEnergy();
    }

    return energy;
}

void
Reactor::moveMolecules( double dt )
{
    for ( auto& mol_info : molecules_ )
    {
        mol_info->move( dt );
    }
}

double
Reactor::wallTempAdditionalVelocity( double m ) const
{
    return ( 1 + 0.5 * wall_templ_ / m );
}

void
Reactor::handleWallCollisions()
{
    for ( auto& mol : molecules_ )
    {
        double m  = mol->getM();
        double r  = mol->getR();
        double x  = mol->getX();
        double y  = mol->getY();
        double vx = mol->getVx();
        double vy = mol->getVy();

        double temp_v = wallTempAdditionalVelocity( m );

        if ( x + 2 * r > piston_pos_ )
        {
            mol->setVx( -vx - temp_v );
            mol->setX( piston_pos_ - 2 * r );
        }

        if ( x < 0 )
        {
            mol->setVx( -vx + temp_v );
            mol->setX( 0 );
        }

        if ( y + 2 * r > h_ )
        {
            mol->setVy( -vy - temp_v );
            mol->setY( h_ - 2 * r );
        }

        if ( y < 0 )
        {
            mol->setVy( -vy + temp_v );
            mol->setY( 0 );
        }
    }
}

void
Reactor::handleMoleculesCollisions()
{
    remove_indexes_.clear();
    new_molecules_.clear();

    size_t n_molecules = molecules_.size();

    if ( n_molecules == 0 )
    {
        return;
    }

    for ( size_t i = 0; i < n_molecules - 1; ++i )
    {
        for ( size_t j = i + 1; j < n_molecules; ++j )
        {
            if ( collide( i, j ) )
            {
                break;
            }
        }
    }

    if ( n_molecules == 0 )
    {
        return;
    }

    std::sort( remove_indexes_.begin(), remove_indexes_.end(), []( size_t a, size_t b ) {
        return a > b;
    } );

    for ( const auto& req : remove_indexes_ )
    {
        if ( req < molecules_.size() )
        {
            molecules_.erase( molecules_.begin() + req );
        }
    }

    for ( auto& req : new_molecules_ )
    {
        molecules_.push_back( std::move( req ) );
    }
}

bool
Reactor::collide( size_t mol1_idx, size_t mol2_idx )
{
    Molecule& mol1 = *molecules_[mol1_idx];
    Molecule& mol2 = *molecules_[mol2_idx];

    if ( Molecule::checkCollision( mol1, mol2 ) )
    {
        remove_indexes_.push_back( mol1_idx );
        remove_indexes_.push_back( mol2_idx );

        collide( mol1, mol2 );

        return true;
    }

    return false;
}

void
Reactor::collide( Molecule& mol1, Molecule& mol2 )
{
    // clang-format off
    static std::function<void( Reactor&, Molecule&, Molecule& )>
	vtable[Molecule::Type::Count][Molecule::Type::Count] =
		{ &Reactor::collideCircleCircle, &Reactor::collideCircleSquare,
		  &Reactor::collideSquareCircle, &Reactor::collideSquareSquare };
    // clang-format on

    vtable[mol1.getType()][mol2.getType()]( *this, mol1, mol2 );
}

void
Reactor::collideCircleCircle( Molecule& mol1, Molecule& mol2 )
{
    static auto getRandomAngle = []() {
        static std::random_device                     rd;
        static std::mt19937                           gen( rd() );
        static std::uniform_real_distribution<double> dis( 0.0, 2.0 * M_PI );

        return dis( gen );
    };

    double m          = mol1.getM() + mol2.getM();
    double r          = m;
    double x          = ( mol1.getX() + mol2.getX() ) / 2.0f;
    double y          = ( mol1.getY() + mol2.getY() ) / 2.0f;
    double energy     = mol1.getFullEnergy() + mol2.getFullEnergy();
    double disp_angle = getRandomAngle();
    double v          = sqrt( 2 * energy / m );
    double vx         = v * std::cos( disp_angle );
    double vy         = v * std::sin( disp_angle );

    new_molecules_.push_back( { std::make_unique<SquareMolecule>( r, x, y, vx, vy, m ) } );
}

void
Reactor::collideCircleSquare( Molecule& mol1, Molecule& mol2 )
{
    collideCircleCircle( mol1, mol2 );
}

void
Reactor::collideSquareCircle( Molecule& mol1, Molecule& mol2 )
{
    collideCircleCircle( mol1, mol2 );
}

void
Reactor::collideSquareSquare( Molecule& mol1, Molecule& mol2 )
{
    double r             = config::Reactor::Physics::Molecule::Circle::Radius;
    double x             = ( mol1.getX() + mol2.getX() ) / 2.0f;
    double y             = ( mol1.getY() + mol2.getY() ) / 2.0f;
    double total_circles = mol1.getM() + mol2.getM();
    double energy        = mol1.getFullEnergy() + mol2.getFullEnergy();
    double disp_distance =
        2 * config::Reactor::Physics::Molecule::Circle::Radius / std::sin( M_PI / total_circles );

    double circle_energy = energy / total_circles;
    double v_circle =
        sqrt( 2 * circle_energy / config::Reactor::Physics::Molecule::Circle::Weight );

    for ( int i = 0; i < total_circles; i++ )
    {
        double offset_angle   = 2.0f * M_PI * i / total_circles;
        double cos_disp_angle = std::cos( offset_angle );
        double sin_disp_angle = std::sin( offset_angle );

        double spawn_x = x + disp_distance * cos_disp_angle;
        double spawn_y = y + disp_distance * sin_disp_angle;

        new_molecules_.push_back( { std::make_unique<CircleMolecule>(
            r,
            spawn_x,
            spawn_y,
            v_circle * cos_disp_angle,
            v_circle * sin_disp_angle,
            config::Reactor::Physics::Molecule::Circle::Weight ) } );
    }
}

} // namespace model
} // namespace reactor
