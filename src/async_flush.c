//
// Created by Yongkang on 07/04/2022.
//

#include "async_flush.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "circle.h"
#include "log.h"

extern node *head;
extern node *tail;
extern node *current;

int mqid;

void handler(int signum) {
    printf("%d\n", mqid);
    msgctl(mqid, IPC_RMID, NULL);
    close_log();
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

    /* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
       we can exit the parent process. */
    if (pid > 0) {
        printf("Daemon process id: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */
    initialize();
    open_log();

    int oflag = 0666 | IPC_CREAT | IPC_EXCL;
    mqid = msgget(KEY, oflag);

    msg_buf *buffer = (msg_buf *) malloc(sizeof(msg_buf));
    int buf_len = sizeof(msg_buf) - sizeof(long);

    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    signal(SIGTERM, handler);

    int remaining = 0;

    /* The Big Loop */
    while (1) {
        ssize_t n = msgrcv(mqid, buffer, buf_len, 0, IPC_NOWAIT);
        int flag = 1;
        if (n > 0) {
            action s = insert(buffer->ph_addr, buffer->len);
            remaining++;
            if (s != NONE) {
                if (s == OVERWRITE) {
                    log_covered(buffer->ph_addr);
                }
                log_towrite(buffer->ph_addr);
            }
            flag = 0;
        }

        if (flag || remaining >= THRESHOLD) {
            if (current->len != 0) {
                void *ph_addr = current->ph_addr;
                // TODO: execute the write
                written();
                remaining--;
                log_written(ph_addr);
            } else if (current->next != current->prev) {
                current = current->next;
            } else {
                // TODO: sleep
            }
        }
    }

    /* clean up */
    msgctl(mqid, IPC_RMID, NULL);
    close_log();
    exit(EXIT_SUCCESS);
}
