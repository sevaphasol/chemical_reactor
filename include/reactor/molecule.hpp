#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

namespace reactor {

class Molecule : public sf::Drawable {
  public:
    Molecule( double r, double x, double y, double vx, double vy, double weight )
        : r_( r ), x_( x ), y_( y ), vx_( vx ), vy_( vy ), weight_( weight ) {};

    virtual ~Molecule() = default;

    enum Type {
        CIRCLE,
        SQUARE,
        N_TYPES,
    };

    void
    Move( double dt )
    {
        x_ += vx_ * dt;
        y_ += vy_ * dt;

        UpdateShapePosition();
    }

    double
    GetX() const
    {
        return x_;
    }

    double
    GetY() const
    {
        return y_;
    }

    double
    GetVx() const
    {
        return vx_;
    }

    double
    GetVy() const
    {
        return vy_;
    }

    void
    SetVx( double vx )
    {
        vx_ = vx;
    }

    void
    SetVy( double vy )
    {
        vy_ = vy;
    }

    void
    SetX( double x )
    {
        x_ = x;
        SetShapeX( x );
    }

    void
    SetY( double y )
    {
        y_ = y;
        SetShapeY( y );
    }

    double
    GetR() const
    {
        return r_;
    }

    double
    GetWeight() const
    {
        return weight_;
    }

    double
    GetKineticEnergy() const
    {
        return weight_ * ( vx_ * vx_ + vy_ * vy_ ) / 2;
    }

    // double
    // GetPotentialEnergy() const
    // {
    //     // return weight_ * Config::SpeedVelocitySq;
    //     return 0.0;
    // }

    double
    GetFullEnergy() const
    {
        return GetKineticEnergy(); //+ GetPotentialEnergy();
    }

    double
    GetEnergy() const
    {
        return GetKineticEnergy();
    }

    Type virtual GetType() const = 0;

  public:
    static void
    Collide( Molecule& mol1, Molecule& mol2 )
    {
        double m1      = mol1.GetWeight();
        double v1x     = mol1.GetVx();
        double v1y     = mol1.GetVy();
        double m2      = mol2.GetWeight();
        double v2x     = mol2.GetVx();
        double v2y     = mol2.GetVy();
        double delta_m = m1 - m2;
        double sum_m   = m1 + m2;

        mol1.SetVx( ( delta_m * v1x + 2 * m2 * v2x ) / sum_m );
        mol1.SetVy( ( delta_m * v1y + 2 * m2 * v2y ) / sum_m );
        mol2.SetVx( ( -delta_m * v2x + 2 * m1 * v1x ) / sum_m );
        mol2.SetVy( ( -delta_m * v2y + 2 * m1 * v1y ) / sum_m );
    }

    static bool
    CheckCollision( const Molecule& mol1, const Molecule& mol2 )
    {
        double x1 = mol1.GetX();
        double y1 = mol1.GetY();
        double r1 = mol1.GetR();
        double x2 = mol2.GetX();
        double y2 = mol2.GetY();
        double r2 = mol2.GetR();

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

    void
    SetOrigin( sf::Vector2f origin )
    {
        origin_x_ = origin.x;
        origin_y_ = origin.y;
    }

  private:
    virtual void
    UpdateShapePosition() = 0;

    virtual void
    SetShapeX( double x ) = 0;

    virtual void
    SetShapeY( double y ) = 0;

  protected:
    double origin_x_;
    double origin_y_;

    double weight_;

    double r_;

    double x_;
    double y_;

    double vx_;
    double vy_;
};

} // namespace reactor
