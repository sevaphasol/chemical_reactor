#pragma once

#include "gui/draggable.hpp"
#include "gui/widget.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <string>
#include <config.hpp>

namespace gui {

class Button : public Widget, public gui::Draggable<Button> {
  public:
    using FunctorType = std::function<void()>;

    explicit Button( sf::Vector2f       pos,
                     sf::Vector2f       size,
                     const std::string& text,
                     FunctorType        functor )
        : Widget( pos, size ), functor_( functor ), pressed_( false ), hover_( false )
    {
        font_.loadFromFile( config::Reactor::Buttons::Common::Font::Name );

        rect_.setPosition( pos_ );
        rect_.setSize( size_ );
        rect_.setFillColor( config::Reactor::Buttons::Common::Parameters::Color::Default );

        text_.setFont( font_ );
        text_.setString( text );
        text_.setCharacterSize( config::Reactor::Buttons::Common::Font::Size );
        text_.setFillColor( config::Reactor::Buttons::Common::Font::Color );
    }

    void
    HandleEvents( const sf::Event& event ) override
    {
        HandleDragEvent( event );

        bool mouse_pressed = ( event.type == sf::Event::MouseButtonPressed &&
                               event.mouseButton.button == sf::Mouse::Left );

        sf::Vector2i mouse_pos = ( event.type == sf::Event::MouseMoved )
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
    Update() override
    {
        UpdateRectPosition();
        UpdateTextPosition();

        sf::Color button_color;

        if ( pressed_ )
        {
            button_color = config::Reactor::Buttons::Common::Parameters::Color::Pressed;
        } else if ( hover_ )
        {
            button_color = config::Reactor::Buttons::Common::Parameters::Color::Hover;
        } else
        {
            button_color = config::Reactor::Buttons::Common::Parameters::Color::Default;
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
    UpdateRectPosition()
    {
        rect_.setPosition( pos_ );
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
