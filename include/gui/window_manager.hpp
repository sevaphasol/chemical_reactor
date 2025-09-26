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
                   application::Config::WindowStyle )
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

            for ( auto& container : containers_ )
            {
                container->HandleEvents( event );
            }
        }
    }

    void
    Update()
    {
        for ( auto& container : containers_ )
        {
            container->Update();
        }
    }

    void
    Draw()
    {
        window_.clear();

        for ( const auto& container : containers_ )
        {
            window_.draw( *container );
        }

        window_.display();
    }

  protected:
    std::vector<std::unique_ptr<Container>> containers_;

  private:
    sf::RenderWindow window_;
};

} // namespace gui
