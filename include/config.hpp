#pragma once

#include "gfx_core/color.hpp"
#include "gfx_core/vector2.hpp"
#include <sys/types.h>

namespace config {

struct Common
{
    struct Font
    {
        static constexpr const char* const  Name  = "assets/JetBrainsMono-Regular.ttf";
        static inline const gfx_core::Color Color = gfx_core::Color::White;
    };
};

struct Reactor
{
    static inline const gfx_core::Vector2f Position        = { 10.0f, 10.0f };
    static inline const gfx_core::Vector2f Size            = { 600.0f, 400.0f };
    static inline const gfx_core::Color    BackGroundColor = { 100, 100, 100 };

    struct Window
    {
        static constexpr uint              Width  = 1200.0f;
        static constexpr uint              Height = 800.0f;
        static constexpr const char* const Title  = "SphereRendering";
    };

    struct Buttons
    {
        static inline const gfx_core::Vector2f Position = { 100.0f, 475.0f };
        static inline const gfx_core::Vector2f Size     = { 600.0f, 300.0f };

        struct Common
        {
            struct Font
            {
                static constexpr const char* const  Name  = config::Common::Font::Name;
                static constexpr uint               Size  = 14;
                static inline const gfx_core::Color Color = config::Common::Font::Color;
            };

            struct Parameters
            {
                static inline const gfx_core::Vector2f Size = { 170.0f, 70.0f };

                struct Color
                {
                    static inline const gfx_core::Color Default = { 100, 100, 100 };
                    static inline const gfx_core::Color Hover   = { 150, 100, 100 };
                    static inline const gfx_core::Color Pressed = { 200, 100, 100 };
                };
            };
        };

        struct Specialization
        {
            struct AddMolecule
            {
                static inline const gfx_core::Vector2f Position = { 25.0f, 25.0f };
            };

            struct RemoveMolecule
            {
                static inline const gfx_core::Vector2f Position = { 225.0f, 25.0f };
            };

            struct MovePiston
            {
                static constexpr float MoveDistance = 10.0f;

                struct Left
                {
                    static inline const gfx_core::Vector2f Position = { 25.0f, 125.0f };
                };

                struct Right
                {
                    static inline const gfx_core::Vector2f Position = { 225.0f, 125.0f };
                };
            };
        };
    };

    struct Graphs
    {
        static inline const gfx_core::Vector2f Position = { 750.0f, 0.0f };
        static inline const gfx_core::Vector2f Size     = { 400.0f, 800.0f };

        struct Common
        {
            struct Font
            {
                static constexpr const char* const  Name  = config::Common::Font::Name;
                static inline const gfx_core::Color Color = config::Common::Font::Color;

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
                static inline const gfx_core::Vector2f Size = { 300.0f, 300.0f };

                static constexpr int GridDivs = 10;

                struct Color
                {
                    static inline const gfx_core::Color Grid = { 100, 100, 100 };
                    static inline const gfx_core::Color Axis = gfx_core::Color::White;
                    static inline const gfx_core::Color Plot = gfx_core::Color::Red;
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
                        struct Horizontal
                        {
                            static constexpr float X = 8.5f;
                            static constexpr float Y = 10.0f;
                        };

                        struct Vertical
                        {
                            static constexpr float X = 60.0f;
                            static constexpr float Y = 8.5f;
                        };
                    };
                };
            };
        };

        struct Specialization
        {
            struct Number
            {
                static inline const gfx_core::Vector2f Position = { 50.0f, 50.0f };
            };

            struct Energy
            {
                static inline const gfx_core::Vector2f Position = { 50.0f, 450.0f };
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

                static inline const gfx_core::Color Color = gfx_core::Color::Red;
            };

            struct Square
            {
                static constexpr float Radius = 5.0f;
                static constexpr float Weight = 2.0f;

                static inline const gfx_core::Color Color = gfx_core::Color::Green;
            };
        };
    };
};

} // namespace config
