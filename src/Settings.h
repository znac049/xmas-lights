#ifndef _SETTINGS_H_
#define _SETTINGS_H_

class Settings {
    public:
        enum storeAs { IS_STRING, IS_INT };

        static struct {
            storeAs varType;
            char *varName;
        } allVars[] = {
            {IS_STRING, "deviceName"},
            {IS_INT, "patternNumber"},
            {IS_INT, "speed"},
            {IS_INT, "loopDelay"},
            {IS_INT, "brightness"},
        };

        static bool load();
        static bool save();

        static bool set(char *varName, char *varValue);
        static bool set(char *varName, int varValue); 
};

#endif