#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/container_state.hpp"

namespace gui {
class Widget : public sf::Drawable {
  public:
    Widget( sf::Vector2f pos, sf::Vector2f size ) : pos_( pos ), size_( size ) {}

    virtual void
    HandleEvents( const sf::Event& event ) = 0;

    virtual void
    Update( ContainerState& global_state ) = 0;

    sf::Vector2f
    GetPos() const
    {
        return pos_;
    }

    void
    SetPos( const sf::Vector2f& pos )
    {
        pos_ = pos;
    }

    bool
    PointInside( const sf::Vector2f& point ) const
    {
        return ( ( point.x >= pos_.x && point.x <= pos_.x + size_.x ) &&
                 ( point.y >= pos_.y && point.y <= pos_.y + size_.y ) );
    }

  protected:
    sf::Vector2f pos_;
    sf::Vector2f size_;
};

} // namespace gui
