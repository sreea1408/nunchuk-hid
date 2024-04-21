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

#include <Arduino.h>
#include <Wire.h>

#include "nunchuk.hpp"

constexpr uint8_t DEVICE_ADDRESS = 0x52;

void nunchuk::initialize()
{
    Wire.begin();
    send_byte(0x55, 0xF0);
    send_byte(0x00, 0xFB);
    send_byte(0xFA);
    delayMicroseconds(200);
    Wire.requestFrom(DEVICE_ADDRESS, NUNCHUK_DATA_SIZE);
    get_data_from_rx_buffer();
}

void nunchuk::request_data()
{
    send_byte(0x00);
    delayMicroseconds(200);
    Wire.requestFrom(DEVICE_ADDRESS, NUNCHUK_DATA_SIZE);
    get_data_from_rx_buffer();
}

const uint8_t* const nunchuk::get_data() const
{
    return data;
}

void nunchuk::get_data_from_rx_buffer()
{
    for (uint8_t i = 0; Wire.available() && (i < NUNCHUK_DATA_SIZE); ++i)
    {
        data[i] = Wire.read();
    }
}

void nunchuk::send_byte(const uint8_t data, const uint8_t location) const
{
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(location);
    Wire.write(data);
    Wire.endTransmission();
}

void nunchuk::send_byte(const uint8_t data) const
{
    Wire.beginTransmission(DEVICE_ADDRESS);
    Wire.write(data);
    Wire.endTransmission();
}
