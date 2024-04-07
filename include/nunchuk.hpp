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
