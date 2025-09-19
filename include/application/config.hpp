#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <sys/types.h>
#include <SFML/Graphics.hpp>

namespace application {

class Config {
  public:
    static constexpr uint              WindowWidth          = 1200.0f;
    static constexpr uint              WindowHeight         = 800.0f;
    static inline const sf::VideoMode  WindowVideoMode      = { WindowWidth, WindowHeight };
    static constexpr const char* const Title                = "SphereRendering";
    static inline const sf::Uint32     WindowStyle          = sf::Style::Close;
    static inline const sf::Vector2f   ReactorPos           = { 0.0f, 0.0f };
    static inline const sf::Vector2f   ReactorSize          = { 600.0f, 800.0f };
    static inline const sf::Vector2f   NumberPlotPos        = { 800.0f, 50.0f };
    static inline const sf::Vector2f   NumberPlotSize       = { 300.0f, 300.0f };
    static inline const sf::Vector2f   EnergyPlotPos        = { 800.0f, 450.0f };
    static inline const sf::Vector2f   EnergyPlotSize       = { 300.0f, 300.0f };
    static constexpr double            DeltaTime            = 0.02f;
    static constexpr double            CircleMoleculeWeight = 1.0f;
    static constexpr double            SquareMoleculeWeight = 2.0f;
};

} // namespace application
