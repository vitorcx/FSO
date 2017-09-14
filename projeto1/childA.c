//Duvida: sem chamar msg_rcv_user_panel o outro terminal nao abre
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

struct msgbuf{
    long type;
    char text[MSG_MAX_SIZE];
};

void shm_wrt_usr_msg(char* shm, char* msg){

    //char* test_msg = "Hello World";
    //printf("shared memory attached at address %p\n", shm);
    sprintf (shm, "%s%c", msg, '\0');
    //printf("%s escrito na shm\n", test_msg);

}

int shm_rd(char* shm){//retona 1 se a mensagem foi lida pelo outro processo, 0 se não foi lida
    int shm_size;
    shm_size = strlen(shm);
    if(shm[shm_size-1]=='*') return 1;
    else return 0;
}


void msg_rcv_user_panel(int msg_queue_id, char* shm){
    struct msgbuf user_msg;
    char* exit_command = "quit";
    for(;;){
        if(msgrcv(msg_queue_id, (struct msgbuf*)&user_msg, sizeof(user_msg), 0, 0)==-1)
            perror("msgrcv");

        printf("(Filho) Msg recebida da fila: %s\n", user_msg.text);
        shm_wrt_usr_msg(shm, user_msg.text);
        printf("Mensagem escrita na memoria compartilhada\n");
        if(strcmp(user_msg.text, exit_command)==0) return;
    }
}

int main(void) {
    //Acesso a fila de mensagem
    //gera a mesma chave gerada no processo pai.
    char* key_file_path = "procPaiA.c";
    char msg_queue_key_id = 'A';
    key_t msg_queue_key;
    if((msg_queue_key = ftok(key_file_path, msg_queue_key_id))==-1){
        perror("ftok");
        exit(1);
    }

    //msg_queue_id armazena o mesmo id da fila criada pelo processo pai para poder acessá-la
    int msg_queue_id;
    if((msg_queue_id = msgget(msg_queue_key, 0666 | IPC_CREAT))==-1){
        perror("msgget");
        exit(1);
    }

    //Acesso a memoria compartilhada
    //Gerar chave da memoria compartilhada
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
    shm = (char *)shmat(shm_id, 0, 0);

    //Informa o tamanho do segmento de memoria
    //shmctl(shm_id, IPC_STAT, &shm_buffer);
    //int seg_size = shm_buffer.shm_segsz;
    //printf("Tamanho do segmento: %d\n", seg_size);
    /* Write a string to the shared memory segment.  */
    //sprintf (shared_memory, “Hello, world.”);

    msg_rcv_user_panel(msg_queue_id, shm);


    shmctl (shm_id, IPC_RMID, 0);
    return 0;
}

/*char* mem_msg;
mem_msg = (char *)malloc(strlen(shm)*sizeof(char));
int i;
for(i=0; i<strlen(shm); i++)
    mem_msg[i] = shm[i];
printf("%s\n", mem_msg);
Codigo que le da memoria compartilhada*/
