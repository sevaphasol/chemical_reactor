#pragma once

#include "application/config.hpp"
#include <SFML/Graphics.hpp>
#include <application/molecule.hpp>
#include <application/reactor.hpp>
#include <application/graph.hpp>

namespace application {

class WindowManager {
  public:
    WindowManager()
        : window_( Config::WindowVideoMode, Config::Title, Config::WindowStyle ),
          reactor_( Config::ReactorPos, Config::ReactorSize ),
          number_plot_( Config::NumberPlotPos, Config::NumberPlotSize, "Number" ),
          energy_plot_( Config::EnergyPlotPos, Config::EnergyPlotSize, "Energy" )
    {
        window_.setFramerateLimit( 60 );
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
        reactor_.AddCircleMolecule( r, x, y, vx, vy );
    }

    void
    AddSquareMolecule( double r, double x, double y, double vx, double vy )
    {
        reactor_.AddSquareMolecule( r, x, y, vx, vy );
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

            int left  = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) );
            int right = int( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) );

            reactor_.MovePiston( ( right - left ) * 10 );
        }
    }

    void
    Render( double time )
    {
        reactor_.Render( Config::DeltaTime );
        number_plot_.AddPoint( time, reactor_.GetMoleculesCount() );
        energy_plot_.AddPoint( time, reactor_.CalcSumEnergy() / 1e+6 );
    }

    void
    Draw()
    {
        window_.clear();

        window_.draw( reactor_ );
        window_.draw( number_plot_ );
        window_.draw( energy_plot_ );

        window_.display();
    }

  private:
    sf::RenderWindow window_;

    Reactor reactor_;
    Graph   number_plot_;
    Graph   energy_plot_;
};

} // namespace application
