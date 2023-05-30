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

// function to get total cpu time
long long get_total_cpu_time() {
    long long result = 0;
    // open cpu time file
    FILE *fp = fopen("/proc/stat", "rb");
    if (fp == NULL) {
        perror("fopen /proc/stat");
        exit(EXIT_FAILURE);
    }
    // move to the first data
    fseek(fp, 5, SEEK_SET);
    // loop to get the data
    for (int i = 0; i < 10; i++) {
        long long temp = 0;
        fscanf(fp, "%lld", &temp);
        result += temp;
    }
    fclose(fp);
    return result;
}

// macro for max length of filename
#define MAX_PID_FILENAME_LENGTH 32
// function to get the process cpu time
long long get_process_cpu_time(char *process) {
    long long result = 0;
    // create filename
    char filename[MAX_PID_FILENAME_LENGTH];
    sprintf(filename, "/proc/%s/stat", process);
    // open file
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("fopen %s failed\n", filename);
        exit(EXIT_FAILURE);
    }
    // move to the first data
    for (int i = 0; i < 13;) {
        if (fgetc(fp) == ' ') {
            i++;
        }
    }
    // get the data
    for (int i = 0; i < 4; i++) {
        long long temp = 0;
        fscanf(fp, "%lld", &temp);
        result += temp;
    }
    fclose(fp);
    return result;
}

// macro for max length
#define MAX_PROCESS_NUM_LENGTH 32
long long get_number_of_cores() {
    // get the number of core
    system("grep -E 'processor' /proc/cpuinfo > hw0401_data/cores");
    FILE *cores = fopen("hw0401_data/cores", "rb");
    if (cores == NULL) {
        perror("fopen cores");
        exit(EXIT_FAILURE);
    }
    // count the number of lines
    long long cores_num = 0;
    char temp[MAX_PROCESS_NUM_LENGTH];
    while (fgets(temp, MAX_PROCESS_NUM_LENGTH, cores) != NULL) {
        cores_num++;
    }
    fclose(cores);
    return cores_num;
}

// get the total memory size
long long get_total_memory_size() {
    long long result = 0;
    // open memory file
    FILE *fp = fopen("/proc/meminfo", "rb");
    if (fp == NULL) {
        perror("fopen /proc/meminfo");
        exit(EXIT_FAILURE);
    }
    // move to the data
    fseek(fp, 10, SEEK_SET);
    // get the data
    fscanf(fp, "%lld", &result);
    fclose(fp);
    return result;
}

// get the process memory usage
long long get_process_memory_usage(char *process) {
    long long result = 0;
    // create filename
    char filename[MAX_PID_FILENAME_LENGTH];
    sprintf(filename, "/proc/%s/stat", process);
    // open file
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("fopen %s failed\n", filename);
        exit(EXIT_FAILURE);
    }
    // move to the first data
    for (int i = 0; i < 23;) {
        if (fgetc(fp) == ' ') {
            i++;
        }
    }
    // get the data
    fscanf(fp, "%lld", &result);
    // get page size
    long long page_size = getpagesize();
    // get the memory usage
    result *= page_size / 1024;
    fclose(fp);
    return result;
}

// macro for max length of timestamp
#define MAX_TIMESTAMP_LENGTH 32
// get timestamp
char *get_timestamp() {
    // create timestamp
    if (system("date \"+%F %T\" > hw0401_data/time") < 0) {
        perror("system date");
        return 0;
    }
    // open timestamp file
    FILE *fp = fopen("hw0401_data/time", "rb");
    if (fp == NULL) {
        perror("fopen hw0401_data/time");
        return 0;
    }
    // get the timestamp
    char *result = malloc(MAX_TIMESTAMP_LENGTH);
    fgets(result, MAX_TIMESTAMP_LENGTH, fp);
    // remove the newline
    result[strlen(result) - 1] = '\0';
    fclose(fp);
    return result;
}

// macro for max length of process name
#define MAX_PROCESS_NAME_LENGTH 256
char *get_process_name(char *process) {
    // create filename
    char filename[MAX_PID_FILENAME_LENGTH];
    sprintf(filename, "/proc/%s/stat", process);
    // open file
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("fopen %s failed\n", filename);
        exit(EXIT_FAILURE);
    }
    // move to the data
    for (char c; c != '(';) {
        c = fgetc(fp);
    }
    // get the name
    char *result = malloc(MAX_PROCESS_NAME_LENGTH);
    int i = 0;
    for (char c; (c = fgetc(fp)) != ')'; i++) {
        result[i] = c;
    }
    result[i] = '\0';
    fclose(fp);
    return result;
}

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
        FILE *fp = fopen("hw0401_data/process", "wb");
        if (fp == NULL) {
            printf("You deleted the file to record the process id.\n");
            return 0;
        }
        // write file content
        fwrite(process, strlen(process), 1, fp);
        // close file
        fclose(fp);
    }

    // string for timestamp
    char *timestamp_str = NULL;
    // variable for cpu core
    long long cpu_cores = get_number_of_cores();
    // variable for cpu time
    long long total_cpu_last = get_total_cpu_time();
    long long total_cpu_now = 0;
    long long process_cpu_last = get_process_cpu_time(process);
    long long process_cpu_now = 0;
    // variable for memory usage
    long long total_memory = get_total_memory_size();
    long long process_memory = 0;
    // get process name
    char *process_name = get_process_name(process);
    // loop
    while (count > 0) {
        // interval
        sleep(interval);

        // get timestamp
        if (timestamp) {
            timestamp_str = get_timestamp();
        }

        // get cpu time
        total_cpu_now = get_total_cpu_time();
        process_cpu_now = get_process_cpu_time(process);
        // get cpu usage
        double cpu_usage = (double)(process_cpu_now - process_cpu_last) * (double)100.0 * (double)cpu_cores / (double)(total_cpu_now - total_cpu_last);

        // get process memory usage
        process_memory = get_process_memory_usage(process);
        // get memory usage percentage
        double memory_usage = (double)process_memory * (double)100.0 / (double)total_memory;

        // output
        if (timestamp) {
            printf("%s %s: %.1lf(%%CPU) %.1lf(%%MEM) %s(COMMAND)\n", 
                    timestamp_str, process, cpu_usage, memory_usage, process_name);
            free(timestamp_str);
        }
        else {
            printf("%s: %.1lf(%%CPU) %.1lf(%%MEM) %s(COMMAND)\n", 
                    process, cpu_usage, memory_usage, process_name);
        }

        // now to last
        total_cpu_last = total_cpu_now;
        process_cpu_last = process_cpu_now;
        
        // check count
        if (count < 1001) {
            count--;
        }
    }

    // exit
    return 0;
}