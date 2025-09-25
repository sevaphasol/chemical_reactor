#pragma once

#include "application/widget.hpp"
#include <memory>
#include <vector>

namespace application {

template<typename GlobalStateType>
class Container {
  public:
    void
    HandleEvents()
    {
        for ( auto& widget : widgets_ )
        {
            widget->HandleEvents();
        }
    }

    void
    Update()
    {
        for ( auto& widget : widgets_ )
        {
            widget->Update( global_state_ );
        }
    }

    void
    AddWidget( const std::unique_ptr<Widget>& widget )
    {
        widgets_.push_back( std::move( widget ) );
    }

  private:
    std::vector<std::unique_ptr<Widget>> widgets_;

    GlobalStateType global_state_;
};

} // namespace application
