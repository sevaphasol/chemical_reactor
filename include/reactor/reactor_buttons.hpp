#pragma once

#include "config.hpp"
#include "gui/button.hpp"
#include "gui/widget.hpp"

namespace reactor {

class ReactorButtons : public gui::Widget {
  public:
    explicit ReactorButtons( gfx_core::Vector2f pos, gfx_core::Vector2f size )
        : ReactorButtons( pos.x, pos.y, size.x, size.y ) {};

    explicit ReactorButtons( float x, float y, float w, float h ) : gui::Widget( x, y, w, h )
    {
        add_mol_button_ =
            AddButtonAndGetAccess( config::Reactor::Buttons::Specialization::AddMolecule::Position,
                                   config::Reactor::Buttons::Common::Parameters::Size,
                                   "Add Molecule" );

        rm_mol_button_ = AddButtonAndGetAccess(
            config::Reactor::Buttons::Specialization::RemoveMolecule::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Remove Molecule" );

        mv_pistol_l_button_ = AddButtonAndGetAccess(
            config::Reactor::Buttons::Specialization::MovePiston::Left::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Move Pistol Left" );

        mv_pistol_r_button_ = AddButtonAndGetAccess(
            config::Reactor::Buttons::Specialization::MovePiston::Right::Position,
            config::Reactor::Buttons::Common::Parameters::Size,
            "Move Pistol Right" );
    }

    virtual void
    Update() override;

  private:
    gui::Button*
    AddButtonAndGetAccess( const gfx_core::Vector2f& button_pos,
                           const gfx_core::Vector2f& button_size,
                           const std::string&        button_name )
    {
        auto button_unique_p =
            std::make_unique<gui::Button>( button_pos, button_size, button_name );

        gui::Button* button_dirty_p = button_unique_p.get();

        AddChild( std::move( button_unique_p ) );

        return button_dirty_p;
    }

  private:
    gui::Button* add_mol_button_;
    gui::Button* rm_mol_button_;
    gui::Button* mv_pistol_l_button_;
    gui::Button* mv_pistol_r_button_;
};

} // namespace reactor
