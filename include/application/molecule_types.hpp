#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "application/molecule.hpp"
#include "application/config.hpp"

namespace application {

class CircleMolecule : public Molecule {
  public:
    CircleMolecule( double r, double x, double y, double vx, double vy, double weight )
        : Molecule( r, x, y, vx, vy, weight ), shape_( r )
    {
        shape_.setPosition( x, y );
        shape_.setFillColor( Config::CircleMoleculeColor );
    }

  private:
    void
    UpdateShapePosition() override
    {
        shape_.setPosition( x_, y_ );
    }

    void
    SetShapeX( double x ) override
    {
        shape_.setPosition( x, y_ );
    }

    void
    SetShapeY( double y ) override
    {
        shape_.setPosition( x_, y );
    }

    Type
    GetType() const override
    {
        return CIRCLE;
    }

    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        target.draw( shape_, states );
    }

  private:
    sf::CircleShape shape_;
};

class SquareMolecule : public Molecule {
  public:
    SquareMolecule( double r, double x, double y, double vx, double vy, double weight )
        : Molecule( r, x, y, vx, vy, weight ), shape_( sf::Vector2f( r * 2, r * 2 ) )
    {
        shape_.setPosition( x, y );
        shape_.setFillColor( Config::SquareMoleculeColor );
    }

  private:
    void
    UpdateShapePosition() override
    {
        shape_.setPosition( x_, y_ );
    }

    void
    SetShapeX( double x ) override
    {
        shape_.setPosition( x, y_ );
    }

    void
    SetShapeY( double y ) override
    {
        shape_.setPosition( x_, y );
    }

    Type
    GetType() const override
    {
        return SQUARE;
    }

    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        target.draw( shape_, states );
    }

  private:
    sf::RectangleShape shape_;
};

} // namespace application
