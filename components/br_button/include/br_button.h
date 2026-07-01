#pragma once

// Structs for button config
typedef void (*button_callback_t)(void *args);

typedef struct {
    button_callback_t onpress;
    void *callback_args;
} button_config_t;

// function for button setup (who could have guessed...)
void br_button_setup(button_config_t *button_config);

