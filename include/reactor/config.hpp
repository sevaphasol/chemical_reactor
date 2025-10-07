#pragma once

#include "gfx/core/color.hpp"
#include "gfx/core/vector2.hpp"
#include <sys/types.h>

namespace config {

struct Common
{
    struct Font
    {
        static constexpr const char* const   Name  = "assets/JetBrainsMono-Regular.ttf";
        static inline const gfx::core::Color Color = gfx::core::Color::White;
    };
};

struct Reactor
{
    static inline const gfx::core::Vector2f Position        = { 50.0f, 50.0f };
    static inline const gfx::core::Vector2f Size            = { 625.0f, 400.0f };
    static inline const gfx::core::Color    BackGroundColor = { 100, 100, 100 };

    struct Window
    {
        static constexpr uint              Width  = 1200.0f;
        static constexpr uint              Height = 800.0f;
        static constexpr const char* const Title  = "SphereRendering";
    };

    struct ButtonPanel
    {
        static inline const gfx::core::Vector2f Position = { 100.0f, 475.0f };
        static inline const gfx::core::Vector2f Size     = { 420.0f, 225.0f };

        struct Common
        {
            struct Font
            {
                static constexpr const char* const   Name  = config::Common::Font::Name;
                static constexpr uint                Size  = 14;
                static inline const gfx::core::Color Color = config::Common::Font::Color;
            };

            struct Parameters
            {
                static inline const gfx::core::Vector2f Size = { 170.0f, 70.0f };

                struct Color
                {
                    static inline const gfx::core::Color Default = { 100, 150, 100 };
                    static inline const gfx::core::Color Hover   = { 100, 200, 100 };
                    static inline const gfx::core::Color Pressed = { 100, 250, 100 };
                };
            };
        };

        struct Buttons
        {
            struct AddMolecule
            {
                static inline const gfx::core::Vector2f Position = { 25.0f, 25.0f };
            };

            struct RemoveMolecule
            {
                static inline const gfx::core::Vector2f Position = { 225.0f, 25.0f };
            };

            struct MovePiston
            {
                static constexpr float MoveDistance = 1.0f;

                struct Left
                {
                    static inline const gfx::core::Vector2f Position = { 25.0f, 125.0f };
                };

                struct Right
                {
                    static inline const gfx::core::Vector2f Position = { 225.0f, 125.0f };
                };
            };
        };
    };

    struct GraphPanel
    {
        static inline const gfx::core::Vector2f Position = { 700.0f, 0.0f };
        static inline const gfx::core::Vector2f Size     = { 400.0f, 700.0f };

        struct Common
        {
            struct Font
            {
                static constexpr const char* const   Name  = config::Common::Font::Name;
                static inline const gfx::core::Color Color = config::Common::Font::Color;

                struct Title
                {
                    static constexpr uint Size = 16;
                };

                struct Labels
                {
                    static constexpr uint Size = 12;
                };
            };

            struct Parameters
            {
                static inline const gfx::core::Vector2f Size = { 300.0f, 300.0f };

                static constexpr int GridDivs = 10;

                struct Color
                {
                    static inline const gfx::core::Color Grid = { 100, 100, 100 };
                    static inline const gfx::core::Color Axis = gfx::core::Color::White;
                    static inline const gfx::core::Color Plot = gfx::core::Color::Red;
                };

                struct Title
                {
                    struct Padding
                    {
                        static constexpr float Y = 30.0f;
                    };
                };

                struct Labels
                {
                    struct Padding
                    {
                        static inline const gfx::core::Vector2f Horizontal = { 8.5f, 10.0f };
                        static inline const gfx::core::Vector2f Vertical   = { 60.0f, 8.5f };
                    };
                };
            };
        };

        struct Graphs
        {
            struct Number
            {
                static inline const gfx::core::Vector2f Position = { 25.0f, 20.0f };
            };

            struct Energy
            {
                static inline const gfx::core::Vector2f Position = { 25.0f, 180.0f };
            };
        };
    };

    struct Physics
    {
        static constexpr double DeltaTime       = 0.02f;
        static constexpr float  SpeedVelocity   = 3000;
        static constexpr float  SpeedVelocitySq = SpeedVelocity * SpeedVelocity;

        struct Molecule
        {
            static constexpr float StartVelocityMax = 1000;

            struct Circle
            {
                static constexpr float Radius = 5.0f;
                static constexpr float Weight = 1.0f;

                static inline const gfx::core::Color Color = gfx::core::Color::Red;
            };

            struct Square
            {
                static constexpr float Radius = 5.0f;
                static constexpr float Weight = 2.0f;

                static inline const gfx::core::Color Color = gfx::core::Color::Green;
            };
        };
    };
};

} // namespace config
