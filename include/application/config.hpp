#pragma once

#include <sys/types.h>
#include <SFML/Graphics.hpp>

namespace application {

class Config {
  public:
    static constexpr const char* const Title                = "SphereRendering";
    static constexpr uint              WindowWidth          = 1200.0f;
    static constexpr uint              WindowHeight         = 800.0f;
    static constexpr float             CameraFov            = 1.05;
    static constexpr float             MoveScale            = 0.1f;
    static constexpr float             RotateScale          = 0.04f;
    static constexpr float             DeltaTime            = 0.02f;
    static constexpr float             CircleMoleculeWeight = 1.0f;
    static inline const sf::Color      BackgroundColor      = sf::Color( 16, 16, 16 );
};

} // namespace application
