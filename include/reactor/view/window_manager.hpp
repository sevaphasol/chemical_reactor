#include "gfx/ui/window_manager.hpp"

#include "reactor/model/reactor.hpp"
#include "reactor/controller/reactor.hpp"

namespace reactor {
namespace view {

class WindowManager : public gfx::ui::WindowManager {
  public:
    WindowManager( float w, float h, const char* title );

  private:
    model::Reactor      model_;
    controller::Reactor controller_;
};

} // namespace view
} // namespace reactor
