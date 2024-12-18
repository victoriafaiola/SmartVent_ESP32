#ifndef PERSIST_H
#define PERSIST_H

//Includes
#include <Preferences.h>
#include "config.h"
#include "functions.h"

//Variables default values
#define DEFAULT_SSID        "Red name"
#define DEFAULT_SSID_PASS   "Password"

void save_config(uint8_t name);
void load_config(void);

#endif
