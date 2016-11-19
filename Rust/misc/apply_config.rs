let result = if self.tapping {
    unsafe { libinput_device_config_tap_set_enabled(device, LIBINPUT_CONFIG_TAP_ENABLED) };
} else {
    unsafe { libinput_device_config_tap_set_enabled(device, LIBINPUT_CONFIG_TAP_DISABLED) };
}
// TODO: find result value, return Error
/*if result < 0 {
    return false;
}*/

result = match self.tap_map {
    TapMap::None => 0,
    TapMap::LeftRightMiddle => unsafe {
        libinput_device_config_tap_set_button_map(device, LIBINPUT_CONFIG_TAP_MAP_LRM)
    },
    TapMap::LeftMiddleRight => unsafe {
        libinput_device_config_tap_set_button_map(device, LIBINPUT_CONFIG_TAP_MAP_LMR)
    }
}

result = if self.drag {
    libinput_device_config_tap_set_drag_enabled(device, LIBINPUT_CONFIG_DRAG_ENABLED);
} else {
    libinput_device_config_tap_set_drag_enabled(device, LIBINPUT_CONFIG_DRAG_DISABLED);
}

result = if self.drag_lock {
    libinput_device_config_tap_set_drag_enabled(device, LIBINPUT_CONFIG_DRAG_LOCK_ENABLED);
} else {
    libinput_device_config_tap_set_drag_enabled(device, LIBINPUT_CONFIG_DRAG_LOCK_DISABLED);
}

result = if self.natural_scroll {
    libinput_device_config_scroll_set_natural_scroll_enabled(device, 1);
} else {
    libinput_device_config_scroll_set_natural_scroll_enabled(device, 0);
}

result = if self.left_handed {
    libinput_device_config_left_handed_set(device, 1);
} else {
    libinput_device_config_left_handed_set(device, 0);
}

result = if self.middle_button {
    libinput_device_config_middle_emulation_set_enabled(device, 1);
} else {
    libinput_device_config_middle_emulation_set_enabled(device, 0);
}

result = is self.disabled_while_typing {
    libinput_device_config_dwt_set_enabled(device, 1);
} else {
    libinput_device_config_dwt_set_enabled(device, 0);
}

result = match self.tap_map {
    ClickMethod::None => 0,
    ClickMethod::Areas => unsafe {
        libinput_device_config_click_set_method(device, LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS)
    },
    ClickMethod::Finger => unsafe {
        libinput_device_config_click_set_method(device, LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER)
    },
}

result = match self.scroll_method {
    ScrollMethod::None => 0,
    ScrollMethod::Fingers => unsafe {
        libinput_device_config_scroll_set_method(device, LIBINPUT_CONFIG_SCROLL_2FG)
    },
    ScrollMethod::Edge => unsafe {
        libinput_device_config_scroll_set_method(device, LIBINPUT_CONFIG_SCROLL_EDGE)
    },
    ScrollMethod::ButtonDown => unsafe {
        libinput_device_config_scroll_set_method(device, LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN)
        // Call libinput_device_config_scroll_set_button(device, uint32_t)?
    },
}

if (libinput_device_config_accel_is_available(device)) {
libinput_device_config_accel_set_speed(device,
                               options->speed);
if (options->profile != LIBINPUT_CONFIG_ACCEL_PROFILE_NONE)
libinput_device_config_accel_set_profile(device,
                                     options->profile);
