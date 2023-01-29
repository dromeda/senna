#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

struct RequestData
{
    double response_time;
    int response_code;
};

void make_requests(char *address, int quantity, struct RequestData *data)
{
    CURL *curl;
    CURLcode res;
    double start_time, end_time;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, address);
        for (int i = 0; i < quantity; i++)
        {
            start_time = clock();
            res = curl_easy_perform(curl);
            end_time = clock();
            data[i].response_time = (end_time - start_time) / CLOCKS_PER_SEC;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &data[i].response_code);
            if (res != CURLE_OK)
            {
                fprintf(stderr, "Error while trying to execute the requisition: %s\n",
                        curl_easy_strerror(res));
            }
        }
        curl_easy_cleanup(curl);
    }
}

void print_report(struct RequestData *data, int quantity)
{
    double total_response_time = 0.0;
    int min_response_time_index = 0, max_response_time_index = 0;
    int total_response_code_200 = 0;

    for (int i = 0; i < quantity; i++)
    {
        total_response_time += data[i].response_time;
        if (data[i].response_time < data[min_response_time_index].response_time)
        {
            min_response_time_index = i;
        }
        if (data[i].response_time > data[max_response_time_index].response_time)
        {
            max_response_time_index = i;
        }
        if (data[i].response_code == 200)
        {
            total_response_code_200++;
        }
    }

    double average_response_time = total_response_time / quantity;
    printf("\n\nFinal report\n");
    printf("Average response time: %lf seconds\n", average_response_time);
    printf("Fastest request: %d (total time: %lf seconds, HTTP code: %d)\n", min_response_time_index, data[min_response_time_index].response_time, data[min_response_time_index].response_code);
    printf("Slowest request %d (total: %lf seconds, HTTP code: %d)\n", max_response_time_index, data[max_response_time_index].response_time, data[max_response_time_index].response_code);
    printf("Quantity of requests with HTTP status code 200: %d\n", total_response_code_200);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <address> <quantity>\n", argv[0]);
        return 1;
    }

    char *address = argv[1];
    int quantity = atoi(argv[2]);
    struct RequestData data[quantity];
    make_requests(address, quantity, data);
    print_report(data, quantity);

    return 0;
}
