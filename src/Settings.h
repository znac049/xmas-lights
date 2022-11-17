#ifndef _SETTINGS_H_
#define _SETTINGS_H_

class Settings {
    public:
        static nvm_option *allVars[];

        static bool load();
        static bool save();

        static bool set(char *varName, char *varValue);
        static bool set(char *varName, int varValue); 
};

#endif