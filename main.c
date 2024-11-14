#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>


#define DIAS_DA_SEMANA 4

typedef struct {


    char nome[100];
    char cpf[12];
    int quantidadePessoas, dia;
} Reserva;


bool validarCpf(const char *cpf) {
    if (strlen(cpf) != 11) {
        printf("CPF inválido! O CPF deve conter 11 dígitos.\n\n");
        return false;
    }
    return true;
}

void formatarCpf(const char *cpf, char *cpfFormato) {
    int j = 0;
    for (int i = 0; i < 11; i++) {
        if (i == 3 || i == 6) cpfFormato[j++] = '.';
        else if (i == 9) cpfFormato[j++] = '-';
        cpfFormato[j++] = cpf[i];
    }
    cpfFormato[j] = '\0';
}

void definirLimiteReservas(int limiteReservasDia[]) {
    printf("Ola anfitrião!\n\nInforme o numero de lugares que podem ser reservados  para cada dia:\n\n");
    for (int i = 0; i < DIAS_DA_SEMANA; i++) {
        switch (i) {
        case 0:
            printf("Quinta-feira:\n");
            break;
        case 1:
            printf("Sexta-feira:\n");
            break;
        case 2:
            printf("Sábado:\n");
            break;
        case 3:
            printf("Domingo:\n");
            break;
        default:
            printf("Opção inválida!\n");
            continue;
        }
        do {
            scanf("%d", &limiteReservasDia[i]);
            if (limiteReservasDia[i] <= 0) printf("O numero de lugares deve ser positivo, continue!\n");
        } while (limiteReservasDia[i] <= 0);
    }
}

bool registroReservas(Reserva *reserva, int *reservasDia, int *totalPessoas, int dia, int limiteReservasDia[]) {

    int lugaresDisponiveis = limiteReservasDia[dia - 1] - totalPessoas[dia - 1];

    if (reservasDia[dia - 1] < limiteReservasDia[dia - 1]) {
        printf("Informe o nome de quem vai reservar:\n");
        fgets(reserva->nome, sizeof(reserva->nome), stdin);
        reserva->nome[strcspn(reserva->nome, "\n")] = '\0';

        printf("Informe o CPF do cliente:\n");
        fgets(reserva->cpf, sizeof(reserva->cpf), stdin);
        reserva->cpf[strcspn(reserva->cpf, "\n")] = '\0';

        while (!validarCpf(reserva->cpf)) {
            printf("Informe o CPF do cliente:\n");
            fgets(reserva->cpf, sizeof(reserva->cpf), stdin);
            reserva->cpf[strcspn(reserva->cpf, "\n")] = '\0';
        }

        printf("Informe para quantas pessoas é a reserva:\n");
        scanf("%d", &reserva->quantidadePessoas);
        getchar();

        if (reserva->quantidadePessoas > lugaresDisponiveis) {
            printf("Erro: A quantidade de pessoas excede os lugares disponíveis para o dia %d.\n", dia);
            printf("Tente reservar em outro dia!\n");
            return false;
        }

        reserva->dia = dia;
        reservasDia[dia - 1]++;
        totalPessoas[dia - 1] += reserva->quantidadePessoas;

        printf("Reserva registrada com sucesso\n");
        return true;
    } else {
        printf("Limite de reservas excedido para o dia %d\n", dia);
        return false;
    }
}

void listarReservas(Reserva reserva[], int totalReservas) {
    printf("--------------- Listar Reservas ---------------\n\n");
    for (int i = 0; i < totalReservas; i++) {
        char cpfFormato[15];
        formatarCpf(reserva[i].cpf, cpfFormato);

        printf("Nome: %s\n", reserva[i].nome);
        printf("Cpf: %s\n", cpfFormato);
        printf("Dia: ");
        switch (reserva[i].dia) {
        case 1:
            printf("Quinta-feira\n");
            break;
        case 2:
            printf("Sexta-feira\n");
            break;
        case 3:
            printf("Sábado\n");
            break;
        case 4:
            printf("Domingo\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
        printf("Quantidade de pessoas: %d\n", reserva[i].quantidadePessoas);
        printf("===============================\n\n");
    }
}

void mostrarTotalPessoas(int totalPessoas[]) {
    printf("--------------- Total de pessoas por dia ---------------\n\n");
    printf("Quinta-feira %d\n", totalPessoas[0]);
    printf("Sexta-feira %d\n", totalPessoas[1]);
    printf("Sábado %d\n", totalPessoas[2]);
    printf("Domingo %d\n", totalPessoas[3]);
}

bool sair() {
    char confirmar;

    printf("Você deseja realmente sair (digite s/n)?\n");
    scanf("%c", &confirmar);
    getchar();

    if(confirmar == 's' || confirmar == 'S'){
        printf("encerrando...\n");
        return 1;
    }else{
    printf("Retornando ao menu...\n");
    return 0;
    }
}

void limparTela() {
    system("cls");
}

void pausarSistema() {
    system("pause");
}

int main() {
    setlocale(LC_ALL, "");

    Reserva reserva[100];
    int opcao, dia, totalReservas = 0;
    int reservasDia[DIAS_DA_SEMANA] = {0};
    int limiteReservasDia[DIAS_DA_SEMANA] = {0};
    char continuar;
    int totalPessoas[DIAS_DA_SEMANA] = {0};
    bool sairPrograma = false;



    definirLimiteReservas(limiteReservasDia);

    do {
        limparTela();
        printf("--------------- Escolha uma opção -------------\n\n");
        printf("1-Fazer reserva\n");
        printf("2-Listar reservas\n");
        printf("3-Total de pessoas por dia\n");
        printf("4-Sair\n\n");
        scanf("%d", &opcao);
        getchar();
        printf("\n");

        switch (opcao) {
        case 1:
            do {
                printf("Para qual dia é a reserva?\n");
                printf("1- Quinta-feira\n");
                printf("2- Sexta-feira\n");
                printf("3- Sábado\n");
                printf("4- Domingo\n\n");
                scanf("%d", &dia);
                getchar();
                printf("\n");

                if (dia >= 1 && dia <= 4) {
                    if (registroReservas(&reserva[totalReservas], reservasDia, totalPessoas, dia, limiteReservasDia)) {
                        totalReservas++;
                    }
                } else {
                    printf("Dia inválido!\n");
                }

                printf("Para continuar digite s/n:\n\n");
                scanf(" %c", &continuar);

            } while (continuar == 's' || continuar == 'S');
            break;

        case 2:
            limparTela();
            listarReservas(reserva, totalReservas);
            pausarSistema();
            break;

        case 3:
            limparTela();
            mostrarTotalPessoas(totalPessoas);
            pausarSistema();
            break;

        case 4:
            limparTela();

            if(sair()){
                sairPrograma = true;
            }

            break;

        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (!sairPrograma);

    return 0;
}
