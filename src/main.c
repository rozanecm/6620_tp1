#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>

/* define max input. Number is max supported for 32 bit unsigned int */
#define MAX_INPUT UINT_MAX

void print_help_data(){
    printf("Usage:\n "
                   "\tcommon -h \n"
                   "\tcommon -v \n"
                   "\tcommon [options] M N \n"
                   "Options:\n"
                   "\t-h,--help \tPrint usage information.\n"
                   "\t-V, --version \tPrints version information.\n"
                   "\t-o, --output\tPath to output file.\n"
                   "\t-d  --divisor Just the divisor\n"
                   "\t-m  --multiple Just the multiple\n"
                   "Examples:\n"
                   "\tcommon -o - 256 192\n");
}

void print_version_info(){
    printf("Version 1.0\n");
}

int mcd(int a, int b) {
    /* make sure a > b
     * although this is not strictly necessary, we make it this way so it is
     * easier to follow */
    if (a < b){
        int aux = a;
        a = b;
        b = aux;
    }

    if (b == 0){
        return a;
    } else {
        return mcd(b, a % b);
    }
}

int mcm(const int a, const int b){
    return abs(a * b) / mcd(a, b);
}

short int check_range(unsigned long int a, unsigned long int b){
    /* This function tests the input numbers to be in range [2, MAX_INPUT].
     * Return values:
     *      0: Success.
     *      1: Failure.
     * */
    if ((a >= 2) && (a <= MAX_INPUT) && (b >= 2) && (b <= MAX_INPUT)){
        /* Success */
        return 0;
    }

    /* failure */
    return 1;
}

void process_input_numbers(unsigned long int *a, unsigned long int *b,
                           char *input1, char *input2){
    /* Process input numbers */
    errno = 0;
    char* endptr = NULL;
    unsigned long int asdf = strtoul(input1, &endptr, 10);
    *a = asdf;
    /* error checking performed according to strtol man page */
    if ((errno == ERANGE && (*a == LONG_MAX || *a == LONG_MIN))
        || (errno != 0 && *a == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    *b = strtoul(input2, &endptr, 10);
    /* error checking performed according to strtol man page */
    if ((errno == ERANGE && (*b == LONG_MAX || *b == LONG_MIN))
        || (errno != 0 && *b == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (check_range(*a, *b) == 1){
        exit(EXIT_FAILURE);
    }
}

void print_mcm(unsigned int a, unsigned int b, char* path){
    /* According to ASCII table, 45 is the '-' char.
     * Source: http://www.asciitable.com/ */
    if (*path == 45){
        /* output to stdout */
        printf("%i\n", mcm(a, b));
    }else{
        FILE* file = fopen(path, "w");
        /* error checking */
        if (file == NULL){
            exit(EXIT_FAILURE);
        }

        fprintf(file, "%i\n", mcm(a, b));

        fclose(file);
    }
}

void print_mcd(unsigned int a, unsigned int b, char* path){
    /* According to ASCII table, 45 is the '-' char.
     * Source: http://www.asciitable.com/ */
    if (*path == 45){
        /* output to stdout */
        printf("%i\n", mcd(a, b));
    }else{
        FILE* file = fopen(path, "w");
        /* error checking */
        if (file == NULL){
            exit(EXIT_FAILURE);
        }

        fprintf(file, "%i\n", mcd(a, b));

        fclose(file);
    }
}

int main(int argc, char* argv[]){
    unsigned long int a, b;
    static struct option long_options[] = {
            {"help", 	    no_argument, 		0, 'h' },
            {"version",	    no_argument, 		0, 'v' },
            {"output",	    required_argument,	0, 'o' },
            {"divisor",	    no_argument,	    0, 'd' },
            {"multiple",	no_argument,    	0, 'm' },
            {0,			    0,					0,  0  }
    };
    int option_index = 0;
    int c = getopt_long(argc, argv, "hvo:dm", long_options, &option_index);
    switch(c){
        case 'h':
            print_help_data();
            break;
        case 'v':
            print_version_info();
            break;
        case 'o':
            process_input_numbers(&a, &b, argv[argc-2], argv[argc-1]);
            print_mcm(a, b, optarg);
            print_mcd(a, b, optarg);
            break;
        case 'd':
            process_input_numbers(&a, &b, argv[argc-2], argv[argc-1]);
            print_mcd(a, b, "-");
            break;
        case 'm':
            process_input_numbers(&a, &b, argv[argc-2], argv[argc-1]);
            print_mcm(a, b, "-");
            break;
        default:
            process_input_numbers(&a, &b, argv[argc-2], argv[argc-1]);
            print_mcm(a, b, "-");
            print_mcd(a, b, "-");
    }

    exit(EXIT_SUCCESS);
}