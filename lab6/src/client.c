#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include "common.h"

struct Server {
    char ip[255];
    int port;
};

void* ConnectToServer(void* arg) {
    struct Server* server = (struct Server*)arg;

    struct hostent *hostname = gethostbyname(server->ip);
    if (hostname == NULL) {
        fprintf(stderr, "gethostbyname failed with %s\n", server->ip);
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server->port);
    server_addr.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);

    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck < 0) {
        fprintf(stderr, "Socket creation failed!\n");
        exit(1);
    }

    if (connect(sck, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Connection failed\n");
        exit(1);
    }

    uint64_t begin = 1;
    uint64_t end = 1;
    uint64_t mod = 1;

    char task[sizeof(uint64_t) * 3];
    memcpy(task, &begin, sizeof(uint64_t));
    memcpy(task + sizeof(uint64_t), &end, sizeof(uint64_t));
    memcpy(task + 2 * sizeof(uint64_t), &mod, sizeof(uint64_t));

    if (send(sck, task, sizeof(task), 0) < 0) {
        fprintf(stderr, "Send failed\n");
        exit(1);
    }

    char response[sizeof(uint64_t)];
    if (recv(sck, response, sizeof(response), 0) < 0) {
        fprintf(stderr, "Receive failed\n");
        exit(1);
    }

    uint64_t answer = 0;
    memcpy(&answer, response, sizeof(uint64_t));
    printf("answer: %lu\n", answer);

    close(sck);
    return NULL;
}

int main(int argc, char **argv) {
    uint64_t k = -1;
    uint64_t mod = -1;
    char servers[255] = {'\0'};

    while (true) {
        static struct option options[] = {{"k", required_argument, 0, 0},
                                          {"mod", required_argument, 0, 0},
                                          {"servers", required_argument, 0, 0},
                                          {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "", options, &option_index);

        if (c == -1)
            break;

        switch (c) {
        case 0: {
            switch (option_index) {
            case 0:
                ConvertStringToUI64(optarg, &k);
                break;
            case 1:
                ConvertStringToUI64(optarg, &mod);
                break;
            case 2:
                memcpy(servers, optarg, strlen(optarg));
                break;
            default:
                printf("Index %d is out of options\n", option_index);
            }
        } break;

        case '?':
            printf("Arguments error\n");
            break;
        default:
            fprintf(stderr, "getopt returned character code 0%o?\n", c);
        }
    }

    if ((int)k == -1 || (int)mod == -1 || !strlen(servers)) {
        fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(servers, "r");
    if (!file) {
        perror("Failed to open servers file");
        return 1;
    }

    char line[255];
    int servers_num = 0;
    while (fgets(line, sizeof(line), file)) {
        servers_num++;
    }
    fseek(file, 0, SEEK_SET);

    struct Server *to = malloc(sizeof(struct Server) * servers_num);
    for (int i = 0; i < servers_num; i++) {
        fgets(line, sizeof(line), file);
        sscanf(line, "%254[^:]:%d", to[i].ip, &to[i].port);
    }
    fclose(file);

    pthread_t threads[servers_num];
    for (int i = 0; i < servers_num; i++) {
        if (pthread_create(&threads[i], NULL, ConnectToServer, &to[i])) {
            printf("Error: pthread_create failed!\n");
            return 1;
        }
    }

    for (int i = 0; i < servers_num; i++) {
        pthread_join(threads[i], NULL);
    }

    free(to);
    return 0;
}