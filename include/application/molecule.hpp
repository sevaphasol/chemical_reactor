#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

namespace application {

class Molecule : public sf::Drawable {
  public:
    Molecule( float r, float x, float y, float vx, float vy, float weight = 0.0f )
        : r_( r ), x_( x ), y_( y ), vx_( vx ), vy_( vy ), weight_( weight ) {};

    virtual ~Molecule() = default;

    enum Type {
        CIRCLE,
        SQUARE,
        N_TYPES,
    };

    void
    Move( float dt )
    {
        x_ += vx_ * dt;
        y_ += vy_ * dt;

        UpdateShapePosition();
    }

    float
    GetX() const
    {
        return x_;
    }

    float
    GetY() const
    {
        return y_;
    }

    float
    GetVx() const
    {
        return vx_;
    }

    float
    GetVy() const
    {
        return vy_;
    }

    void
    SetVx( float vx )
    {
        vx_ = vx;
    }

    void
    SetVy( float vy )
    {
        vy_ = vy;
    }

    void
    SetX( float x )
    {
        x_ = x;
        SetShapeX( x );
    }

    void
    SetY( float y )
    {
        y_ = y;
        SetShapeY( y );
    }

    float
    GetR() const
    {
        return r_;
    }

    float
    GetWeight() const
    {
        return weight_;
    }

    Type virtual GetType() const = 0;

  public:
    static void
    Collide( Molecule& mol1, Molecule& mol2 )
    {
        float m1      = mol1.GetWeight();
        float v1x     = mol1.GetVx();
        float v1y     = mol1.GetVy();
        float m2      = mol2.GetWeight();
        float v2x     = mol2.GetVx();
        float v2y     = mol2.GetVy();
        float delta_m = m1 - m2;
        float sum_m   = m1 + m2;

        mol1.SetVx( ( delta_m * v1x + 2 * m2 * v2x ) / sum_m );
        mol1.SetVy( ( delta_m * v1y + 2 * m2 * v2y ) / sum_m );
        mol2.SetVx( ( -delta_m * v2x + 2 * m1 * v1x ) / sum_m );
        mol2.SetVy( ( -delta_m * v2y + 2 * m1 * v1y ) / sum_m );
    }

    static bool
    CheckCollision( const Molecule& mol1, const Molecule& mol2 )
    {
        float x1 = mol1.GetX();
        float y1 = mol1.GetY();
        float r1 = mol1.GetR();
        float x2 = mol2.GetX();
        float y2 = mol2.GetY();
        float r2 = mol2.GetR();

        float cx1 = x1 + r1;
        float cy1 = y1 + r1;
        float cx2 = x2 + r2;
        float cy2 = y2 + r2;

        float delta_cx = cx1 - cx2;
        float delta_cy = cy1 - cy2;

        float distance_sq = delta_cx * delta_cx + delta_cy * delta_cy;

        float critical_distance = r1 + r2;

        return distance_sq < critical_distance * critical_distance;
    }

  private:
    virtual void
    UpdateShapePosition() = 0;

    virtual void
    SetShapeX( float x ) = 0;

    virtual void
    SetShapeY( float y ) = 0;

  protected:
    float weight_;

    float r_;

    float x_;
    float y_;

    float vx_;
    float vy_;
};

} // namespace application
