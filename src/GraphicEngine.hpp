/*
 * Copyright (c) 2019-2020, Мира Странная <rsxrwscjpzdzwpxaujrr@yahoo.com>
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

#include <functional>

#include <SFML/Graphics.hpp>

#include <SFGUI/SFGUI.hpp>

#include "Gui/MainMenu.hpp"

namespace mazemaze {

class GraphicEngine {
public:
    void open_window();

    void loop(sfg::SFGUI& sfgui, gui::MainMenu& main_menu);
    void wait_key(std::function<void (const sf::Keyboard::Key)> const& onKey);
    void unwait_key();

    void set_fullscreen(bool fullscreen);
    void set_antialiasing(unsigned int antialiasing);
    void set_vsync(bool vsync);
    void set_on_set_states_callback(std::function<void ()> const& on_set_states);

    sf::RenderWindow& get_window() const;
    int get_width() const;
    int get_height() const;
    unsigned int get_max_antialiasing() const;
    bool get_fullscreen() const;
    bool get_vsync() const;
    bool has_focus() const;

    GraphicEngine(GraphicEngine const&) = delete;
    void operator= (GraphicEngine const&) = delete;

    static GraphicEngine& inst() {
        static GraphicEngine instance;
        return instance;
    }

private:
    GraphicEngine();
    ~GraphicEngine();

    sf::RenderWindow* window;

    sf::Vector2i old_window_pos;
    sf::Vector2u old_window_size;
#ifdef _WIN32
    bool old_maximized;
#endif

    int width;
    int height;
    bool running;
    bool need_reopen;
    bool need_reopen_event;
    bool fullscreen;
    bool vsync;
    bool focus;
    unsigned int max_antialiasing;
    sf::ContextSettings settings;
    sf::VideoMode video_mode;

    sf::Image icon;

    std::function<void (const sf::Keyboard::Key)> on_key_waiting;
    std::function<void ()> on_set_states;

    void open_window(unsigned int width, unsigned int height, bool fullscreen);
    void open_window(sf::VideoMode video_mode, bool fullscreen);
    void update();
    void set_states();
    unsigned int calc_max_antialiasing();
#ifdef _WIN32
    void update_old_maximized();
#endif
    void handle_events(gui::MainMenu& main_menu);
};

}
