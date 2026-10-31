
#include <errno.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double paral(double R1, double R2);
double series(double R1, double R2);
void print_help();

int main(int argc, char *argv[]) {
    int ch;

    char state = 0;
    int have_v = 0;
    double R1 = 0, R2 = 0, result = 0;

    const char *label;

    if (argc == 1) {
        fprintf(stderr, "[ERR] No argument found, quitting\n");
        fprintf(stderr, "[ERR] Use help options (-h or --help) for informations\n");
        exit(EXIT_FAILURE);
    }

    static struct option long_options[] = 
    {
        {"type", required_argument,   0, 't'},
        {"value",  required_argument,   0, 'v'},
        {"help",      no_argument,    0, 'h'},
        {  NULL,         0,         NULL,  0 }
    };

    int option_index = 0;

    while ((ch = getopt_long(argc, argv, "t:v:h", long_options, &option_index)) != -1)
    {
        switch (ch) {
            case 't': {
                if (strcmp(optarg, "series") == 0) state = 's';
                else if (strcmp(optarg, "parallel") == 0) state = 'p';
                else {
                    fprintf(stderr, "[ERR] No such valid arguments found in type option\n");
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 'v': {
                char *endptr1;
                char *endptr2;
                
                errno = 0;

                R1 = strtod(optarg, &endptr1);

                if (endptr1 == optarg || *endptr1 != ',') {
                    fprintf(stderr, "[ERR] First value is not a valid number or missing a comma delimiter\n");
                    exit(EXIT_FAILURE);
                }

                char *second_str = endptr1 + 1;
                R2 = strtod(second_str, &endptr2);

                if (endptr2 == second_str || *endptr2 != '\0') {
                    fprintf(stderr, "[ERR] Second value contains trailing invalid characters or is not a valid number\n");
                    exit(EXIT_FAILURE);
                }

                if (errno == ERANGE) {
                    fprintf(stderr, "[ERR] One of the numbers is out of range (too large or too small)\n");
                    exit(EXIT_FAILURE);
                }

                have_v = 1;
                break;
            }
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);

            case '?':

            default:
                fprintf(stderr, "[ERR] Invalid argument found, quitting.\n");
                fprintf(stderr, "[ERR] Use help options (-h or --help) for informations\n");
                exit(EXIT_FAILURE);
        }
    }

    if (!state || !have_v) {
        fprintf(stderr, "[ERR] Both --type and --value are required\n");
        exit(EXIT_FAILURE);
    }

    if (!(isfinite(R1) && R1 > 0) || !(isfinite(R2) && R2 > 0)) {
        fprintf(stderr, "[ERR] Resistances must be finite and positive\n");
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        fprintf(stderr, "[ERR] Unexpected argument: %s\n", argv[optind]);
        exit(EXIT_FAILURE);
    }

    switch (state) {
        case 'p': result = paral(R1, R2); label = "Parallel"; break;
        case 's': result = series(R1, R2); label = "Series";   break;
        default:  exit(EXIT_FAILURE);
    }

    if (!isfinite(result)) {
        fprintf(stderr, "[ERR] Result overflowed (not finite)\n");
        exit(EXIT_FAILURE);
    }

    printf("R1 = %g ohm, R2 = %g ohm\n", R1, R2);
    printf("State = %s\n", label);
    printf("Result = %g ohm\n", result);

    exit(EXIT_SUCCESS);
}

double paral(double R1, double R2) {
    return 1.0 / (1.0 / R1 + 1.0 / R2);
}

double series(double R1, double R2) {
    return R1 + R2;
}

void print_help() {
    printf("\nUsage: ./rescomb [-t|--type] <type-value> [-v|--value] <R1,R2> [other_options]\n");
    printf("\nDescription: ");
    printf("\n  -t, --type          type you want, supports only \"parallel\" and \"series\"");
    printf("\n  -v, --value         value of both resistors, double data type");
    printf("\n  -h, --help          print this messages");
    printf("\n\nExamples: ./rescomb -t parallel -v 12,6\n");
}
