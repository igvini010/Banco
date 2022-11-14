#include <stdio.h>
#include <stdlib.h>

//Tela inicial
void telaInicial(){

    printf("1 - Fazer login\n");
    printf("2 - Fazer cadastro\n");
    printf("3 - Sair\n");

}

//Mostra o saldo do usuario
float saldoUser(int idUser){

    char txt; //caracteres do db
    FILE *file3;
    file3 = fopen("usuarios.txt", "r");

    int c = 0;
    int u = 1;
    float num = 0;
    float num2 = 0;
    int d = 0;

    //passa por todos os caracteres do db
    while(txt != EOF){

        //saldo
        txt = fgetc(file3); //caracteres do que tem dentro do db
        int cont = 1;
        if(u == idUser && c == 3){
            while(txt != '|'){
                if(txt != '.' && d == 0){
                    num += txt-48;
                    num *= 10;
                }
                if(txt == '.'){
                    d = 1;
                    txt = fgetc(file3); //caracteres do que tem dentro do db
                }
                if(txt != '|' && d == 1){
                    num2 *= cont;
                    num2 += txt-48;
                    cont *= 10;
                    //printf("num2 = %f\n", num2);
                }
                txt = fgetc(file3); //caracteres do que tem dentro do db
            }
        }

        //separa os usuarios e suas respectivas colunas(id,user,pass,saldo)
        if(txt == ','){
            c++;
        }
        if(txt == '|'){
            c = 0;
            u++;
        }
    }
    num /= 10;
    num2 /= 100;

    return num + num2;

}

//Tela do usuario
void telaUser(char user[], int idUser){

    int op;
    system("cls");
    
    while(1){
        printf("Bem Vindo %s do id %d!\n", user, idUser);
        printf("\n1 - Mostrar saldo\n");
        printf("2 - Sair\n");
        printf("\n> ");
        scanf("%d", &op);
        system("cls");

        if(op >= 1 && op <= 2){
            if(op == 1){
                float res = saldoUser(idUser);
                printf("saldo = %.2f\n\n", res);
            }else if(op == 2){
                break;
            }
        }else{
            printf("Opcao invalida!\n\n");
        }
    }
}

//Verifica se o usuario e senha tem no db
void verify(char user[], char pass[], int *idUser, int *verifyUser, int *verifyPass){

    int c = 0; //colunas no db
    int u = 1; //numero do usuario

    char txt; //caracteres do db
    FILE *file;
    file = fopen("usuarios.txt", "r");

    int count = 0; //conta os caracteres da senha do db
    int count2 = 0; //conta os caracteres da senha
    int count3 = 0; //conta os caracteres do usuario

    int us = 0; //conta a qntd de caracteres iguais com o usuario
    int s = 0; //conta a qntd de caracteres iguais com a senha

    int passN = 0; //mostra o id da senha selecionado
    int verS = 0; //mostra se existe a senha digitada no db

    int userN = 0; //mostra o id do usuario selecionado
    int verU = 0; //mostra se existe o usuario digitada no db

    int end = 0; //verifica se a validacao do user ja foi feita

    float num = 0;
    float num2 = 0;
    int d = 0;
    
    //contador de caracteres do user
    for(int i=0;user[i]!='\0';i++){
        count3++;
    }
    //contador de caracteres do pass
    for(int i=0;pass[i]!='\0';i++){
        count2++;
    }

    //passa por todos os caracteres do db
    while(txt != EOF){
        txt = fgetc(file); //caracteres do que tem dentro do db

        //verifica o campo usuario
        if(txt != '|' && txt != ',' && c == 1 && end == 0){
            if(user[count] == txt){
                us++;
            }
            count++;
        }else if(txt == ','){
            if(count == us && count == count3){
                verU = 1;
                userN = u;
                end = 1;
            }
        }

        //verifica o campo senha
        if(end == 2){
            while(txt != ','){
                if(pass[count] == txt){
                    s++;
                }
                count++;
                txt = fgetc(file); //caracteres do que tem dentro do db
            }
            end = 3;

            if(count == s && count == count2){
                verS = 1;
                break;
            }
        }

        //se terminou a validacao do user, ele ja pode entrar na validacao do pass
        if(end == 1){
            end++;
        }

        //se a senha estiver errada, ele sai do loop
        if(end == 3){
            break;
        }

        //separa os usuarios e suas respectivas colunas(id,user,pass,saldo)
        if(txt == ','){
            c++;
            count = 0;
            s = 0;
            us = 0;
        }
        if(txt == '|'){
            c = 0;
            u++;
        }
    }
    //printf("\nidUser = %d\ntemUser? %d\nsenhaCorreta? %d\nuser = %s\npass = %s\n", userN, verU, verS, user, pass);

    *idUser = userN;
    *verifyUser = verU;
    *verifyPass = verS;

}

