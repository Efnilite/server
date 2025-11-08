#include "util.h"

#include <errno.h>
#include <string.h>

void parse_program_arguments(
    const struct p_argument_t* p_args, const size_t p_args_len,
    const int count, char* args[]
) {
    if (count < 2) {
        return;
    }

    // first argument is process name by standard
    for (int i = 1; i < count; ++i) {
        const char* spec = args[i];

        for (int argi = 0; argi < p_args_len; ++argi) {
            const struct p_argument_t argument = p_args[argi];

            if (spec[0] != '-' || spec[1] != argument.name) {
                continue;
            }

            char arg[256];
            for (int j = i + 1; j < i + 1 + argument.len; ++j) {
                strcat(arg, args[j]);
            }

            argument.parser(arg);

            i += argument.len;
        }
    }
}

long int parse_int(const char* str) {
    char* end;
    const long int result = strtol(str, &end, 10);
    if (end == str) {
        ERROR_NO(EINVAL, "No port specified");
    }
    if (*end != '\0') {
        ERROR_NO(EINVAL, "Invalid character in server port");
    }
    return result;
}
