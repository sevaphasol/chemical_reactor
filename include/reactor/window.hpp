#pragma once

#include "config.hpp"
#include "gui/button.hpp"
#include "gui/window_manager.hpp"
#include "reactor/graph.hpp"
#include "reactor/reactor.hpp"
#include <memory>

void
foo()
{
    std::cerr << "TestButton" << std::endl;
}

namespace reactor {

class ReactorWindow : public gui::WindowManager {
  public:
    ReactorWindow()
    {
        desktop_.AddChild( std::make_unique<Reactor>( application::Config::ReactorPos,
                                                      application::Config::ReactorSize ) );

        desktop_.AddChild( std::make_unique<EnergyGraph>( application::Config::NumberPlotPos,
                                                          application::Config::NumberPlotSize,
                                                          "Number" ) );
        desktop_.AddChild( std::make_unique<NumberGraph>( application::Config::EnergyPlotPos,
                                                          application::Config::EnergyPlotSize,
                                                          "Energy" ) );

        desktop_.AddChild( std::make_unique<gui::Button>(
            application::Config::AddMolButtonPos,
            application::Config::ButtonSize,
            "Add Molecule",
            []() { std::cerr << "Pressed 'Add Molecule' button" << std::endl; } ) );
        desktop_.AddChild( std::make_unique<gui::Button>(
            application::Config::RemoveMolButtonPos,
            application::Config::ButtonSize,
            "Remove Molecule",
            []() { std::cerr << "Pressed 'Remove Molecule' button" << std::endl; } ) );
        desktop_.AddChild( std::make_unique<gui::Button>(
            application::Config::MovePistonLeftButtonPos,
            application::Config::ButtonSize,
            "Move Pistol Left",
            []() { std::cerr << "Pressed 'Move Pistol Left' button" << std::endl; } ) );
        desktop_.AddChild( std::make_unique<gui::Button>(
            application::Config::MovePistonRightButtonPos,
            application::Config::ButtonSize,
            "Move Pistol Right",
            []() { std::cerr << "Pressed 'Move Pistol Right' button" << std::endl; } ) );
    }
};

} // namespace reactor
