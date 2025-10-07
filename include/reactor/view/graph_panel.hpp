#pragma once

#include "gfx/core/rectangle_shape.hpp"
#include "gfx/ui/widget.hpp"
#include "reactor/model/graph_panel.hpp"

namespace reactor {
namespace view {

class GraphPanel : public gfx::ui::Widget {
  public:
    explicit GraphPanel( model::GraphPanel& model );

    virtual bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;

  private:
    enum GraphCode {
        Energy = 0,
        Number = 1,
    };

    void
    setupGraph( model::Graph& model, const gfx::core::Vector2f& pos, const char* title );

    virtual void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    model::GraphPanel& model_;

    gfx::core::RectangleShape border_;
};

} // namespace view
} // namespace reactor
