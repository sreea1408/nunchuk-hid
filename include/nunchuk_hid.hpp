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
