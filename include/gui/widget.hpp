#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <optional>
#include <vector>

namespace gui {

class Widget : public sf::Drawable {
  public:
    explicit Widget( const sf::Vector2f& pos, const sf::Vector2f& size )
        : pos_( pos ), size_( size ), rect_( size ) {};

    explicit Widget( const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color )
        : Widget( pos, size )
    {
        rect_.setFillColor( color );
    }

    explicit Widget( float x, float y, float w, float h ) : pos_( x, y ), size_( w, h ) {};

    virtual void
    HandleEvents( const sf::Event& event )
    {
        HandleEventChildren( event );
    }

    virtual void
    Update()
    {
        UpdateChildren();
    }

    void
    HandleEventChildren( const sf::Event& event )
    {
        for ( auto& child : childern_ )
        {
            child->HandleEvents( event );
        }
    }

    virtual void
    UpdateChildren()
    {
        for ( auto& child : childern_ )
        {
            child->Update();
        }
    }

    virtual void
    HandleEventsSelf() {};

    virtual void
    UpdateSelf() {};

    sf::Vector2f
    GetAbsolutePos() const
    {
        return pos_ + GetParentAbsolutePos();
    }

    sf::Vector2f
    GetParentAbsolutePos() const
    {
        return ( parent_ != nullptr ) ? parent_->GetAbsolutePos() : sf::Vector2f( 0, 0 );
    }

    sf::Vector2f
    GetPos() const
    {
        return pos_;
    }

    sf::Vector2f
    GetSize() const
    {
        return size_;
    }

    void
    SetPos( const sf::Vector2f& pos )
    {
        pos_ = pos;
    }

    void
    SetSize( const sf::Vector2f& size )
    {
        size_ = size;
    }

    bool
    PointInside( const sf::Vector2f& point ) const
    {
        return ( ( point.x >= pos_.x && point.x <= pos_.x + size_.x ) &&
                 ( point.y >= pos_.y && point.y <= pos_.y + size_.y ) );
    }

    void
    AddChild( std::unique_ptr<Widget> child )
    {
        child->parent_ = this;
        childern_.push_back( std::move( child ) );
    }

  private:
    virtual void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        DrawSelf( target, states );
        DrawChildren( target, states );
    }

    virtual void
    DrawSelf( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        states.transform.translate( GetParentAbsolutePos() );

        target.draw( rect_, states );
    }

    virtual void
    DrawChildren( sf::RenderTarget& target, sf::RenderStates states ) const
    {
        for ( const auto& child : childern_ )
        {
            target.draw( *child, states );
        }
    }

  protected:
    sf::RectangleShape rect_;

    sf::Vector2f pos_;
    sf::Vector2f size_;

    Widget* parent_;

    std::vector<std::unique_ptr<Widget>> childern_;
};

} // namespace gui
