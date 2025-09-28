#pragma once

#include "config.hpp"
#include "gui/button.hpp"
#include "gui/widget.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace reactor {

class ReactorButtons : public gui::Widget {
  public:
    explicit ReactorButtons( sf::Vector2f pos, sf::Vector2f size )
        : ReactorButtons( pos.x, pos.y, size.x, size.y ) {};

    explicit ReactorButtons( float x, float y, float w, float h ) : gui::Widget( x, y, w, h )
    {
        AddChild( std::make_unique<gui::Button>(
            config::Reactor::Buttons::Specialization::AddMolecule::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Add Molecule",
            []() { std::cerr << "Pressed 'Add Molecule' button" << std::endl; } ) );
        AddChild( std::make_unique<gui::Button>(
            config::Reactor::Buttons::Specialization::RemoveMolecule::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Remove Molecule",
            []() { std::cerr << "Pressed 'Remove Molecule' button" << std::endl; } ) );
        AddChild( std::make_unique<gui::Button>(
            config::Reactor::Buttons::Specialization::MovePiston::Left::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Move Pistol Left",
            []() { std::cerr << "Pressed 'Move Pistol Left' button" << std::endl; } ) );
        AddChild( std::make_unique<gui::Button>(
            config::Reactor::Buttons::Specialization::MovePiston::Right::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Move Pistol Right",
            []() { std::cerr << "Pressed 'Move Pistol Right' button" << std::endl; } ) );
    }
};

} // namespace reactor
