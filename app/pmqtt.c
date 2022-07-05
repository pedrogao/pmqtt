#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"
#include "config.h"
#include "server.h"

int main(int argc, char **argv)
{

    char *addr = DEFAULT_HOSTNAME;
    char *port = DEFAULT_PORT;
    char *confpath = DEFAULT_CONF_PATH;
    int debug = 0;
    int opt;

    // Set default configuration
    config_set_default();

    while ((opt = getopt(argc, argv, "a:c:p:m:vn:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            addr = optarg;
            strcpy(conf->hostname, addr);
            break;
        case 'c':
            confpath = optarg;
            break;
        case 'p':
            port = optarg;
            strcpy(conf->port, port);
            break;
        case 'v':
            debug = 1;
            break;
        default:
            fprintf(stderr,
                    "Usage: %s [-a addr] [-p port] [-c conf] [-v]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Override default DEBUG mode
    conf->loglevel = debug == 1 ? DEBUG : WARNING;

    // Try to load a configuration, if found
    config_load(confpath);

    // Print configuration
    config_print();

    start_server(conf->hostname, conf->port);

    return 0;
}
