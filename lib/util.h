#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <strings.h>

#define UUID_LEN 37

#define MAX_LOG_SIZE 119

enum log_level
{
    DEBUG,
    INFORMATION,
    WARNING,
    ERROR
};

bool is_integer(const char *);
int parse_int(const char *);
int number_len(size_t);
int generate_uuid(char *);

/* Logging */
void p_log_init(const char *);
void p_log_close(void);
void p_log(int, const char *, ...);

/* Memory management */
void *p_malloc(size_t);
void *p_calloc(size_t, size_t);
void *p_realloc(void *, size_t);
size_t malloc_size(void *);
void p_free(void *);
char *p_strdup(const char *);
char *remove_occur(char *, char);
char *append_string(char *, char *, size_t);

size_t memory_used(void);

#define log(...) p_log(__VA_ARGS__)
#define p_debug(...) log(DEBUG, __VA_ARGS__)
#define p_warning(...) log(WARNING, __VA_ARGS__)
#define p_error(...) log(ERROR, __VA_ARGS__)
#define p_info(...) log(INFORMATION, __VA_ARGS__)

#define STREQ(s1, s2, len) strncasecmp(s1, s2, len) == 0 ? true : false

#endif
