#pragma once

#include "gui/draggable.hpp"
#include "gui/text.hpp"
#include "gui/widget.hpp"
#include "config.hpp"
#include <string>

namespace gui {

class Button : public Widget, public gui::Draggable<Button> {
  public:
    explicit Button( gfx_core::Vector2f pos, gfx_core::Vector2f size, const std::string& text )
        : Widget( pos, size ), pressed_( false ), hover_( false ),
          text_( pos,
                 text,
                 config::Reactor::Buttons::Common::Font::Name,
                 config::Reactor::Buttons::Common::Font::Size,
                 config::Reactor::Buttons::Common::Font::Color )
    {
        rect_.setFillColor( config::Reactor::Buttons::Common::Parameters::Color::Default );
    }

    void
    HandleEvents( const gfx_core::Event& event ) override
    {
        // std::cerr << "HandleEvents() from Button" << std::endl;

        HandleDragEvent( event );

        pressed_ = false;

        switch ( event.type )
        {
            case gfx_core::Event::MouseButtonPressed:
                OnMousePress( event );
                break;
            case gfx_core::Event::MouseMoved:
                OnMouseMove( event );
                break;
            default:
                break;
        };
    }

    void
    OnMousePress( const gfx_core::Event& event )
    {
        // std::cerr << "OnMousePress() from Button" << std::endl;

        switch ( event.mouse_button.button )
        {
            case gfx_core::Mouse::Left:
                // std::cerr << "case gfx_core::Mouse::Left: from Button" << std::endl;
                pressed_ = hover_;
                // std::cerr << "pressed_ = " << pressed_ << std::endl;
                break;
            case gfx_core::Mouse::Right:
                HandleDragEvent( event );
                break;
            default:
                break;
        }
    }

    void
    OnMouseMove( const gfx_core::Event& event )
    {
        hover_ = PointInside( gfx_core::Vector2f( event.mouse_move.x, event.mouse_move.y ) );
    }

    void
    Update() override
    {
        UpdateTextPosition();

        gfx_core::Color button_color;

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
    DrawChildren( gfx_core::Window& window, gfx_core::Transform transform ) const override
    {
        transform.translate( GetPos() );

        window.draw( text_, transform );
    }

    void
    UpdateTextPosition()
    {
        text_.MoveInCenterOfRect( { 0, 0 }, rect_.getSize() );
    }

  private:
    Text text_;

    bool pressed_;
    bool hover_;
};

} // namespace gui
