#pragma once

#include "config.hpp"
#include "gui/container.hpp"
#include <SFML/Graphics.hpp>
#include <reactor/molecule.hpp>
#include <reactor/reactor.hpp>
#include <reactor/graph.hpp>
#include <memory>

namespace gui {

class WindowManager {
  public:
    explicit WindowManager()
        : window_( application::Config::WindowVideoMode,
                   application::Config::Title,
                   application::Config::WindowStyle ),
          desktop_( 0, 0, application::Config::WindowWidth, application::Config::WindowHeight )
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
