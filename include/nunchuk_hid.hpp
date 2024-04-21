/*
    nunchuk-hid
    Copyright (C) 2024  sreea1408

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once

#include "nunchuk.hpp"

constexpr uint8_t STATE_SIZE = 3;

class nunchuk_hid
{
public:
    nunchuk_hid();
    void update_if_changed(const uint8_t* const nunchuk_data);

private:
    void set_state(uint8_t btn_state, uint8_t x_state, uint8_t y_state);
    void send_state() const;

    uint8_t state[STATE_SIZE];
    uint8_t previous_nunchuk_data[NUNCHUK_DATA_SIZE];
};
