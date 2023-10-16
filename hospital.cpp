#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//capacidade maxima de vetores
#define TOTAL 2

//estrutura data e hora
struct tm parse_date_hour(char *str) 
{
    struct tm tm = {0};
    char *token;

    token = strtok(str, "/ ");
    tm.tm_mday = atoi(token);
    token = strtok(NULL, "/ ");
    tm.tm_mon = atoi(token) - 1;
    token = strtok(NULL, "/ ");
    tm.tm_year = atoi(token) - 1900;
    token = strtok(NULL, ": ");
    tm.tm_hour = atoi(token);
    token = strtok(NULL, ": ");
    tm.tm_min = atoi(token);

    return tm;
}

//estrutura medico
typedef struct
{
	char CRM[12];
	char Nome[50];
	char Especialidade[50];
	char Email[50];
} Medico;

//estrutura paciente
typedef struct
{
	char CPF[12];
	char Nome[50];
	char Data_Nasc[12];
	char Email[50];
} Paciente;

//estrutura consulta
typedef struct
{
	char CRM[12];
	char CPF[12];
	time_t Data_Hora;
	char Consultorio[12];
} Consulta;

//Submenu MEDICOS
//Funcao Buscar CRM
//*vet_med, eh um ponteiro para o vetor de struct Medico
//total_med eh o total de médicos inclusos 

int buscar_med(Medico *vet_med, int total_med, char CRM[])
 {
	//percorrer o vetor
    for (int i = 0; i < total_med; i++)
	 {
	 //comparar o CRM que esta no vetor com o CRM 
    	//se estiver no vetor, retorna o indice do CRM informado
        if (strcmp(vet_med[i].CRM, CRM) == 0) 
		{
            return i;
        }
    }
    //se o CRM informado nao esta no vetor, retorna -1
    return -1;
}


//Funcao Incluir Medico

void incluir_med(Medico *vet_med, int *total_med)
 {
	//*total_med eh o ponteiro para acessar o conteudo do endereco de memoria do vetor de medicos
	//sera usado para verficiar o total de vetores livres para incluir novos medicos
	char CRM[12], Nome [50], Especialidade[50], Email[50];
	char lixo[2];
	
	if(*total_med == TOTAL)
	{
		printf("Nao ha mais espaco para incluir medicos!\n");
	}
	else
	{
		printf("Digite o CRM do medico que deseja incluir: \n");
		gets(CRM);
		
		//verificando se o CRM informado ja esta incluso no vetor
		if (buscar_med(vet_med, *total_med, CRM) != -1)
		{
			printf("Esse medico ja existe no sistema! \n");
		}
		else
		{ //se chegou aqui, o medico ainda nao tem o CRM no sistema e pode ser cadastrado
		printf("Digite o Nome do medico que deseja incluir: \n");
		gets(Nome);
		
		printf("Digite a Especialidade do medico que deseja incluir: \n");
		gets(Especialidade);
		
		printf("Digite o Email do medico que deseja incluir: \n");
		gets(Email);
		
		//inserindo os dados digitados no vetor de medicos
		strcpy(vet_med[*total_med].CRM, CRM);
		strcpy(vet_med[*total_med].Nome, Nome);
		strcpy(vet_med[*total_med].Especialidade, Especialidade);
		strcpy(vet_med[*total_med].Email, Email);
		
		//como inserimos um medico, eh preciso incrementar no vetor de medicos para modificar o total
		(*total_med)++;
		printf("Medico inserido com sucesso!\n\n ");
		}
		printf("Digite ENTER para continuar... \n");
		gets(lixo);
	}
}

