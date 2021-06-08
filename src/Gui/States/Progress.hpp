/*
 * Copyright (c) 2020-2021, Мира Странная <rsxrwscjpzdzwpxaujrr@yahoo.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../State.hpp"

namespace mazemaze {

class Game;

namespace gui {

class MainMenu;

namespace states {

class Progress : public State {
public:
    const char max_size_chars = 4;

    explicit Progress(MainMenu& main_menu);
    ~Progress() override;

    void tick(void*, float delta_time) override;
    void reset_text() override;
    void setGame(Game* game);

private:
    MainMenu& main_menu;

    sfg::Button::Ptr back_button;
    sfg::Label::Ptr  maze_size_label;
    sfg::ProgressBar::Ptr progress_bar;

    Game* game;

    void init_signals();
};

}
}
}
