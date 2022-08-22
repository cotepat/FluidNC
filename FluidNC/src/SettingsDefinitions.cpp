#include "SettingsDefinitions.h"
#include "Logging.h"

StringSetting* config_filename;

StringSetting* build_info;

StringSetting* start_message;

IntSetting* status_mask;

IntSetting* fake_report_inches;

IntSetting* fake_homing_enabled;

IntSetting* fake_homing_dir_invert;

IntSetting* fake_homing_pulloff;

IntSetting* fake_spindle_min;

IntSetting* fake_spindle_max;

IntSetting* fake_soft_limits;

IntSetting* fake_x_accel;

IntSetting* fake_y_accel;

IntSetting* fake_z_accel;

IntSetting* fake_x_max_feed;

IntSetting* fake_y_max_feed;

IntSetting* fake_z_max_feed;

IntSetting* fake_x_resolution;

IntSetting* fake_y_resolution;

IntSetting* fake_z_resolution;

IntSetting* fake_x_max_travel;

IntSetting* fake_y_max_travel;

IntSetting* fake_z_max_travel;

EnumSetting* message_level;

enum_opt_t messageLevels = {
    // clang-format off
    { "None", MsgLevelNone },
    { "Error", MsgLevelError },
    { "Warning", MsgLevelWarning },
    { "Info", MsgLevelInfo },
    { "Debug", MsgLevelDebug },
    { "Verbose", MsgLevelVerbose },
    // clang-format on
};

enum_opt_t onoffOptions = { { "OFF", 0 }, { "ON", 1 } };

void make_coordinate(CoordIndex index, const char* name) {
    float coord_data[MAX_N_AXIS] = { 0.0 };
    auto  coord                  = new Coordinates(name);
    coords[index]                = coord;
    if (!coord->load()) {
        coords[index]->setDefault();
    }
}

void make_settings() {
    Setting::init();

    // Propagate old coordinate system data to the new format if necessary.
    // G54 - G59 work coordinate systems, G28, G30 reference positions, etc
    make_coordinate(CoordIndex::G54, "G54");
    make_coordinate(CoordIndex::G55, "G55");
    make_coordinate(CoordIndex::G56, "G56");
    make_coordinate(CoordIndex::G57, "G57");
    make_coordinate(CoordIndex::G58, "G58");
    make_coordinate(CoordIndex::G59, "G59");
    make_coordinate(CoordIndex::G28, "G28");
    make_coordinate(CoordIndex::G30, "G30");

    message_level = new EnumSetting("Which Messages", EXTENDED, WG, NULL, "Message/Level", MsgLevelInfo, &messageLevels, NULL);

    config_filename = new StringSetting("Name of Configuration File", EXTENDED, WG, NULL, "Config/Filename", "config.yaml", 1, 50, NULL);

    // GRBL Numbered Settings     
    // Settings for GRBL gcode senders compatibility only... They do not affect FluidNC in any way.
    fake_z_max_travel = new IntSetting("Z max travel (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "132", "Fake/$132", 50, 0, 500, NULL);
    fake_y_max_travel = new IntSetting("Y max travel (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "131", "Fake/$131", 500, 0, 5000, NULL);
    fake_x_max_travel = new IntSetting("X max travel (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "130", "Fake/$130", 500, 0, 5000, NULL);
    fake_z_accel = new IntSetting("Z acceleration (fake value. used by some senders, does not affect fluidNC behavior)", GRBL, WG, "122", "Fake/$122", 500, 0, 10000, NULL);
    fake_y_accel = new IntSetting("Y acceleration (fake value. used by some senders, does not affect fluidNC behavior)", GRBL, WG, "121", "Fake/$121", 500, 0, 10000, NULL);
    fake_x_accel = new IntSetting("X acceleration (fake value. used by some senders, does not affect fluidNC behavior)", GRBL, WG, "120", "Fake/$120", 500, 0, 10000, NULL);
    fake_z_max_feed = new IntSetting("Z max feed (fake value. used by some senders, does not affect fluidNC behavior)", GRBL, WG, "112", "Fake/$112", 1500, 0, 150000, NULL);
    fake_y_max_feed = new IntSetting("Y max feed (fake value. used by some senders, does not affect fluidNC behavior)", GRBL, WG, "111", "Fake/$111", 1500, 0, 150000, NULL);
    fake_x_max_feed = new IntSetting("X max feed (fake value. used by some senders, does not affect fluidNC behavior)", GRBL, WG, "110", "Fake/$110", 1500, 0, 150000, NULL);
    fake_z_resolution = new IntSetting("Z resolution (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "102", "Fake/$102", 0, 0, 32000, NULL);
    fake_y_resolution = new IntSetting("Y resolution (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "101", "Fake/$101", 0, 0, 32000, NULL);
    fake_x_resolution = new IntSetting("X resolution (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "100", "Fake/$100", 0, 0, 32000, NULL);
    fake_spindle_min =  new IntSetting("Spindle min (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "31", "Fake/$31", 0, 0, 100000, NULL);
    fake_spindle_max =  new IntSetting("Spindle max (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "30", "Fake/$30", 30000, 0, 100000, NULL);
    fake_homing_pulloff = new IntSetting("Homing pulloff (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "27", "Fake/$27", 0, 0, 10, NULL);
    fake_homing_dir_invert = new IntSetting("Homing direction invert mask (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "23", "Fake/$23", 0, 0, 7, NULL);
    fake_homing_enabled = new IntSetting("Homing enabled? (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "22", "Fake/$22", 1, 0, 1, NULL);
    fake_soft_limits = new IntSetting("Soft limits enabled? (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "20", "Fake/$20", 0, 0, 1, NULL);
    fake_report_inches = new IntSetting("Report in inches? (used by some senders, does not affect fluidNC behavior)", GRBL, WG, "13", "Report_inches", 0, 0, 1, NULL);

    status_mask = new IntSetting("What to include in status report", GRBL, WG, "10", "Report/Status", 1, 0, 3, NULL);

    build_info = new StringSetting("OEM build info for $I command", EXTENDED, WG, NULL, "Firmware/Build", "", 0, 20, NULL);

    start_message =
        new StringSetting("Message issued at startup", EXTENDED, WG, NULL, "Start/Message", "Grbl \\V [FluidNC \\B (\\R) \\H]", 0, 40, NULL);
}
