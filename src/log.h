#ifndef LOG_H
#define LOG_H


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "consts.h"


#define log_info(text) { \
  fprintf(log_debug_file_get(), "[INFO][%s:%d] ", __FILE__, __LINE__); \
  fprintf(log_debug_file_get(), text); \
  fprintf(log_debug_file_get(), "\n"); \
  fflush(log_debug_file_get()); \
}


#define log_info_f(pattern, ...) { \
  fprintf(log_debug_file_get(), "[INFO][%s:%d] ", __FILE__, __LINE__); \
  fprintf(log_debug_file_get(), pattern, __VA_ARGS__); \
  fprintf(log_debug_file_get(), "\n"); \
  fflush(log_debug_file_get()); \
}


#define log_error(text) { \
  fprintf(log_debug_file_get(), "[ERROR][%s:%d] ", __FILE__, __LINE__); \
  fprintf(log_debug_file_get(), text); \
  fprintf(log_debug_file_get(), "\n"); \
  fflush(log_debug_file_get()); \
}


#define log_error_f(pattern, ...) { \
  fprintf(log_debug_file_get(), "[ERROR][%s:%d] ", __FILE__, __LINE__); \
  fprintf(log_debug_file_get(), pattern, __VA_ARGS__); \
  fprintf(log_debug_file_get(), "\n"); \
  fflush(log_debug_file_get()); \
}


#define log_fatal(text) { \
  fprintf(log_debug_file_get(), "[FATAL][%s:%d] ", __FILE__, __LINE__); \
  fprintf(log_debug_file_get(), text); \
  fprintf(log_debug_file_get(), "\n"); \
  fflush(log_debug_file_get()); \
  exit(1); \
}


#define log_fatal_f(pattern, ...) { \
  fprintf(log_debug_file_get(), "[FATAL][%s:%d] ", __FILE__, __LINE__); \
  fprintf(log_debug_file_get(), pattern, __VA_ARGS__); \
  fprintf(log_debug_file_get(), "\n"); \
  fflush(log_debug_file_get()); \
  exit(1); \
}


#define assert(condition, text) { \
  if (!(condition)) { \
    log_fatal(text); \
  } \
}


#define assert_f(condition, pattern, ...) { \
  if (!(condition)) { \
    log_fatal_f(pattern, __VA_ARGS__); \
  } \
}


void log_init(void);
struct _IO_FILE* log_debug_file_get(void);


#endif

