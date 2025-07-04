/*
 * Copyright (C) 2021 eYs3D Corporation
 * All rights reserved.
 * This project is licensed under the Apache License, Version 2.0.
 */

 #pragma once

 #include <cstdint>
 #include <cstdio>
 #include <ctime>
 #include <iostream>
 #include <chrono>
 #include <thread>
 #include <type_traits>
 #include <unistd.h>     // access(), usleep(), etc (for Linux)
 #include <cstring>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 
 #ifdef WIN32
     #include <winsock.h>
     #include "eSPDI_Common.h"
 #else
     #include "eSPDI_def.h"
 #endif
 
 // -------------------------------------------------------------------
 // Rect structure
 // -------------------------------------------------------------------
 typedef struct Rect {
     int32_t x;
     int32_t y;
     int32_t width;
     int32_t height;
 } Rect;
 
 // -------------------------------------------------------------------
 // Avoid macro redefinition conflicts (e.g., OpenCV)
 // -------------------------------------------------------------------
 #ifdef MAX
 #undef MAX
 #endif
 #ifdef MIN
 #undef MIN
 #endif
 
 template<typename T>
 constexpr const T& MAX(const T& a, const T& b) {
     return (a > b) ? a : b;
 }
 
 template<typename T>
 constexpr const T& MIN(const T& a, const T& b) {
     return (a < b) ? a : b;
 }
 
 // -------------------------------------------------------------------
 // Compatibility definitions (mainly for Windows)
 // -------------------------------------------------------------------
 #ifdef WIN32
     #define F_OK 0
     #define R_OK 4
     #define W_OK 2
     #define X_OK 6
     #define ushort USHORT
     int gettimeofday(struct timeval *tp, void *tzp);
     void usleep(__int64 usec);
     unsigned int sleep(unsigned int seconds);
     int is_big_endian(void);
     char* dirname(char *path);
     int clock_gettime(int, struct timespec *tv);
 #endif
 
 // -------------------------------------------------------------------
 // Utility Function Declarations
 // -------------------------------------------------------------------
 char* string_trim(char *str);
 
 int read_fully(int fd, void* data, size_t byte_count, const char *log_tag);
 int write_fully(int fd, const void* data, size_t byte_count, const char *log_tag);
 
 void get_process_name(uint32_t pid, char *procName, int length);
 int get_executable_path(char *path, int length, const char *log_tag);
 int get_executable_dir(char *dir, int length, const char *log_tag);
 
 int getenv_to_int(const char *env, int default_value);
 int create_directory(const char *dirPath, const char *log_tag);
 
 int64_t now_in_microsecond_unix_time();
 int64_t now_in_microsecond_high_res_time_MONOTONIC();
 int64_t now_in_microsecond_high_res_time_REALTIME();
 
 int get_cpu_core_count();
 void get_time_YYYY_MM_DD_HH_MM_SS(int64_t timeMs, char* date, size_t length);
 
 #ifndef WIN32
 int get_model_name(const char *devPath, char *out, int length, const char *log_tag);
 #endif
 
 USB_PORT_TYPE get_usb_type(const char *devPath);
 
 void reschedule(std::chrono::microseconds us);
 