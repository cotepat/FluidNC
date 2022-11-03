#pragma once

#include "Settings.h"

extern StringSetting* config_filename;

extern StringSetting* build_info;

extern StringSetting* start_message;

extern IntSetting* status_mask;

extern IntSetting* sd_fallback_cs;

extern IntSetting* fake_report_inches;

extern IntSetting* fake_homing_enabled;

extern IntSetting* fake_homing_dir_invert;

extern IntSetting* fake_homing_pulloff;

extern IntSetting* fake_spindle_min;

extern IntSetting* fake_soft_limits;

extern IntSetting* fake_x_accel;

extern IntSetting* fake_y_accel;

extern IntSetting* fake_z_accel;

extern IntSetting* fake_x_max_feed;

extern IntSetting* fake_y_max_feed;

extern IntSetting* fake_z_max_feed;

extern IntSetting* fake_x_resolution;

extern IntSetting* fake_y_resolution;

extern IntSetting* fake_z_resolution;

extern IntSetting* fake_x_max_travel;

extern IntSetting* fake_y_max_travel;

extern IntSetting* fake_z_max_travel;

extern EnumSetting* message_level;
