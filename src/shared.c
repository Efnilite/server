#include "shared.h"

void parse_program_arguments(const int count, char* args[]) {
    if (count < 2) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        const char* spec = args[i];

        // for (int argi = 0; argi < LEN(arguments); ++argi) {
        //     const struct p_argument_t argument = arguments[argi];
        //     if (spec[0] == '-' && spec[1] == argument.name) {
        //
        //     }
        // }
    }
}