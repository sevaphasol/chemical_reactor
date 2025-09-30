#include "config.hpp"
#include "reactor/reactor.hpp"
#include "reactor/reactor_buttons.hpp"

namespace reactor {

void
ReactorButtons::Update()
{
    Reactor* reactor = static_cast<Reactor*>( parent_ );

    if ( add_mol_button_->IsPressed() )
    {
        reactor->AddRandomCircleMolecule();
    }

    if ( rm_mol_button_->IsPressed() )
    {
        reactor->RemoveMolecule();
    }

    if ( mv_pistol_l_button_->IsPressed() )
    {
        reactor->MovePiston( -config::Reactor::Buttons::Specialization::MovePiston::MoveDistance );
    }

    if ( mv_pistol_r_button_->IsPressed() )
    {
        reactor->MovePiston( config::Reactor::Buttons::Specialization::MovePiston::MoveDistance );
    }

    UpdateChildren();
}

} // namespace reactor
