#pragma once

#include "gui/draggable.hpp"
#include "gui/text.hpp"
#include "gui/widget.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <config.hpp>
#include <iostream>
#include <string>

namespace gui {

class Button : public Widget, public gui::Draggable<Button> {
  public:
    explicit Button( sf::Vector2f pos, sf::Vector2f size, const std::string& text )
        : Widget( pos, size ), pressed_( false ), hover_( false ),
          text_( pos,
                 text,
                 config::Reactor::Buttons::Common::Font::Name,
                 config::Reactor::Buttons::Common::Font::Size,
                 config::Reactor::Buttons::Common::Font::Color )
    {
        rect_.setPosition( pos_ );
        rect_.setSize( size_ );
        rect_.setFillColor( config::Reactor::Buttons::Common::Parameters::Color::Default );
    }

    void
    HandleEvents( const sf::Event& event ) override
    {
        HandleDragEvent( event );

        pressed_ = false;

        switch ( event.type )
        {
            case sf::Event::MouseButtonPressed:
                OnMousePress( event );
                break;
            case sf::Event::MouseMoved:
                OnMouseMove( event );
                break;
            default:
                break;
        };
    }

    void
    OnMousePress( const sf::Event& event )
    {
        switch ( event.mouseButton.button )
        {
            case sf::Mouse::Left:
                pressed_ = hover_;
                break;
            case sf::Mouse::Right:
                HandleDragEvent( event );
                break;
            default:
                break;
        }
    }

    void
    OnMouseMove( const sf::Event& event )
    {
        hover_ = PointInside( sf::Vector2f( event.mouseMove.x, event.mouseMove.y ) );
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

    bool
    IsPressed() const
    {
        return pressed_;
    }

  private:
    void
    draw( sf::RenderTarget& target, sf::RenderStates states ) const override
    {
        states.transform.translate( GetParentAbsolutePos() );

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
        text_.MoveInCenterOfRect( rect_.getPosition(), rect_.getSize() );
    }

  private:
    Text text_;

    bool pressed_;
    bool hover_;
};

} // namespace gui
