#include "reactor/graph.hpp"
#include "reactor/reactor.hpp"
#include "reactor/reactor_graphs.hpp"

namespace reactor {

float
ReactorGraphs::GetElapsedTime()
{
    Reactor* reactor_info = static_cast<Reactor*>( parent_ );

    return reactor_info->GetElapsedTime();
}

float
ReactorGraphs::GetMoleculesAmount()
{
    Reactor* reactor_info = static_cast<Reactor*>( parent_ );

    return reactor_info->GetMoleculesAmount();
}

float
ReactorGraphs::GetFullEnergy()
{
    Reactor* reactor_info = static_cast<Reactor*>( parent_ );

    return reactor_info->GetFullEnergy();
}

void
EnergyGraph::Update()
{
    UpdateGraphRoutine();

    ReactorGraphs* reactor_info = static_cast<ReactorGraphs*>( parent_ );

    AddPoint( reactor_info->GetElapsedTime(), reactor_info->GetFullEnergy() );
}

void
NumberGraph::Update()
{
    UpdateGraphRoutine();

    ReactorGraphs* reactor_info = static_cast<ReactorGraphs*>( parent_ );

    AddPoint( reactor_info->GetElapsedTime(), reactor_info->GetMoleculesAmount() );
}

} // namespace reactor
