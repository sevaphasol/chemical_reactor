#pragma once

#include "gui/container.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <reactor/molecule.hpp>
#include <reactor/reactor.hpp>
#include <reactor/graph.hpp>

namespace gui {

class WindowManager {
  public:
    explicit WindowManager( float w, float h, const std::string& title, const sf::Uint32& style )
        : window_( sf::VideoMode( w, h ), title, style ), desktop_( 0, 0, w, h )
    {
        window_.setFramerateLimit( 60 );
    }

    virtual ~WindowManager() = default;

    void
    Run()
    {
        while ( window_.isOpen() )
        {
            HandleEvents();
            Update();
            Draw();
        }
    }

  private:
    void
    HandleEvents()
    {
        sf::Event event;

        while ( window_.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window_.close();
            }

            desktop_.HandleEvents( event );
        }
    }

    void
    Update()
    {
        desktop_.Update();
    }

    void
    Draw()
    {
        window_.clear();
        window_.draw( desktop_ );
        window_.display();
    }

  protected:
    Widget desktop_;

  private:
    sf::RenderWindow window_;
};

} // namespace gui
