#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define MSG_MAX_SIZE 100

//Struct da mensagem
struct msgbuf{
    long type;
    char text[MSG_MAX_SIZE];
};

//Função para receber mensagem do usuário e enviar para fila
void msg_snd_user_panel(int msg_queue_id){
    struct msgbuf user_msg;
    user_msg.type = 1;
    char* exit_command = "quit";
    int exit_strcmp;
    while((exit_strcmp = strcmp(user_msg.text, exit_command))!=0){
        printf("Digite a mensagem desejada de até %d caracteres (Digite %s para sair):\n", MSG_MAX_SIZE, exit_command);
        scanf(" %[^\n]s", user_msg.text);

        if(msgsnd(msg_queue_id, (struct msgbuf*)&user_msg, sizeof(user_msg), 0)==-1)//quit está sendo colocado na fila
            perror("msgsnd");

    }
}

int main(void){

    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    //geração da chave de identificação para a fila de mensagem
    //Visivel para o processo pai e filho
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

    if(pid == 0){

        //O código aqui dentro será executado no processo filho
        //impressão das mensagens recebidas da fila
        fflush(stdin);
        execlp("gnome-terminal", "gnome-terminal", "-e", "./cA", NULL);
        exit(1);

    }
    else{

        //O código neste trecho será executado no processo pai
        //Interação com o usuário e envio da mensagem para a fila
        msg_snd_user_panel(msg_queue_id);

    }
    msgctl(msg_queue_id, IPC_RMID, 0);
    exit(0);
}
