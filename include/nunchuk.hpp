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

constexpr uint8_t NUNCHUK_DATA_SIZE = 6;

class nunchuk
{
public:
    void initialize();
    const uint8_t* const get_data() const;
    void request_data();

private:
    void get_data_from_rx_buffer();
    void send_byte(uint8_t data, uint8_t location) const;
    void send_byte(uint8_t data) const;

    uint8_t data[NUNCHUK_DATA_SIZE];
};
