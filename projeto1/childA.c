#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define MSG_MAX_SIZE 100

struct msgbuf{
    long type;
    char text[MSG_MAX_SIZE];
};

void msg_rcv_user_panel(int msg_queue_id){
    struct msgbuf user_msg;
    char* exit_command = "quit";
    for(;;){
        if(msgrcv(msg_queue_id, (struct msgbuf*)&user_msg, sizeof(user_msg), 0, 0)==-1)
            perror("msgrcv");
        printf("Filho: %s\n", user_msg.text);
        if(strcmp(user_msg.text, exit_command)==0) return;
    }
}

int main(void) {
    char* key_file_path = "procPaiA.c";
    char msg_queue_key_id = 'A';
    key_t msg_queue_key;
    if((msg_queue_key = ftok(key_file_path, msg_queue_key_id))==-1){
        perror("ftok");
        exit(1);
    }

    //criação da fila
    int msg_queue_id;
    if((msg_queue_id = msgget(msg_queue_key, 0666 | IPC_CREAT))==-1){
        perror("msgget");
        exit(1);
    }

    msg_rcv_user_panel(msg_queue_id);

    return 0;
}
