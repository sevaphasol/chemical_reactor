#include "reactor/graph.hpp"
#include "reactor/reactor.hpp"
#include "reactor/reactor_graphs.hpp"

namespace reactor {

float
ReactorGraphs::GetElapsedTime()
{
    auto* reactor_info = static_cast<Reactor*>( parent_ );

    return reactor_info->GetElapsedTime();
}

float
ReactorGraphs::GetMoleculesAmount()
{
    auto* reactor_info = static_cast<Reactor*>( parent_ );

    return reactor_info->GetMoleculesAmount();
}

float
ReactorGraphs::GetFullEnergy()
{
    auto* reactor_info = static_cast<Reactor*>( parent_ );

    return reactor_info->GetFullEnergy();
}

void
EnergyGraph::Update()
{
    std::cerr << "Updating EnergyGraph... " << std::endl;

    UpdateGraphRoutine();

    auto* reactor_info = static_cast<ReactorGraphs*>( parent_ );

    AddPoint( reactor_info->GetElapsedTime(), reactor_info->GetFullEnergy() );
}

void
NumberGraph::Update()
{
    UpdateGraphRoutine();

    auto* reactor_info = static_cast<ReactorGraphs*>( parent_ );

    AddPoint( reactor_info->GetElapsedTime(), reactor_info->GetMoleculesAmount() );
}

} // namespace reactor
