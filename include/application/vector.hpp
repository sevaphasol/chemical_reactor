#pragma once

#include <SFML/Graphics/Color.hpp>
#include <cmath>

namespace application {

class Vector {
  public:
    Vector( float x, float y, float z );

    Vector( const sf::Color& color );

    bool
    Valid() const;

    float
    GetLenSq() const;

    float
    GetLen() const;

    float
    GetX() const;

    float
    GetY() const;

    float
    GetZ() const;

    void
    Clamp( float lo, float hi );

    float
    operator,( const Vector& that ) const;

    Vector
    operator+( const Vector& that ) const;

    Vector
    operator-( const Vector& that ) const;

    void
    operator+=( const Vector& that );

    void
    operator-=( const Vector& that );

    Vector
    operator+( float scalar ) const;

    Vector
    operator-( float scalar ) const;

    Vector
    operator*( float scalar ) const;

    void
    operator+=( float scalar );

    void
    operator-=( float scalar );

    void
    operator*=( float scalar );

  private:
    float x_;
    float y_;
    float z_;
};

Vector
operator*( float scalar, const Vector& v );

float
CalcCos( const Vector& v1, const Vector& v2 );

float
CalcSin( const Vector& v1, const Vector& v2 );

float
CalcVecMulModule( const Vector& v1, const Vector& v2 );

} // namespace application
