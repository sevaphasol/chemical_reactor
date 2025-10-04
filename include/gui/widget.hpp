#pragma once

#include "gfx_core/color.hpp"
#include "gfx_core/drawable.hpp"
#include "gfx_core/rectangle_shape.hpp"
#include "gfx_core/event.hpp"
#include "gfx_core/transform.hpp"
#include "gfx_core/transformable.hpp"
#include "gfx_core/vector2.hpp"
#include "gfx_core/window.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <vector>
#include <iostream>

namespace gui {

class Widget : public gfx_core::Drawable {
  public:
    explicit Widget( const gfx_core::Vector2f& pos ) { rect_.setPosition( pos ); };

    explicit Widget( const gfx_core::Vector2f& pos, const gfx_core::Vector2f& size ) : rect_( size )
    {
        rect_.setPosition( pos );
    };

    explicit Widget( const gfx_core::Vector2f& pos,
                     const gfx_core::Vector2f& size,
                     const gfx_core::Color&    color )
        : Widget( pos, size )
    {
        rect_.setFillColor( color );
    }

    explicit Widget( float x, float y, float w, float h ) : rect_( gfx_core::Vector2f( w, h ) )
    {
        rect_.setPosition( gfx_core::Vector2f( x, y ) );
        rect_.setFillColor( gfx_core::Color::Black );
    };

    virtual void
    HandleEvents( const gfx_core::Event& event )
    {
        // // std::cerr << "HandleEvents() from widget " << typeid( *this ).name() << std::endl;

        HandleEventChildren( event );
    }

    virtual void
    Update()
    {
        // // // std::cerr << "Update() from widget " << typeid( *this ).name() << std::endl;

        UpdateChildren();
    }

    void
    HandleEventChildren( const gfx_core::Event& event )
    {
        // // std::cerr << "HandleEventChildren() from widget " << typeid( *this ).name() <<
        // std::endl;

        for ( auto& child : childern_ )
        {
            child->HandleEvents( event );
        }
    }

    virtual void
    UpdateChildren()
    {
        // // std::cerr << "UpdateChildren() from widget " << typeid( *this ).name() << std::endl;

        for ( auto& child : childern_ )
        {
            child->Update();
        }
    }

    gfx_core::Vector2f
    GetAbsolutePos() const
    {
        return GetPos() + GetParentAbsolutePos();
    }

    gfx_core::Vector2f
    GetParentAbsolutePos() const
    {
        // std::cerr << "parent_ = " << parent_ << std::endl;

        return ( parent_ != nullptr ) ? parent_->GetAbsolutePos() : gfx_core::Vector2f( 0, 0 );
    }

    gfx_core::Vector2f
    GetPos() const
    {
        return rect_.getPosition();
    }

    gfx_core::Vector2f
    GetSize() const
    {
        return rect_.getSize();
    }

    void
    SetPos( const gfx_core::Vector2f& pos )
    {
        rect_.setPosition( pos );
    }

    void
    SetSize( const gfx_core::Vector2f& size )
    {
        rect_.setSize( size );
    }

    bool
    PointInside( const gfx_core::Vector2f& point ) const
    {
        gfx_core::Vector2f abs_pos = GetAbsolutePos();

        gfx_core::Vector2f size = GetSize();

        return ( ( point.x >= abs_pos.x && point.x <= abs_pos.x + size.x ) &&
                 ( point.y >= abs_pos.y && point.y <= abs_pos.y + size.y ) );
    }

    void
    AddChild( std::unique_ptr<Widget> child )
    {
        child->parent_ = this;
        childern_.push_back( std::move( child ) );
    }

  private:
    virtual void
    draw( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        // // std::cerr << "draw() from widget " << typeid( *this ).name() << std::endl;

        DrawSelf( window, transform );
        DrawChildren( window, transform );
    }

    virtual void
    DrawSelf( gfx_core::Window& window, gfx_core::Transform transform ) const
    {
        // // std::cerr << "DrawSelf() from widget " << typeid( *this ).name() << std::endl;

        // auto sf_color = reinterpret_cast<sf::RectangleShape*>( rect_.getImpl() )->getFillColor();

        // // std::cerr << "r = " << int( sf_color.r ) << std::endl;
        // // std::cerr << "g = " << int( sf_color.g ) << std::endl;
        // // std::cerr << "b = " << int( sf_color.b ) << std::endl;
        // // std::cerr << "a = " << int( sf_color.a ) << std::endl;

        window.draw( rect_, transform );
    }

    virtual void
    DrawChildren( gfx_core::Window& window, gfx_core::Transform transform ) const
    {
        // // std::cerr << "DrawChildren() from widget " << typeid( *this ).name() << std::endl;

        transform.translate( GetPos() );

        for ( const auto& child : childern_ )
        {
            window.draw( *child, transform );
        }
    }

  protected:
    gfx_core::RectangleShape rect_;

    Widget* parent_{ nullptr };

    std::vector<std::unique_ptr<Widget>> childern_;
};

} // namespace gui
