// a program to moniter the process of a program in /proc

// include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// print help macro
#define print_help printf("Usage: hw0401 [options]... <pid>\n" \
                          "Options:\n" \
                          "\t-i, --interval <int> Display the process information every <int> seconds.\n" \
                          "\t\t\tDefault value: 1, Range: 1-100\n" \
                          "\t-c, --count <count> Display the process information <count > times.\n" \
                          "\t\t\tDefault behavior: infinite loop, Range: 1-1000\n" \
                          "\t-t, --timestamp Display the timestamp.\n" \
                          "\t-h, --help Display this description.\n")

// define the maximal length of a line
#define MAX_LINE_LENGTH 512
// define the maximal length of a timestamp
#define MAX_TIMESTAMP_LENGTH 32
// define the maximal length of a stat
#define MAX_STAT_LENGTH 384

// main
int main(int argc, char **argv) {
    // variables
    int interval = 1;
    int count = 1001;
    int timestamp = 0;
    char *process = NULL;
    while (argc > 1) {
        // move to the next argument
        argc--; argv++;

        if (strcmp(*argv, "-i") == 0 || strcmp(*argv, "--interval") == 0) {
            argc--; argv++;
            interval = atoi(*argv);
            if (interval < 1 || interval > 100) {
                print_help;
                return 0;
            }
        }
        else if (strcmp(*argv, "-c") == 0 || strcmp(*argv, "--count") == 0) {
            argc--; argv++;
            count = atoi(*argv);
            if (count < 1 || count > 1000) {
                print_help;
                return 0;
            }
        }
        else if (strcmp(*argv, "-t") == 0 || strcmp(*argv, "--timestamp") == 0) {
            timestamp = 1;
        }
        else if (strcmp(*argv, "-h") == 0 || strcmp(*argv, "--help") == 0) {
            print_help;
            return 0;
        }
        else {
            if (process != NULL) {
                print_help;
                return 0;
            }
            process = *argv;
        }
    }

    if (process == NULL) {
        // open record file
        FILE *fp = fopen("hw0401_data/process", "rb");
        if (fp == NULL) {
            printf("You didn't input a process id,\n" \
                   "and you removed the file to record the process id.\n");
            return 0;
        }
        // check file content
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        if (size == 0) {
            printf("You didn't input a process id,\n" \
                   "and you have no process id input yet.\n");
            return 0;
        }
        // allocate memory
        process = malloc(size + 1);
        if (process == NULL) {
            perror("malloc process name");
            return 0;
        }
        // read file content
        rewind(fp);
        if (fread(process, size, 1, fp) != 1) {
            perror("fread process name");
            return 0;
        }
        // close file
        fclose(fp);
    }
    else {
        // open record file
        FILE *fp = fopen("process", "wb");
        if (fp == NULL) {
            printf("You deleted the file to record the process id.\n");
            return 0;
        }
        // write file content
        fwrite(process, strlen(process), 1, fp);
        // close file
        fclose(fp);
    }

    // generate cat /proc/pid/stat
    char *path = malloc(strlen("cat /proc/") + strlen(process) + strlen("/stat > hw0401_data/stat") + 1);
    if (path == NULL) {
        perror("malloc path of stat");
        return 0;
    }
    sprintf(path, "cat /proc/%s/stat > hw0401_data/stat", process);

    // file pointer and array for time
    char *timestamp_str = NULL;
    int timestamp_length = 0;
    FILE *fp_time = NULL;
    if (timestamp) {
        timestamp_str = malloc(MAX_TIMESTAMP_LENGTH);
        fp_time = fopen("hw0401_data/time", "rb");
        if (fp_time == NULL) {
            printf("You deleted the file to record the timestamp.\n");
            return 0;
        }
    }
    else {
        timestamp_str = "";
    }
    // file pointer and array for stat
    char *stat_str = malloc(MAX_STAT_LENGTH);
    int stat_length = 0;
    FILE *fp_stat = fopen("hw0401_data/stat", "rb");
    if (fp_stat == NULL) {
        printf("You deleted the file to record the process information.\n");
        return 0;
    }
    // array for output
    char *output = malloc(MAX_LINE_LENGTH);
    // loop
    while (count > 0) {
        // get timestamp
        if (timestamp) {
            if (system("date \"+%F %T\" > hw0401_data/time") < 0) {
                perror("system date");
                return 0;
            }

            // check length
            fseek(fp_time, 0, SEEK_END);
            timestamp_length = ftell(fp_time);

            // read timestamp
            rewind(fp_time);
            if (fread(timestamp_str, timestamp_length, 1, fp_time) != 1) {
                perror("fread timestamp");
                return 0;
            }
            timestamp_str[timestamp_length - 1] = '\0'; // remove '\n'
        }

        // get stat
        if (system(path) < 0) {
            perror("system stat");
            return 0;
        }

        // check length
        fseek(fp_stat, 0, SEEK_END);
        stat_length = ftell(fp_stat);

        // read stat
        rewind(fp_stat);
        if (fread(stat_str, stat_length, 1, fp_stat) != 1) {
            perror("fread stat");
            return 0;
        }
        stat_str[stat_length - 1] = '\0'; // remove '\n'

        // setup the output message
        sprintf(output, "%s %s: %s", timestamp_str, process, stat_str);

        // output
        puts(output);

        // check count
        if (count < 1001) {
            count--;
        }

        // interval
        sleep(interval);
    }

    // exit
    return 0;
}