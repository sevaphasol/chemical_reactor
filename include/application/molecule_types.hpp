#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "application/molecule.hpp"
#include "application/config.hpp"

namespace application {

class CircleMolecule : public Molecule {
  public:
    CircleMolecule( float r, float x, float y, float vx, float vy )
        : Molecule( r, x, y, vx, vy, 1.0f ), shape_( r )
    {
        shape_.setPosition( x, y );
    }

  private:
    void
    UpdateShapePosition() override
    {
        shape_.setPosition( x_, y_ );
    }

    void
    SetShapeX( float x ) override
    {
        shape_.setPosition( x, y_ );
    }

    void
    SetShapeY( float y ) override
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
    SquareMolecule( float r, float x, float y, float vx, float vy, float weight )
        : Molecule( r, x, y, vx, vy, weight ), shape_( sf::Vector2f( r * 2, r * 2 ) )
    {
        shape_.setPosition( x, y );
    }

  private:
    void
    UpdateShapePosition() override
    {
        shape_.setPosition( x_, y_ );
    }

    void
    SetShapeX( float x ) override
    {
        shape_.setPosition( x, y_ );
    }

    void
    SetShapeY( float y ) override
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
