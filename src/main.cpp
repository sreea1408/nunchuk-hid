#include <Arduino.h>

#include "nunchuk.hpp"
#include "nunchuk_hid.hpp"

nunchuk_hid nunchuk_hid_dev;
nunchuk nunchuk_dev;

void setup()
{
    nunchuk_dev.initialize();
}

void loop()
{
    nunchuk_dev.request_data();
    nunchuk_hid_dev.update_if_changed(nunchuk_dev.get_data());
    delayMicroseconds(500);
}
