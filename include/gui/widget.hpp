#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include "gui/container_state.hpp"

namespace gui {

class Widget : public sf::Drawable {
  public:
    Widget( sf::Vector2f pos, sf::Vector2f size ) : pos_( pos ), size_( size ) {}

    virtual void
    HandleEvents( ContainerState& global_state ) = 0;

    virtual void
    Update( ContainerState& global_state ) = 0;

  protected:
    sf::Vector2f pos_;
    sf::Vector2f size_;
};

} // namespace gui
