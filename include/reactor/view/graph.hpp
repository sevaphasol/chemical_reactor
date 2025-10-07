#pragma once

#include "gfx/core/font.hpp"
#include "gfx/core/text.hpp"
#include "gfx/core/vertex_array.hpp"
#include "gfx/ui/widget.hpp"
#include "reactor/model/graph.hpp"

#include <string>

namespace reactor {
namespace view {

class Graph : public gfx::ui::Widget {
  public:
    explicit Graph( model::Graph&              model,
                    const std::string&         title,
                    const gfx::core::Vector2f& pos,
                    const gfx::core::Vector2f& size );
    bool
    onIdleSelf( const gfx::core::Event::IdleEvent& event ) override;

  private:
    void
    drawSelf( gfx::core::Window& window, gfx::core::Transform transform ) const override;

    void
    updateFromModel();
    void
    recalculateSteps();
    float
    logicalToScreenX( float x ) const;
    float
    logicalToScreenY( float y ) const;
    void
    drawGridLines( gfx::core::Window& window, gfx::core::Transform transform ) const;
    void
    drawAxisLabels( gfx::core::Window& window, gfx::core::Transform transform ) const;
    void
    updateTitlePosition();

    model::Graph&           model_;
    gfx::core::Font         font_;
    gfx::core::Text         title_text_;
    mutable gfx::core::Text axis_labels_text_;

    gfx::core::Vector2f    step_{ 1, 1 };
    gfx::core::VertexArray plot_;
};

} // namespace view
} // namespace reactor