//Funcao Alterar Medico
void alterar_med(Medico *vet_med, int *total_med)
{
	char CRM[12], Nome[50], Especialidade[50], Email[50];
	char lixo[2];
	//variavel indice sera usada para alterar o medico em sua posicao original no vetor
	//diferente da funcao Incluir, em que o medico era inserido na ultima posicao livre do vetor
	int indice;
	
	printf("Digite o CRM do medico que deseja alterar: \n");
	gets(CRM);
	
	//verificando se o CRM já existe no sistema
	indice = buscar_med(vet_med, *total_med, CRM);
	
	if (indice == -1)
	{
		printf("Esse CRM nao existe no sistema! \n");
	}
	//se chegou aqui, eh porque o CRM existe no sistema e pode ser alterado
	else
	{
	printf("Digite o Nome do medico que deseja alterar: \n");
		gets(Nome);
		
		printf("Digite a Especialidade do medico que deseja alterar: \n");
		gets(Especialidade);
		
		printf("Digite o Email do medico que deseja alterar: \n");
		gets(Email);
		
		//alterando os dados digitados no indice original
		strcpy(vet_med[indice].Nome, Nome);
		strcpy(vet_med[indice].Especialidade, Especialidade);
		strcpy(vet_med[indice].Email, Email);
		printf("Medico alterado com sucesso! \n\n");	
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
	
}

//Funcao Excluir Medico

void excluir_med(Medico *vet_med, int *total_med)
{
	char CRM[12];
    char lixo[2];
    int indice, i;
    
    printf("Digite o CRM do medico que deseja excluir do sistema: \n");
    gets(CRM);
    
    indice = buscar_med(vet_med, *total_med, CRM);
    
    //Se o indice for -1, o medico nao existe no sistema
    if(indice == -1)
	{
    	printf("Este medico nao existe no sistema!\n");
	}
	//Se chegou ate aqui, o medico esta cadastrado no sitema
	else
	{
		//percorrendo toda a lista de medicos do sistema pelo indidce do vetor
		for(i = indice; i<(*total_med)-1; i++)
		{
			//Estamos usando a strcpy para copiar a struct Medico de i+1 no lugar de i
			//deslocando para a esquerda os elementos armazenados no vetor (i+1) para apagar o medico desejado
			strcpy( vet_med[i].CRM, vet_med[i+1].CRM );
            strcpy( vet_med[i].Nome, vet_med[i+1].Nome );
            strcpy( vet_med[i].Especialidade, vet_med[i+1].Especialidade );
            strcpy( vet_med[i].Email, vet_med[i+1].Email );
		}
		//decrementa o total de medicos inclusos no sistema 
		(*total_med)--;
		printf("O Medico foi excluido com sucesso!\n\n");
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
}

void consultar_med(Medico *vet_med, int *total_med)
{
	char CRM[12];
    char lixo[2];
    int indice; 
		
	printf("Digite o CRM do medico que deseja consultar: \n");
	gets(CRM);
	
	//usando a funcao buscar_med para encontrar o medico pelo CRM informado
	indice = buscar_med(vet_med, *total_med, CRM);
	
	if (indice == -1)
	{
		printf("O CRM informado nao existe no sistema!");
	}
	//se chegou aqui, o medico existe no sistema
	else
	{
		printf("CRM: %s\n",  vet_med[indice].CRM);
        printf("Nome: %s\n", vet_med[indice].Nome);
        printf("Especialidade: %s\n",  vet_med[indice].Especialidade);
        printf("Email: %s\n", vet_med[indice].Email);
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
}

void listar_todos_med(Medico *vet_med, int *total_med)
{
	char lixo[2];
	int indice;
	
	if ((*total_med == 0))
	{
		printf("Nao existe medicos cadastrados no sistema! \n");
	}
	//se chegou aqui, existe pelo o menos um medico cadastrado no sistema
	else
	{
		//percorrendo a lista de total de medicos para achar todos que estao cadastrados no sistema
		for(indice = 0; indice < (*total_med); indice++)
		{
			printf("\n\n");
			printf("Medico %d\n", indice);
			printf("CRM: %s\n", vet_med[indice].CRM);
			printf("Nome: %s\n", vet_med[indice].Nome);
			printf("Especialidade: %s\n", vet_med[indice].Especialidade);
			printf("Email: %s\n", vet_med[indice].Email);
		}
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
}



//Sub Menu PACIENTES

//Funcao para bucar pacientes pelo CPF
int buscar_pac(Paciente *vet_pac, int total_pac, char CPF[])
{
	
    for (int i = 0; i < total_pac; i++)
	 {
        if (strcmp(vet_pac[i].CPF, CPF) == 0)
		{
            return i;
        }
    }
    return -1;
}

//Funcao Incluir Paciente

void incluir_pac(Paciente *vet_pac, int *total_pac)
{
	
	char CPF[12], Nome [50], Data_Nasc[50], Email[50];
	char lixo[2];
	
	if(*total_pac == TOTAL)
	{
		printf("Nao ha mais espaco para incluir pacientes!\n");
	}
	else
	{
		printf("Digite o CPF do paciente que deseja incluir: \n");
		gets(CPF);
		
		if (buscar_pac(vet_pac, *total_pac, CPF) != -1)
		{
			printf("Esse paciente ja existe no sistema! \n");
		}
		else
		{ 
		printf("Digite o Nome do paciente que deseja incluir: \n");
		gets(Nome);
		
		printf("Digite a data de nascimento do paciente que deseja incluir: \n");
		gets(Data_Nasc);
		
		printf("Digite o Email do paciente que deseja incluir: \n");
		gets(Email);
		
		strcpy(vet_pac[*total_pac].CPF, CPF);
		strcpy(vet_pac[*total_pac].Nome, Nome);
		strcpy(vet_pac[*total_pac].Data_Nasc, Data_Nasc);
		strcpy(vet_pac[*total_pac].Email, Email);
		
		(*total_pac)++;
		printf("Paciente inserido com sucesso!\n\n ");
		}
		printf("Digite ENTER para continuar... \n");
		gets(lixo);
	}
}

//Funcao Alterar Paciente
void alterar_pac(Paciente *vet_pac, int *total_pac)
{
	char CPF[12], Nome[50], Data_Nasc[50], Email[50];
	char lixo[2];
	int indice;
	
	printf("Digite o CPF do paciente que deseja alterar: \n");
	gets(CPF);
	
	indice = buscar_pac(vet_pac, *total_pac, CPF);
	
	if (indice == -1)
	{
		printf("Esse CPF nao existe no sistema! \n");
	}
	
	else
	{
		printf("Digite o Nome do paciente que deseja alterar: \n");
		gets(Nome);
		
		printf("Digite a data de nascimento do paciente que deseja alterar: \n");
		gets(Data_Nasc);
		
		printf("Digite o Email do paciente que deseja alterar: \n\n");
		gets(Email);
		
		strcpy(vet_pac[indice].Nome, Nome);
		strcpy(vet_pac[indice].Data_Nasc, Data_Nasc);
		strcpy(vet_pac[indice].Email, Email);
		printf("Paciente alterado com sucesso! \n\n");
		
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
	
}

//Funcao Excluir Paciente

void excluir_pac(Paciente *vet_pac, int *total_pac)
{
	char CPF[12];
    char lixo[2];
    int indice, i;
    
    printf("Digite o CPF do paciente que deseja excluir do sistema: \n");
    gets(CPF);
    
    indice = buscar_pac(vet_pac, *total_pac, CPF);
    
    if(indice == -1)
	{
    	printf("Este paciente nao existe no sistema!");
	}
	else
	{
		for(i= indice; i<(*total_pac)-1; i++)
		{
			strcpy( vet_pac[i].CPF, vet_pac[i+1].CPF );
            strcpy( vet_pac[i].Nome, vet_pac[i+1].Nome );
            strcpy( vet_pac[i].Data_Nasc, vet_pac[i+1].Data_Nasc );
            strcpy( vet_pac[i].Email, vet_pac[i+1].Email );
		}
		(*total_pac)--;
		printf("O Paciente foi excluido com sucesso!\n\n");
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
}

//funcao consultar paciente
void consultar_pac(Paciente *vet_pac, int *total_pac)
{
	char CPF[12];
    char lixo[2];
    int indice; 
		
	printf("Digite o CPF do paciente que deseja consultar: \n");
	gets(CPF);
	
	indice = buscar_pac(vet_pac, *total_pac, CPF);
	
	if (indice == -1)
	{
		printf("O CPF informado nao existe no sistema!");
	}
	else
	{
		printf("CPF: %s\n",  vet_pac[indice].CPF);
        printf("Nome: %s\n", vet_pac[indice].Nome);
        printf("Data de nascimento: %s\n",  vet_pac[indice].Data_Nasc);
        printf("Email: %s\n", vet_pac[indice].Email);
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
}

//Funcao consultar todos os pacientes
void consultar_todos_pac(Paciente *vet_pac, int *total_pac)
{
	char lixo[2];
	int indice;
	
	if ((*total_pac == 0))
	{
		printf("Nao existe pacientes cadastrados no sistema! \n");
	}
	else
	{
		for(indice = 0; indice < (*total_pac); indice++)
		{
			printf("\n \n");
			printf("Paciente %d\n", indice);
			printf("CPF: %s\n", vet_pac[indice].CPF);
			printf("Nome: %s\n", vet_pac[indice].Nome);
			printf("Data de nascimento: %s\n", vet_pac[indice].Data_Nasc);
			printf("Email: %s\n", vet_pac[indice].Email);
		}
	}
	printf("Digite ENTER para continuar... \n");
	gets(lixo);
}


//Submenu CONSULTAS

//funcao buscar Consultas
//verifica se existe uma consulta com certo CRM do medico, CPF do paciente e Data/Hora da consulta cadastrada
//utiliza como parametros o vetor de consultas, total de consultas, e todas as chaves de consultas (CRM, CPF e Data/Hora da consulta)
int buscar_consu(Consulta *vet_consu, int total_consu, char CRM[], char CPF[])
{
	int indice;
	//struct tm tm_consulta = parse_date_hour(Data_Hora);
	//percorre o vetor de consultas ate o total de consultas cadastradas
	for (indice = 0; indice < total_consu; indice++)
	{
		//compara o CRM, CPF e Data/Hora informado com os inseridos no sistema de consultas
		if ((strcmp(vet_consu[indice].CRM, CRM) == 0) &&
            (strcmp(vet_consu[indice].CPF, CPF) == 0))
		{
			return indice;
		}
	//se chegou aqui, nao existe um dos dados informados no sistema
	}
	return -1;
}

//funcao Incluir Consultas

//utiliza como parametros o total_med e total_pac para verificar quantos medicos e pacientes estao inclusos no vetor
//tambem utiliza ponteiros vet_med e vet_pac para o vetor de medicos e pacientes
//ponteiro para o vetor de consultas (vet_consu) e para o total de consultas no vetor (total_consu)
void incluir_consu(Medico *vet_med, int total_med, Paciente *vet_pac, int total_pac, Consulta *vet_consu, int *total_consu)
{
	char CRM[12];
	char CPF[12];
	char Consultorio[12];
	char Data_Hora[17];
	char lixo[2];
	
	//verificando se ha espaco no armazenamento para incluir consultas
	if (*total_consu == TOTAL)
	{
		printf("Nao existe espaco para incluir novas consultas!\n");
	}
	//se chegou aqui, ha espaco no vetor
	else
	{
		printf("Digite o CRM do medico: \n");
		gets(CRM);
		
		//comparando o CRM informado com os CRM cadastrados
		if(buscar_med(vet_med, total_med, CRM) == -1)
		{
			printf("Esse medico nao existe no sistema! \n");
		}
		//se chegou aqui, o CRM esta cadastrado no sistema e o usuario pode digitar o CPF do paciente
		else 
		{
			printf("Digite o CPF do paciente: \n");
			gets(CPF);
			if(buscar_pac(vet_pac, total_pac, CPF) == -1)
			{
				printf("Esse paciente nao existe no sistema! \n");
			}
			//se chegou aqui, o CPF esta cadastrado no sistema e o usuario pode incluir uma consulta
			else
			{
				//verificar se a consulta existe
				if(buscar_consu(vet_consu, *total_consu, CRM, CPF) != -1)
				{
					printf("Essa consulta ja existe! ");
				}
				//tudo ok, receber consultorio, data e hora da consulta e inserir no vetor
				else
				{
					printf("Digite o consultorio para esse cadastro: \n");
					gets(Consultorio);
					printf("Digite a data e hora da consulta (formato: DD/MM/AAAA HH:MM):\n");
                    gets(Data_Hora);
                    
                    //Convertendo a string Data_Hora para a estrutura tm
                    struct tm tm_consulta = parse_date_hour(Data_Hora);
                    //Convertendo a estrutura tm para time_t
        			time_t time_consulta = mktime(&tm_consulta);
					
					//copiando os conteudos do CRM e CPF para o vet_consu e inserindo os dados de Data/Hora e Consultorio
					strcpy(vet_consu[*total_consu].CRM, CRM);
					strcpy(vet_consu[*total_consu].CPF, CPF);
					strcpy(vet_consu[*total_consu].Consultorio, Consultorio);
					vet_consu[*total_consu].Data_Hora = time_consulta;
					
					//incrementando no vetor o total de consultas
					(*total_consu)++;
					printf("Consulta incluida com sucesso! \n");
				}
			}
		}
	}
	printf("Digite ENTER para continuar \n");
	gets(lixo);
}


// Função Alterar Consultas
void alterar_consu(Consulta *vet_consu, int *total_consu)
{
    char CRM[12];
    char CPF[12];
    char Consultorio[12];
    char Data_Hora[17];
    char lixo[2];
    int indice;

    printf("Digite o CRM do medico: \n");
    gets(CRM);
    printf("Digite o CPF do paciente: \n");
    gets(CPF);

    // Verificando se a consulta escolhida existe
    indice = buscar_consu(vet_consu, *total_consu, CRM, CPF);

    if (indice == -1)
    {
        printf("Essa consulta nao existe no sistema! \n");
    }
    // Se chegou aqui, a consulta está no sistema e pode ser alterada
    else
    {
        // Recebendo os novos dados e alterando os dados do vetor na posição "indice"
        printf("Digite o consultorio:\n ");
        gets(Consultorio);
        printf("Digite a nova data e hora da consulta (formato: DD/MM/AAAA HH:MM):\n");
        gets(Data_Hora);

        // Convertendo a string Data_Hora para a estrutura tm
        struct tm tm_consulta = parse_date_hour(Data_Hora);

        strcpy(vet_consu[indice].Consultorio, Consultorio);
        vet_consu[indice].Data_Hora = mktime(&tm_consulta);

        printf("Consulta alterada com sucesso! \n");
    }
    printf("Digite ENTER para continuar \n");
    gets(lixo);
}



// Função Excluir Consulta
void excluir_consu(Consulta *vet_consu, int *total_consu)
{
    char CRM[12];
    char CPF[12];
    char lixo[2];
    int indice, i;

    printf("Digite o CRM do medico: \n");
    gets(CRM);
    printf("Digite o CPF do paciente: \n");
    gets(CPF);

    // Verificando se a consulta escolhida existe
    indice = buscar_consu(vet_consu, *total_consu, CRM, CPF);

    if (indice == -1)
    {
        printf("Essa consulta nao existe no sistema! \n");
    }
    // Se chegou aqui, a consulta está no sistema e pode ser excluída
    else
    {
        for (i = indice; i < (*total_consu) - 1; i++)
        {
            // Deslocando para a esquerda os elementos seguintes armazenados no vetor (i+1)
            strcpy(vet_consu[i].CRM, vet_consu[i + 1].CRM);
            strcpy(vet_consu[i].CPF, vet_consu[i + 1].CPF);
            strcpy(vet_consu[i].Consultorio, vet_consu[i + 1].Consultorio);
            vet_consu[i].Data_Hora = vet_consu[i + 1].Data_Hora;
        }
        // Decrementando o total de consultas
        (*total_consu)--;
        printf("A consulta foi excluida com sucesso! \n");
    }
    printf("Digite ENTER para continuar \n");
    gets(lixo);
}


void consultar_consu(Consulta *vet_consu, int *total_consu)
{
    char CRM[12];
    char CPF[12];
    char lixo[2];
    int indice;

    printf("Digite o CRM do medico: \n");
    gets(CRM);
    printf("Digite o CPF do paciente: \n");
    gets(CPF);

    // Verificando se a consulta escolhida existe
    indice = buscar_consu(vet_consu, *total_consu, CRM, CPF);

    if (indice == -1)
    {
        printf("Essa consulta nao existe no sistema! \n");
    }
    // Se chegou aqui, a consulta está no sistema e pode ter os dados exibidos
    else
    {
        // Exibindo os dados da consulta
        printf("CRM do medico: %s\n", vet_consu[indice].CRM);
        printf("CPF do paciente: %s\n", vet_consu[indice].CPF);
        printf("Consultorio: %s\n", vet_consu[indice].Consultorio);

        // Convertendo o valor time_t em uma string formatada
        char data_hora[20];
        strftime(data_hora, sizeof(data_hora), "%d/%m/%Y %H:%M", localtime(&vet_consu[indice].Data_Hora));
        printf("Data e Hora: %s\n", data_hora);
    }
    printf("Digite ENTER para continuar \n");
    gets(lixo);
}


void consultar_todas_consu(Consulta *vet_consu, int *total_consu)
{
    char lixo[2];
    int indice;

    // Verificando se existem consultas cadastradas no sistema
    if ((*total_consu) == 0)
    {
        printf("Nao existem consultas cadastradas no sistema! \n");
    }
    // Se chegou aqui, existem consultas no sistema
    else
    {
        // Percorrendo o vetor de consultas e exibindo seus dados
        for (indice = 0; indice < (*total_consu); indice++)
        {
            printf("CRM do medico: %s\n", vet_consu[indice].CRM);
            printf("CPF do paciente: %s\n", vet_consu[indice].CPF);
            printf("Consultorio: %s\n", vet_consu[indice].Consultorio);

            // Convertendo o valor time_t em uma string formatada
            char data_hora[20];
            strftime(data_hora, sizeof(data_hora), "%d/%m/%Y %H:%M", localtime(&vet_consu[indice].Data_Hora));
            printf("Data e Hora: %s\n", data_hora);
        }
    }
    printf("Digite ENTER para continuar \n");
    gets(lixo);
}



int main()
{
    Medico armazenamento_med[TOTAL];   
    Paciente armazenamento_pac[TOTAL];
    Consulta armazenamento_consu[TOTAL];
    
    int total_med = 0;
    int total_pac = 0;
    int total_consu = 0;
    int opcao, opcao_sub_menu;

    do {
        printf("--------MENU PRINCIPAL----------");
        printf("\nSubmenu de Medicos..............1");
        printf("\nSubmenu de Pacientes............2");
        printf("\nSubmenu de Consultas............3");
        printf("\nSair............................4\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d%*c", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                do {
                    printf("--------SUBMENU MEDICOS-------");
                    printf("\nIncluir Medico................1");
                    printf("\nAlterar Medico................2");
                    printf("\nExcluir Medico................3");
                    printf("\nConsultar Medico..............4");
                    printf("\nListar Todos os Medicos.......5");
                    printf("\nVoltar ao Menu Principal......6\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &opcao_sub_menu);
                    printf("\n");

                    switch (opcao_sub_menu) {
                        case 1:
                            incluir_med(armazenamento_med, &total_med);
                            break;
                        case 2:
                            alterar_med(armazenamento_med, &total_med);
                            break;
                        case 3:
                            excluir_med(armazenamento_med, &total_med);
                            break;
                        case 4:
                            consultar_med(armazenamento_med, &total_med);
                            break;
                        case 5:
                            listar_todos_med(armazenamento_med, &total_med);
                            break;
                        case 6:
                            printf("Voltar ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_sub_menu != 6);
                break;
            case 2:
                do {
                    printf("--------SUBMENU PACIENTES--------");
                    printf("\nIncluir Paciente................1");
                    printf("\nAlterar Paciente................2");
                    printf("\nExcluir Paciente................3");
                    printf("\nConsultar Paciente..............4");
                    printf("\nListar Todos os Pacientes.......5");
                    printf("\nVoltar ao Menu Principal........6\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &opcao_sub_menu);
                    printf("\n");

                    switch (opcao_sub_menu) {
                        case 1:
                            incluir_pac(armazenamento_pac, &total_pac);
                            break;
                        case 2:
                            alterar_pac(armazenamento_pac, &total_pac);
                            break;
                        case 3:
                            excluir_pac(armazenamento_pac, &total_pac);
                            break;
                        case 4:
                            consultar_pac(armazenamento_pac, &total_pac);
                            break;
                        case 5:
                            consultar_todos_pac(armazenamento_pac, &total_pac);
                            break;
                        case 6:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_sub_menu != 6);
                break;
            case 3:
                do {
                    printf("--------SUBMENU CONSULTAS----------");
                    printf("\nIncluir Consulta................1");
                    printf("\nAlterar Consulta................2");
                    printf("\nExcluir Consulta................3");
                    printf("\nListar uma Consulta.............4");
                    printf("\nListar Todas as Consultas.......5");
                    printf("\nVoltar ao Menu Principal........6\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &opcao_sub_menu);
                    printf("\n");

                    switch (opcao_sub_menu) {
                        case 1:
                            incluir_consu(armazenamento_med, total_med, armazenamento_pac, total_pac, armazenamento_consu, &total_consu);
                            break;
                        case 2:
                            alterar_consu(armazenamento_consu, &total_consu);
                            break;
                        case 3:
                            excluir_consu(armazenamento_consu, &total_consu);
                            break;
                        case 4:
                            consultar_consu(armazenamento_consu, &total_consu);
                            break;
                        case 5:
                            consultar_todas_consu(armazenamento_consu, &total_consu);
                            break;
                        case 6:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_sub_menu != 6);
                break;
        }
    } while (opcao != 3);
}
