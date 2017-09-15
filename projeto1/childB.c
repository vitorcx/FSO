#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#define MSG_MAX_SIZE 100

//Struct da mensagem
struct msgbuf{
    long type;
    char text[MSG_MAX_SIZE];
};

//Função para receber mensagem do usuário e enviar para fila

int main(void){
    //Acesso a fila de mensagem
    //geração da chave de identificação para a fila de mensagem
    char* key_file_path = "childB.c";
    char msg_queue_key_id = 'B';
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

    //Acesso a memória compartilhada
    //Gera a mesma chave de childA par acessarem a mesma memoria
    key_t shm_key;
    if((shm_key = ftok(".", 'X'))==-1){
        perror("ftok");
        exit(1);
    }

    //tamanho da memoria compartilhada 128bytes
    const int shm_segment_size = 0x80;
    //Struct com dados da memoria compartilhada
    struct shmid_ds shm_buffer;
    //Ponteiro para o endereço da memoria compartilhada
    char* shm;
    //id da memoria compartilhada
    int shm_id;
    //criando memoria compartilhada
    if((shm_id = shmget(shm_key, shm_segment_size, 0666 | IPC_CREAT))==-1){
        perror("shmget");
        exit(1);
    }

    //aponta o ponteiro shm para o endereço da memoria compartilhada
    if((shm = (char *)shmat(shm_id, 0, 0))==(char *)-1){
        perror("shmat");
        exit(1);
    }

    int msg_snd;
    struct msgbuf user_msg;

    *shm=1;

    while(1){
        while(*shm==1){
            //printf("Esperando\n");
        }
        *shm=1;

        strcpy(user_msg.text, shm+1);
        printf("Mensagem lida na memoria compartilhada: %s\n", user_msg.text);

        if((msg_snd = msgsnd(msg_queue_id, (struct msgbuf*)&user_msg, sizeof(user_msg), 0))==-1){
            perror("msgrcv");
            exit(1);
        }

        if(strcmp(user_msg.text, "quit")==0){
            msgctl(msg_queue_id, IPC_RMID, 0);
        }
    }

    exit(0);
}
