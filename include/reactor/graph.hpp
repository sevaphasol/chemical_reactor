#pragma once

#include "gui/container_state.hpp"
#include "gui/graph.hpp"
#include "reactor/reactor.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <config.hpp>

namespace reactor {

class EnergyGraph : public gui::Graph {
  public:
    EnergyGraph( sf::Vector2f pos, sf::Vector2f size, const char* name )
        : Graph( pos, size, name ) {};

    virtual void
    Update( gui::ContainerState& state ) override
    {
        UpdateGraphRoutine();

        ReactorState& reactor_state = dynamic_cast<ReactorState&>( state );

        AddPoint( reactor_state.elapsed_time, reactor_state.full_energy );
    }
};

class NumberGraph : public gui::Graph {
  public:
    NumberGraph( sf::Vector2f pos, sf::Vector2f size, const char* name )
        : Graph( pos, size, name ) {};

    virtual void
    Update( gui::ContainerState& state ) override
    {
        UpdateGraphRoutine();

        ReactorState& reactor_state = dynamic_cast<ReactorState&>( state );

        AddPoint( reactor_state.elapsed_time, reactor_state.n_molecules );
    }
};

} // namespace reactor
