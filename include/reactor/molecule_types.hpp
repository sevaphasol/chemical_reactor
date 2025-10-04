#pragma once

#include "gfx_core/window.hpp"
#include "reactor/molecule.hpp"
#include "gfx_core/circle_shape.hpp"
#include "gfx_core/rectangle_shape.hpp"
#include "config.hpp"

namespace reactor {

class CircleMolecule : public Molecule {
  public:
    CircleMolecule( double r, double x, double y, double vx, double vy, double weight )
        : Molecule( r, x, y, vx, vy, weight ), shape_( r )
    {
        shape_.setPosition( x, y );
        shape_.setFillColor( config::Reactor::Physics::Molecule::Circle::Color );
    }

  private:
    void
    UpdateShapePosition() override
    {
        shape_.setPosition( origin_x_ + x_, origin_y_ + y_ );
    }

    void
    SetShapeX( double x ) override
    {
        shape_.setPosition( origin_x_ + x, y_ );
    }

    void
    SetShapeY( double y ) override
    {
        shape_.setPosition( x_, origin_y_ + y );
    }

    Type
    GetType() const override
    {
        return CIRCLE;
    }

    virtual void
    draw( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        window.draw( shape_, transform );
    }

  private:
    gfx_core::CircleShape shape_;
};

class SquareMolecule : public Molecule {
  public:
    SquareMolecule( double r, double x, double y, double vx, double vy, double weight )
        : Molecule( r, x, y, vx, vy, weight ), shape_( gfx_core::Vector2f( r * 2, r * 2 ) )
    {
        shape_.setPosition( x, y );
        shape_.setFillColor( config::Reactor::Physics::Molecule::Square::Color );
    }

  private:
    void
    UpdateShapePosition() override
    {
        shape_.setPosition( origin_x_ + x_, origin_y_ + y_ );
    }

    void
    SetShapeX( double x ) override
    {
        shape_.setPosition( origin_x_ + x, y_ );
    }

    void
    SetShapeY( double y ) override
    {
        shape_.setPosition( x_, origin_y_ + y );
    }

    Type
    GetType() const override
    {
        return SQUARE;
    }

    virtual void
    draw( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        window.draw( shape_, transform );
    }

  private:
    gfx_core::RectangleShape shape_;
};

} // namespace reactor
