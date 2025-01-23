#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_DAYS 5
#define MIN_ENTRIES 100
#define MAX_ENTRIES 1000

// Response codes and their meanings
// 200 - OK: The request has succeeded.
// 201 - Created: The request has been fulfilled and resulted in a new resource being created.
// 400 - Bad Request: The request could not be understood by the server due to malformed syntax.
// 401 - Unauthorized: The request requires user authentication.
// 403 - Forbidden: The server understood the request, but is refusing to fulfill it.
// 404 - Not Found: The server has not found anything matching the Request-URI.
// 500 - Internal Server Error: The server encountered an unexpected condition which prevented it from fulfilling the request.
// 501 - Not Implemented: The server does not support the functionality required to fulfill the request.
// 502 - Bad Gateway: The server received an invalid response from the upstream server.
// 503 - Service Unavailable: The server is currently unable to handle the request due to a temporary overloading or maintenance of the server.

const char *response_codes[] = {"200", "201", "400", "401", "403", "404", "500", "501", "502", "503"};
const char *methods[] = {"GET", "POST", "PUT", "PATCH", "DELETE"};
const char *agents[] = {"Mozilla", "Google Chrome", "Opera", "Safari", "Internet Explorer", "Microsoft Edge", "Crawler and bot", "Library and net tool"};
const char *urls[] = {"/index.html", "/home", "/api/data", "/contact", "/about", "/login", "/signup"};

const char* get_random_response_code() {
    return response_codes[rand() % 10];
}

const char* get_random_method() {
    return methods[rand() % 5];
}

const char* get_random_agent() {
    return agents[rand() % 8];
}

const char* get_random_url() {
    return urls[rand() % 7];
}

void generate_random_ip(char *buffer) {
    sprintf(buffer, "%d.%d.%d.%d", rand() % 256, rand() % 256, rand() % 256, rand() % 256);
}

void generate_log_file(const char *filename, struct tm *day) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int num_entries = MIN_ENTRIES + rand() % (MAX_ENTRIES - MIN_ENTRIES + 1);
    char ip[16];
    struct tm entry_time = *day;
    char time_buffer[30];

    for (int i = 0; i < num_entries; i++) {
        generate_random_ip(ip);
        strftime(time_buffer, sizeof(time_buffer), "%d/%b/%Y:%H:%M:%S %z", &entry_time);

        fprintf(file, "%s - - [%s] \"%s %s HTTP/1.1\" %s %d \"-\" \"%s\"\n",
                ip,
                time_buffer,
                get_random_method(),
                get_random_url(),
                get_random_response_code(),
                rand() % 10000 + 1, // Random size
                get_random_agent());

        entry_time.tm_sec += rand() % 60;
        mktime(&entry_time);
    }

    fclose(file);
}

int main() {
    srand(time(NULL));

    struct tm day = {0};
    time_t now = time(NULL);
    localtime_r(&now, &day);
    day.tm_hour = 0;
    day.tm_min = 0;
    day.tm_sec = 0;

    char filename[30];

    for (int i = 0; i < NUM_DAYS; i++) {
        strftime(filename, sizeof(filename), "nginx_log_%Y%m%d.log", &day);
        generate_log_file(filename, &day);
        day.tm_mday++;
        mktime(&day);
    }

    return 0;
}

