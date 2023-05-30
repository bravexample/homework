// a program to fetch data of stock market from internet by curl

// include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// macro for print help
#define PRINT_HELP printf("Usage: ./hw0405 [OPTION]\n" \
                          "OPTION:\n" \
                          "\t-s : symbol of stock\n" \
                          "\t-i : input JSON file name\n" \
                          "\t-o : output JSON file name\n")

// macro for options
#define STOCK   1
#define INPUT   2
#define OUTPUT  4

// main function
int main(int argc, char **argv) {
    // check argument
    if (argc != 7) {
        PRINT_HELP;
        return 0;
    }

    int option = 0;
    char *symbol_of_stock = NULL;
    char *input_file_name = NULL;
    char *output_file_name = NULL;
    while (argc > 1) {
        // move to next argument
        argc--; argv++;
        // check option
        if (strcmp(*argv, "-s") == 0) {
            option |= STOCK;
            argc--; argv++;
            symbol_of_stock = *argv;
        }
        else if (strcmp(*argv, "-i") == 0) {
            option |= INPUT;
            argc--; argv++;
            input_file_name = *argv;
        }
        else if (strcmp(*argv, "-o") == 0) {
            option |= OUTPUT;
            argc--; argv++;
            output_file_name = *argv;
        }
        else {
            PRINT_HELP;
            return 0;
        }
    }


    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();
  
    if(curl) 
    {
        curl_easy_setopt( curl, CURLOPT_URL, "https://finance.yahoo.com/crypto" );
        
        FILE *pFile = fopen( output_file_name, "wb" );
        if (pFile == NULL) {
            perror("fopen");
            return 1;
        }
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, pFile );
        
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if( res != CURLE_OK )
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
         
        /* always cleanup */ 
        curl_easy_cleanup(curl);
        fclose( pFile );
    }
    return 0;
}
