#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include "application/reactor_state.hpp"

namespace application {

class Widget : public sf::Drawable {
  public:
    Widget() = default;

    virtual void
    HandleEvents() = 0;

    virtual void
    Update( ReactorState& ) = 0;

  private:
    sf::Vector2f pos_;
    sf::Vector2f size_;
};

} // namespace application
