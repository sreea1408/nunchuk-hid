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
