#include "webservice.h"

DUDA_REGISTER("Kernel Version Service", "kernel_version");

#define KERNEL_VERSION_BUFFER_SIZE 256
#define LINUX_VERSION "Linux version "

void cb_kernel_version(duda_request_t *dr)
{
    FILE *fp;
    char buffer[KERNEL_VERSION_BUFFER_SIZE];
    char *kernel_version;
    unsigned long len;
    int beg, end;

    /* get kernel version information from /proc/version */
    if (!(fp = fopen("/proc/version", "r"))) {
        monkey->str_build(&kernel_version, &len, "can not open /proc/version");
    } else if (!fgets(buffer, KERNEL_VERSION_BUFFER_SIZE, fp)) {
        monkey->str_build(&kernel_version, &len, "can not get kernel version");
    } else {
        /*  get begin and end position of kernel version to make up substring for
         *  reponse.
         *
         *  on Linux, the information stored in /proc/version are seperated by
         *  space, and the version information usually comes after string
         *  "Linux version ": Linux version 3.9.2-1-ARCH (nobody@thomas) ...
         */ 
        beg = monkey->str_search(buffer, LINUX_VERSION, MK_STR_SENSITIVE);
        if (beg >= 0) {
            beg += strlen(LINUX_VERSION);
            end = monkey->str_search(buffer + beg, " ", MK_STR_SENSITIVE) + beg;
            if (end >= beg) {
                kernel_version = monkey->str_copy_substr(buffer, beg, end);
            } else {
                monkey->str_build(&kernel_version, &len, "unknown kernel version");
            }
        } else {
            monkey->str_build(&kernel_version, &len, "unknown kernel version");
        }
    }

    /* send kernel version */
    response->http_status(dr, 200);
    response->printf(dr, "Kernel Version: %s", kernel_version);
    response->end(dr, NULL);
    
    /* free allocated resource */
    if (fp) {
        fclose(fp);
    }
    if (kernel_version) {
        free(kernel_version);
    }
}

int duda_main()
{
    map->static_add("/", "cb_kernel_version");
    return 0;
}
