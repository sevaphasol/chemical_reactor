#include "reactor/model/molecule.hpp"

namespace reactor {
namespace model {

Molecule::Molecule( double r, double x, double y, double vx, double vy, double m )
    : r_( r ), x_( x ), y_( y ), vx_( vx ), vy_( vy ), m_( m ) {};

void
Molecule::move( double dt )
{
    x_ += vx_ * dt;
    y_ += vy_ * dt;
}

double
Molecule::getX() const
{
    return x_;
}

double
Molecule::getY() const
{
    return y_;
}

double
Molecule::getVx() const
{
    return vx_;
}

double
Molecule::getVy() const
{
    return vy_;
}

void
Molecule::setVx( double vx )
{
    vx_ = vx;
}

void
Molecule::setVy( double vy )
{
    vy_ = vy;
}

void
Molecule::setX( double x )
{
    x_ = x;
}

void
Molecule::setY( double y )
{
    y_ = y;
}

double
Molecule::getR() const
{
    return r_;
}

double
Molecule::getM() const
{
    return m_;
}

double
Molecule::getKineticEnergy() const
{
    return m_ * ( vx_ * vx_ + vy_ * vy_ ) / 2;
}

double
Molecule::getPotentialEnergy() const
{
    return m_;
}

double
Molecule::getFullEnergy() const
{
    return getKineticEnergy() + getPotentialEnergy();
}

bool
Molecule::checkCollision( const Molecule& mol1, const Molecule& mol2 )
{
    double x1 = mol1.getX();
    double y1 = mol1.getY();
    double r1 = mol1.getR();
    double x2 = mol2.getX();
    double y2 = mol2.getY();
    double r2 = mol2.getR();

    double cx1 = x1 + r1;
    double cy1 = y1 + r1;
    double cx2 = x2 + r2;
    double cy2 = y2 + r2;

    double delta_cx = cx1 - cx2;
    double delta_cy = cy1 - cy2;

    double distance_sq = delta_cx * delta_cx + delta_cy * delta_cy;

    double critical_distance = r1 + r2;

    return distance_sq < critical_distance * critical_distance;
}

} // namespace model
} // namespace reactor
