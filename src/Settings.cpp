#include <Preferences.h>
#include <WString.h>

#include "defs.h"
#include "Settings.h"

nvm_option *Settings::allVars[] = {
    {"deviceName", IS_STRING},
    {"pattern", IS_INT},
};

bool Settings::load()
{
    Preferences prefs;
    int version;

    prefs.begin("chippers");
    version = prefs.getInt("version", -1);

    if (version == -1) {
        Serial.println("Settings reset to defaults in nvram.");

        prefs.clear();
        prefs.putInt("version", 1);

        Settings::save();
    }
    else {
    }

    prefs.end();
    
    return true;
}

bool Settings::save()
{
    Preferences prefs;

    prefs.begin("chippers");
    prefs.end();

    Serial.println("Settings saved to nvram.");

    return true;
}

bool Settings::set(char *varName, char *varValue)
{
    return false;
}

bool Settings::set(char *varName, int varValue) {
    return false;
}


