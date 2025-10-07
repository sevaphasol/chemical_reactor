#include "reactor/view/graph_panel.hpp"
#include "gfx/core/vector2.hpp"
#include "gfx/core/window.hpp"
#include "reactor/config.hpp"
#include "reactor/view/graph.hpp"

#include <memory>

namespace reactor {
namespace view {

GraphPanel::GraphPanel( model::GraphPanel& model ) : model_( model )
{
    setDraggable( true );

    setPosition( config::Reactor::GraphPanel::Position );
    setSize( config::Reactor::GraphPanel::Size );

    border_.setSize( getSize() );
    border_.setFillColor( gfx::core::Color::Transparent );
    border_.setOutlineColor( gfx::core::Color::Red );
    border_.setOutlineThickness( 2.0f );

    setupGraph( model_.getEnergyModel(),
                config::Reactor::GraphPanel::Graphs::Energy::Position,
                "Energy" );

    setupGraph( model_.getNumberModel(),
                config::Reactor::GraphPanel::Graphs::Number::Position,
                "Number" );
}

bool
GraphPanel::onIdleSelf( const gfx::core::Event::IdleEvent& event )
{
    children_[Energy]->onIdle( event );
    children_[Number]->onIdle( event );

    return false;
}

void
GraphPanel::setupGraph( model::Graph& model, const gfx::core::Vector2f& pos, const char* title )
{
    addChild(
        std::make_unique<view::Graph>( model,
                                       title,
                                       pos,
                                       config::Reactor::GraphPanel::Common::Parameters::Size ) );
}

void
GraphPanel::drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const
{
    window.draw( border_, transform );
}

} // namespace view
} // namespace reactor
