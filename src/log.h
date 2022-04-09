//
// Created by Yongkang on 08/04/2022.
//

#ifndef NVM_MALLOC_LOG_H
#define NVM_MALLOC_LOG_H

//#define LOG_FILE "/Users/yongkang/Library/CloudStorage/OneDrive-Personal/Documents/GraduationProject/nvm-malloc/log"
#define LOG_FILE "/home/user/lyk/nvm-malloc/log"

enum op_code {TOWRITE, WRITTEN, COVERED};

void open_log();
void close_log();

void log_towrite(void *ph_addr);
void log_written(void *ph_addr);
void log_covered(void *ph_addr);

#endif //NVM_MALLOC_LOG_H
