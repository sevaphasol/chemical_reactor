#pragma once

#include "gui/graph.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <config.hpp>
#include <string>

namespace reactor {

class EnergyGraph : public gui::Graph {
  public:
    EnergyGraph( sf::Vector2f pos, sf::Vector2f size, const std::string& name )
        : Graph( pos, size, name ) {};

    virtual void
    Update() override;
};

class NumberGraph : public gui::Graph {
  public:
    NumberGraph( sf::Vector2f pos, sf::Vector2f size, const std::string& name )
        : Graph( pos, size, name ) {};

    virtual void
    Update() override;
};

} // namespace reactor
