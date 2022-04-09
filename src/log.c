//
// Created by Yongkang on 08/04/2022.
//

#include "log.h"

#include <stdio.h>

#include "circle.h"

FILE *p;

void open_log() {
    p = fopen(LOG_FILE, "r+");
}

void close_log() {
    fclose(p);
}

void log_towrite(void *ph_addr) {
    fprintf(p, "%d: %p\n", TOWRITE, ph_addr);
}

void log_written(void *ph_addr) {
    fprintf(p, "%d: %p\n", WRITTEN, ph_addr);
}

void log_covered(void *ph_addr) {
    fprintf(p, "%d: %p\n", COVERED, ph_addr);
}
