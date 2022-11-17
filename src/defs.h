
enum nvm_type {IS_INT, IS_STRING};

typedef struct {
    char *name;
    enum nvm_type type;
} nvm_option;
