#include "application/vector.hpp"
#include <SFML/System/Vector2.hpp>
#include <algorithm>

namespace application {

Vector::Vector( float x, float y, float z ) : x_( x ), y_( y ), z_( z ) {};

Vector::Vector( const sf::Color& color ) : x_( color.r ), y_( color.g ), z_( color.b ) {};

bool
Vector::Valid() const
{
    return !( std::isnan( x_ ) || std::isnan( y_ ) || std::isnan( z_ ) );
}

float
Vector::GetX() const
{
    return x_;
}

float
Vector::GetY() const
{
    return y_;
}

float
Vector::GetZ() const
{
    return z_;
}

void
Vector::Clamp( float lo, float hi )
{
    x_ = std::clamp( x_, lo, hi );
    y_ = std::clamp( y_, lo, hi );
    z_ = std::clamp( z_, lo, hi );
}

float
Vector::GetLenSq() const
{
    return ( *this, *this );
}

float
Vector::GetLen() const
{
    return std::sqrt( GetLenSq() );
}

float
Vector::operator,( const Vector& that ) const
{
    return ( this->x_ * that.x_ ) + ( this->y_ * that.y_ ) + ( this->z_ * that.z_ );
}

Vector
Vector::operator+( const Vector& that ) const
{
    return { this->x_ + that.x_, this->y_ + that.y_, this->z_ + that.z_ };
}

Vector
Vector::operator-( const Vector& that ) const
{
    return { this->x_ - that.x_, this->y_ - that.y_, this->z_ - that.z_ };
}

void
Vector::operator+=( const Vector& that )
{
    this->x_ += that.x_;
    this->y_ += that.y_;
    this->z_ += that.z_;
}

void
Vector::operator-=( const Vector& that )
{
    this->x_ -= that.x_;
    this->y_ -= that.y_;
    this->z_ -= that.z_;
}

Vector
Vector::operator+( float scalar ) const
{
    return Vector( this->x_ + scalar, this->y_ + scalar, this->z_ + scalar );
}

Vector
Vector::operator-( float scalar ) const
{
    return Vector( this->x_ - scalar, this->y_ - scalar, this->z_ - scalar );
}

Vector
Vector::operator*( float scalar ) const
{
    return Vector( this->x_ * scalar, this->y_ * scalar, this->z_ * scalar );
}

void
Vector::operator+=( float scalar )
{
    this->x_ += scalar;
    this->y_ += scalar;
    this->z_ += scalar;
}

void
Vector::operator-=( float scalar )
{
    this->x_ -= scalar;
    this->y_ -= scalar;
    this->z_ -= scalar;
}

void
Vector::operator*=( float scalar )
{
    this->x_ *= scalar;
    this->y_ *= scalar;
    this->z_ *= scalar;
}

Vector
operator*( float scalar, const Vector& v )
{
    return v * scalar;
}

float
CalcCos( const Vector& v1, const Vector& v2 )
{
    return ( v1, v2 ) / ( v1.GetLen() * v2.GetLen() );
}

float
CalcSin( const Vector& v1, const Vector& v2 )
{
    return std::sin( std::acos( CalcCos( v1, v2 ) ) );
}

float
CalcVecMulModule( const Vector& v1, const Vector& v2 )
{
    return v1.GetLen() * v2.GetLen() * CalcSin( v1, v2 );
}

} // namespace application
