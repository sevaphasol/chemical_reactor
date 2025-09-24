#pragma once

#include "application/config.hpp"
#include "application/widget.hpp"
#include <SFML/Graphics.hpp>
#include <application/molecule.hpp>
#include <application/reactor.hpp>
#include <application/graph.hpp>
#include <memory>

namespace application {

class WindowManager {
  public:
    WindowManager()
        : window_( Config::WindowVideoMode, Config::Title, Config::WindowStyle ),
          number_plot_( Config::NumberPlotPos, Config::NumberPlotSize, "Number" ),
          energy_plot_( Config::EnergyPlotPos, Config::EnergyPlotSize, "Energy" )
    {
        window_.setFramerateLimit( 60 );
        widgets_.emplace_back(
            std::make_unique<Reactor>( Config::ReactorPos, Config::ReactorSize ) );
    }

    void
    Run()
    {
        double time = 0;

        while ( window_.isOpen() )
        {
            HandleEvents();
            Render( time );
            Draw();

            time += Config::DeltaTime;
        }
    }

    void
    AddCircleMolecule( double r, double x, double y, double vx, double vy )
    {
        // widgets_[0].AddCircleMolecule( r, x, y, vx, vy );
    }

    void
    AddSquareMolecule( double r, double x, double y, double vx, double vy )
    {
        // reactor_.AddSquareMolecule( r, x, y, vx, vy );
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

            for ( auto& widget : widgets_ )
            {
                widget->HandleEvents();
            }
        }
    }

    void
    Render( double time )
    {
        for ( auto& widget : widgets_ )
        {
            widget->Render( Config::DeltaTime );
        }

        number_plot_.AddPoint( time, time );
        energy_plot_.AddPoint( time, time );
    }

    void
    Draw()
    {
        window_.clear();

        for ( const auto& widget : widgets_ )
        {
            window_.draw( *widget );
        }

        window_.draw( number_plot_ );
        window_.draw( energy_plot_ );

        window_.display();
    }

  private:
    sf::RenderWindow window_;

    std::vector<std::unique_ptr<Widget>> widgets_;

    Graph number_plot_;
    Graph energy_plot_;
};

} // namespace application
