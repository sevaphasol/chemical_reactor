// text.hpp — обновлённая версия
#pragma once

#include "gui/widget.hpp"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace gui {

class Text : public Widget {
  public:
    explicit Text( const sf::Vector2f& pos,
                   const std::string&  text,
                   const std::string&  font_name,
                   const sf::Uint32&   font_size,
                   const sf::Color&    text_color )
        : Widget( pos )
    {
        font_.loadFromFile( font_name );
        text_.setFont( font_ );
        text_.setCharacterSize( font_size );
        text_.setString( text );
        text_.setFillColor( text_color );
    }

    explicit Text( const sf::Vector2f& pos,
                   const std::string&  text,
                   const sf::Font&     font,
                   const sf::Uint32&   font_size,
                   const sf::Color&    text_color )
        : Widget( pos ), font_( font ), text_( text, font, font_size )
    {
        text_.setFillColor( text_color );
    }

    void
    SetString( const std::string& str )
    {
        text_.setString( str );
    }

    sf::FloatRect
    GetLocalBounds() const
    {
        return text_.getLocalBounds();
    }

    void
    MoveInCenterOfRect( const sf::Vector2f& rect_pos, const sf::Vector2f& rect_size )
    {
        const sf::FloatRect text_bounds = text_.getLocalBounds();
        text_.setOrigin( text_bounds.left + text_bounds.width / 2.0f,
                         text_bounds.top + text_bounds.height / 2.0f );
        text_.setPosition( rect_pos.x + rect_size.x / 2.0f, rect_pos.y + rect_size.y / 2.0f );
    }

    virtual void
    DrawSelf( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        states.transform.translate( GetParentAbsolutePos() );
        target.draw( text_, states );
    }

  private:
    sf::Font font_;
    sf::Text text_;
};

} // namespace gui
