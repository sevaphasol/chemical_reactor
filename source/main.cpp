#include <SFML/Graphics/Color.hpp>
#include <exception>
#include <random>

#include "application/window_manager.hpp"

int
main()
{
    std::random_device              rd;
    std::mt19937                    gen( rd() );
    std::uniform_int_distribution<> x_distr( 1.0f, 800.0f );
    std::uniform_int_distribution<> y_distr( 1.0f, 800.0f );
    std::uniform_int_distribution<> v_distr( -1000.0f, 1000.0f );

    application::WindowManager manager;

    // manager.AddSquareMolecule( 50, 0, 400, 100, 0 );
    // manager.AddSquareMolecule( 50, 1100, 400, -300, 0 );
    // manager.AddSquareMolecule( 50, 900, 400, 300, 0 );
    // manager.AddSquareMolecule( 50, 1100, 800, 0, -300 );
    // manager.AddCircleMolecule( 100, 110, 400, -300, 100 );

    for ( int i = 0; i < 100; i++ )
    {
        manager.AddCircleMolecule( 5,
                                   x_distr( gen ),
                                   y_distr( gen ),
                                   v_distr( gen ),
                                   v_distr( gen ) );
    }

    manager.Run();

    return 0;
}
