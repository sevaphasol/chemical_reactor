#pragma once

#include <SFML/Graphics/Color.hpp>
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
    static inline const sf::Color      GridColor            = { 100, 100, 100 };
    static inline const sf::Color      AxisColor            = sf::Color::White;
    static inline const sf::Color      PlotColor            = sf::Color::Red;
    static inline const sf::Color      TextColor            = sf::Color::White;
    static inline const sf::Vector2f   ButtonPos            = { 0.0f, 0.0f };
    static inline const sf::Vector2f   ButtonSize           = { 100.0f, 100.0f };
    static inline const sf::Color      ButtonColor          = sf::Color::Red;
    static inline const sf::Color      ButtonPressedColor   = sf::Color::Green;
    static inline const sf::Color      ButtonHoverColor     = sf::Color::Blue;
    static constexpr int               ButtonFontSize       = 10;
    static inline const sf::Color      ButtonTextColor      = sf::Color::White;
    static constexpr int               GridDivs             = 10;
    static constexpr const char* const FontName             = "assets/JetBrainsMono-Regular.ttf";
    static constexpr uint              TitleFontSize        = 16;
    static constexpr uint              LabelsFontSize       = 12;
    static constexpr float             HorLabelsXPadding    = 8.5f;
    static constexpr float             HorLabelsYPadding    = 10.0f;
    static constexpr float             VerLabelsXPadding    = 60.0f;
    static constexpr float             VerLabelsYPadding    = 8.5f;
    static constexpr float             TitleYPadding        = 30.0f;
    static constexpr double            DeltaTime            = 0.02f;
    static constexpr double            CircleMoleculeRadius = 5.0f;
    static constexpr double            CircleMoleculeWeight = 1.0f;
    static constexpr double            SquareMoleculeWeight = 2.0f;
    static inline const sf::Color      CircleMoleculeColor  = sf::Color::Red;
    static inline const sf::Color      SquareMoleculeColor  = sf::Color::Green;
    static constexpr float             SpeedVelocity        = 3000;
    static constexpr float             SpeedVelocitySq      = SpeedVelocity * SpeedVelocity;
    static constexpr float             StartVelocityMax     = 1000;
};

} // namespace application
