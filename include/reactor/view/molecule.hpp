#pragma once

#include "gfx/core/drawable.hpp"
#include "gfx/core/circle_shape.hpp"
#include "gfx/core/rectangle_shape.hpp"

#include "reactor/model/molecule.hpp"

namespace reactor {
namespace view {

class Molecule : public gfx::core::Drawable {
  public:
    Molecule( const model::Molecule& model );
    virtual ~Molecule() = default;

    void
    updateFromModel( const model::Molecule& model );

    void
    draw( gfx::core::Window& window, gfx::core::Transform transform ) const override;

  private:
    const model::Molecule&    model_ref_;
    gfx::core::CircleShape    circle_shape_;
    gfx::core::RectangleShape rect_shape_;
    gfx::core::Drawable*      current_shape_ = nullptr;
};

} // namespace view
} // namespace reactor
