#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace application {

class Button : public sf::Drawable {

    enum State {
        UNPRESSED,
        PRESSED,
        BLINK,
    };

  public:
    Button( const sf::Vector2f& position, const sf::Vector2f& size ) : rect_( position, size ) {};

    bool
    IsTriggered()
    {
        return false;
    }

    void
    Click()
    {
    }

  private:
    void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override {};

  private:
    bool               clicked_;
    sf::Rect<float>    rect_;
    sf::RectangleShape shape_;
};

} // namespace application