//Faz o login do usuario
void login(){

    char user[50];
    char pass[50];

    int idUser;
    int verifyUser;
    int verifyPass;

    printf("Digite seu usuario: ");
    scanf("%s", &user);
    printf("Digite sua senha: ");
    scanf("%s", &pass);

    verify(user,pass,&idUser,&verifyUser,&verifyPass);

    if(verifyUser == 1 && verifyPass == 1){
        //system("cls");
        telaUser(user,idUser);
    }else{
        system("cls");
        printf("Usuario ou senha invalido!\n\n");
    }

}

//Mostra quantos usuario tem no db
int id(){

    char txt; //caracteres do db
    FILE *file;
    file = fopen("usuarios.txt", "r");

    int u = 0;

    while(txt != EOF){
        txt = fgetc(file); //caracteres do que tem dentro do db

        if(txt == '|'){
            u++;
        }
    }

    return u;

}

//Verifica se existe um determinado usuario
int contador(char a[]){

    char txt; //caracteres do db
    FILE *file;
    file = fopen("usuarios.txt", "r");

    int c = 0;
    int u = 0;
    int i = 0;
    int us = 0;
    int count = 0;
    int count2 = 0;

    for(int i=0;a[i]!='\0';i++){
        count2++;
    }

    while(txt != EOF){
        txt = fgetc(file); //caracteres do que tem dentro do db

        //separa os usuarios e suas respectivas colunas(id,user,pass,saldo)
        if(txt == ','){
            c++;
            printf("c = %d\n", c);  
            txt = fgetc(file); //caracteres do que tem dentro do db
        }

        if(txt == '|'){
            c = 0;
            u++;
            txt = fgetc(file); //caracteres do que tem dentro do db
        }

        if(c == 1){
            if(txt == a[count]){
                us++;
            }
            count++;
        }else{
            if(count == count2 && count == us){
                return 1;
            }
            us = 0;
            count = 0;
        }
    }

    return 0;

}

//Cadastra usuarios novos
void cadastro(){

    FILE *file2;
    file2 = fopen("usuarios.txt", "a");

    int count = id();
    char userC[50];
    char passC[50];
    const float saldo = 00.00;
    int id = count+1;

    printf("Digite um usuario: ");
    scanf("%s", userC);
    printf("Digite uma senha: ");
    scanf("%s", passC);

    int res = contador(userC);
    if(res != 1){
        fprintf(file2, "%d,%s,%s,%.2f|", id, userC, passC, saldo);
        system("cls");
        printf("Usuario cadastrado com sucesso!\n\n");
    }else{
        system("cls");
        printf("Usuario existente!\n\n");
    }

    fclose(file2);

}

int main(){

    int opcao;
    system("cls");

    while(1){
        telaInicial();
        printf("> ");
        scanf("%d", &opcao);
        system("cls");

        if(opcao == 1){
            login();
        }else if(opcao == 2){
            cadastro();
        }else if(opcao == 3){
            break;
        }else{
            printf("Opcao invalida!\n\n");
        }
    }

    system("cls");
    printf("Tchau!");
    return 0;

}