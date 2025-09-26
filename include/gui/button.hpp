#pragma once

#include "gui/widget.hpp"
#include "gui/container_state.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>
#include <config.hpp>

namespace gui {

class Button : public Widget {
  public:
    using FunctorType = std::function<void()>;

    Button( sf::Vector2f pos, sf::Vector2f size, const std::string& text, FunctorType functor )
        : Widget( pos, size ), functor_( functor ), pressed_( false ), hover_( false )
    {
        font_.loadFromFile( application::Config::FontName );

        rect_.setPosition( pos_ );
        rect_.setSize( size_ );
        rect_.setFillColor( application::Config::ButtonColor );

        text_.setFont( font_ );
        text_.setString( text );
        text_.setCharacterSize( application::Config::ButtonFontSize );
        text_.setFillColor( application::Config::ButtonTextColor );
        UpdateTextPosition();
    }

    void
    HandleEvents( const sf::Event& event ) override
    {
        bool         mouse_pressed = ( event.type == sf::Event::MouseButtonPressed );
        sf::Vector2i mouse_pos     = ( event.type == sf::Event::MouseMoved )
                                         ? sf::Vector2i( event.mouseMove.x, event.mouseMove.y )
                                         : sf::Vector2i( event.mouseButton.x, event.mouseButton.y );

        bool is_hover = IsMouseOver( mouse_pos );

        if ( mouse_pressed )
        {
            if ( is_hover && !pressed_ )
            {
                pressed_ = true;
            }
        } else
        {
            if ( pressed_ && is_hover )
            {
                if ( functor_ )
                {
                    functor_();
                }
            }

            pressed_ = false;
        }

        hover_ = is_hover;
    }

    void
    Update( ContainerState& container_state ) override
    {
        sf::Color button_color;

        if ( pressed_ )
        {
            button_color = application::Config::ButtonPressedColor;
        } else if ( hover_ )
        {
            button_color = application::Config::ButtonHoverColor;
        } else
        {
            button_color = application::Config::ButtonColor;
        }

        rect_.setFillColor( button_color );
    }

  private:
    void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        target.draw( rect_, states );
        target.draw( text_, states );
    }

    void
    UpdateTextPosition()
    {
        const sf::FloatRect text_bounds = text_.getLocalBounds();
        text_.setOrigin( text_bounds.left + text_bounds.width / 2.0f,
                         text_bounds.top + text_bounds.height / 2.0f );
        text_.setPosition( pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f );
    }

    bool
    IsMouseOver( const sf::Vector2i& mouse_pos ) const
    {
        return ( mouse_pos.x >= pos_.x && mouse_pos.x <= pos_.x + size_.x &&
                 mouse_pos.y >= pos_.y && mouse_pos.y <= pos_.y + size_.y );
    }

  private:
    sf::RectangleShape rect_;
    sf::Text           text_;
    sf::Font           font_;

    bool pressed_;
    bool hover_;

    FunctorType functor_;
};

} // namespace gui
