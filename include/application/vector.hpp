#pragma once

#include <SFML/Graphics/Color.hpp>
#include <cmath>

namespace application {

class Vector {
  public:
    Vector( double x, double y, double z );

    Vector( const sf::Color& color );

    bool
    Valid() const;

    double
    GetLenSq() const;

    double
    GetLen() const;

    double
    GetX() const;

    double
    GetY() const;

    double
    GetZ() const;

    void
    Clamp( double lo, double hi );

    double
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
    operator+( double scalar ) const;

    Vector
    operator-( double scalar ) const;

    Vector
    operator*( double scalar ) const;

    void
    operator+=( double scalar );

    void
    operator-=( double scalar );

    void
    operator*=( double scalar );

  private:
    double x_;
    double y_;
    double z_;
};

Vector
operator*( double scalar, const Vector& v );

double
CalcCos( const Vector& v1, const Vector& v2 );

double
CalcSin( const Vector& v1, const Vector& v2 );

double
CalcVecMulModule( const Vector& v1, const Vector& v2 );

} // namespace application
