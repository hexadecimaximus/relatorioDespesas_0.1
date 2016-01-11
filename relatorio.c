/**
Nome: Relatorio
Programador: Rodrigo "Seth" de Freitas <rodrigo.freitas33@etec.sp.gov.br>
Manutenção: Rodrigo "Seth" de Freitas <rodrigo.freitas33@etec.sp.gov.br>
Versão: 0.1
Licença: GPL/GPLv2

Programa que visa, através de dados fornecidos pelo usuário, dar relatórios sobre gastos mensais, desde coisas mensais - o que é isso? - 
até mesmo coisas supérfluas, que ele compra vez ou outra. O programa é dividido em:
A) Gastos Mensais: São gastos "fixos", que ocorrem mês a mês. Ex: conta de luz, água, internet, plano de saúde, etc.
B) Pequenos Gastos: São gastos que não ocorrem na mesma frequência de um gasto mensal fixo, mas que são computados, afim de ter uma avaliação
de quanto está sendo gasto com coisas "superfluas". Ex: cafézinho, restaurante, livraria, etc.
Os dados são armazenados em um banco de dados, MySQL-5.5.46 para esta versão, mas ele pode ser adaptado para outros SGBDs, e até mesmo para outras 
plataformas. Desenvolvido em Debian 8.1 Jessie, sem recursos de interface gráfica ou internet - não que não possa ser feito em um futuro talvez não
muito distante :P
*/

/*TODO
	* verificar erros em funções scanf() em versões futuras
	* verificar erros em funções fgets() em versões futuras
	* usar strncpy() em versões futuras
	* usar strncat em versões futuras
	* menus em arquivos texto separados, em versões futuras
	* verificar a contagem correta dos dados inseridos, em versões futuras
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include "day.h"
#include "month.h"
#include "data.h"
#define VISTA "a vista"
#define CREDITO "cartão crédito"

void insereDadosPequenosGastos(void);
void selecionaFuncao(void);
void insereBDPequenosGastos(const char*, const char*, const char*, const char*, float, const char*);
void consultaBDPequenosGastos(void);
void consultaDiaMes(void);
void consultaDiaMesAno(void);
void consultaDespesa(void);
void consultaIntervTempo(void);


void consultaDiaMesAno(void){
	MYSQL conexao;
	MYSQL_RES* resp;
	MYSQL_ROW linhas;
	MYSQL_FIELD* campos;
	char ano[5], mes[3], dia[3], query[300];
	int contador;

	puts("\nInsira o ano, com quatro dígitos: ");
	scanf(" %4[^\n]", ano);
	puts("Insira o mês, com dois dígitos: ");
	scanf(" %3[^\n]", mes);
	puts("Insira o dia, com dois dígitos: ");
	scanf(" %3[^\n]", dia);

	mysql_init(&conexao);

	if(mysql_real_connect(&conexao, HOST, USER, PASSWD, DATABASE, 0, NULL, 0)){
		puts("\nConectado com sucesso");

		sprintf(query, "SELECT * FROM pg2015 WHERE TRIM(LEFT(data, 4)) = '%s' AND TRIM(SUBSTRING(data, '6', 2)) = '%s' AND TRIM(RIGHT(data, 2)) = '%s';", ano, mes, dia);
		if(mysql_query(&conexao, query))
			printf("\nErro: %d: %s", mysql_errno(&conexao), mysql_error(&conexao));
		else{
			resp = mysql_store_result(&conexao);
			if(resp){
				campos = mysql_fetch_fields(resp);
				for(contador = 0; contador < mysql_num_fields(resp); contador++){
					printf("%s\t", (campos[contador].name));

					if(mysql_num_fields(resp) > 1)
						printf("\t");
				}			
			}
		}
		printf("\n");
		while((linhas = mysql_fetch_row(resp)) != NULL){
			for(contador = 0; contador < mysql_num_fields(resp); contador++)
				printf("%s          ", linhas[contador]);
				printf("\n");
		}
			
	}

	mysql_free_result(resp);
	mysql_close(&conexao);
}

void consultaDiaMes(void){
	MYSQL conexao;
	MYSQL_RES* resp;
	MYSQL_ROW linhas;
	MYSQL_FIELD* campos;
	char dia[3], mes[3], query[300];
	int contador;
	
	puts("\nInsira o dia, com dois dígitos: ");
	scanf(" %3[^\n]", dia);
	puts("Insira o mês, com dois dígitos: ");
	scanf(" %3[^\n]", mes);

	mysql_init(&conexao);

	if(mysql_real_connect(&conexao, HOST, USER, PASSWD, DATABASE, 0, NULL, 0)){
		puts("\nConectado com sucesso");
		sprintf(query, "SELECT * FROM pg2015 WHERE TRIM(RIGHT(data, 2)) = '%s' AND TRIM(SUBSTRING(data, '6', 2)) = '%s';", dia, mes);
		if(mysql_query(&conexao, query))
			printf("\nErro %d: %s", mysql_errno(&conexao), mysql_error(&conexao));
		else{
		resp = mysql_store_result(&conexao);
			if(resp){
				campos = mysql_fetch_fields(resp);
				for(contador = 0; contador < mysql_num_fields(resp); contador++){
					printf("%s\t", (campos[contador].name));

					if(mysql_num_fields(resp) > 1)
						printf("\t");
				}
		
			}
		}
		printf("\n");


		while((linhas = mysql_fetch_row(resp)) != NULL){
			for(contador = 0; contador < mysql_num_fields(resp); contador++)
				printf("%s          ", linhas[contador]);
				printf("\n");
		}
			
	}

	mysql_free_result(resp);
	mysql_close(&conexao);
}



void consultaBDPequenosGastos(){
	//MYSQL conexao;
	//MYSQL_RES* resp;
	//MYSQL_ROW linhas;
	//MYSQL_FIELD* campos;
	//char query_DiaMes[300];
	//char query_DiaMesAno[300];
	//char query_Despesa[300];
	//char query_Between[300];
	char choice;
	//int contador;

	/*mysql_init(&conexao);
	if(mysql_real_connect(&conexao, HOST, USER, PASSWD, DATABASE, 0, NULL, 0)){
		if(mysql_query(&conexao, query))
			printf("Erro: %d\n", mysql_error(&conexao));
		else
			resp = mysql_store_result(&conexao);

		if(resp){
			campos = mysql_fetch_fields(resp);
			for(contador = 0; contador < mysql_num_fields(resp); contador++){
				printf("%s\t", (campos[contador]).name);
				if(mysql_num_fields(resp) > 1)
					printf("\t");
			}
		}
		printf("\n");

		while((linhas = mysql_fetch_row(resp)) != NULL){
			for(contador = 0; contador < mysql_num_fields(resp); contador++)
				printf("%4s\t\t", linhas[contador]);
				printf("\n");
		}
	} */
	do{
	puts("Como deseja realizar a consulta?");
	puts("[1] Pelo dia e pelo mês (dd/mm)");
	puts("[2] Pelo dia, mês e ano (dd/mm/aaaa)");
	puts("[3] Pelo nome da despesa");
	puts("[4] Por intervalo de tempo");
	puts("[0] Retornar ao menu anterior");
	scanf(" %c%*c", &choice);
	if(choice != '1' && choice != '2' && choice != '3' && choice != '4')
		puts("Insira apenas os números do menu");
	else if(choice == '0')
		return;
	}while(choice != '1' && choice != '2' &&choice != '3' && choice != '4');

	if(choice == '1')
		consultaDiaMes();
	if(choice == '2')
		consultaDiaMesAno();		
	

	//mysql_free_result(resp);
	//mysql_close(&conexao);
}

void insereBDPequenosGastos(const char* data, const char* diaSemana, const char* mes, const char* despesa, float valor, const char* formaPgto){
	MYSQL conexao;
	//int size;
	int res;
	char query[300];
	
/*	printf("\n%s", data);
	printf("\n%s", diaSemana);
	printf("\n%s", mes);
	printf("\n%s", despesa);
	printf("tamanho despesa: %d", strlen(despesa));
	printf("\n%.2f", valor);
	printf("\n%s\n", formaPgto);*/
	mysql_init(&conexao);
	if(mysql_real_connect(&conexao, HOST, USER, PASSWD, DATABASE, 0, NULL, 0)){
		printf("\nConectado com sucesso\n");
		sprintf(query, "INSERT INTO pg2015(data, diaSemana, mes, despesa, valor, formaPgto) VALUES('%s', '%s', '%s', '%s', '%f', '%s');", data, diaSemana, mes, despesa, valor, formaPgto);
	res = mysql_query(&conexao, query);
			if(!res)
				printf("\nRegistros inseridos: %d\n", mysql_affected_rows(&conexao));
			else
				printf("\nErro na inserção %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));
		mysql_close(&conexao);
	}
	else{
		printf("\nFalha de conexao\n");
		printf("Erro: %d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));
	}
	
}


void selecionaFuncao(){
	char choice;
	do{
		puts("\nO que deseja fazer?");
		puts("[1] Inserir dados");
		puts("[2] Consultar dados");
		puts("[3] Alterar/atualizar dados");
		puts("[4] Apagar dados");
		puts("[0] Voltar ao menu anterior");
		scanf(" %c%*c", &choice);

		if(choice == '1')
			insereDadosPequenosGastos();
		else if(choice == '2')
			consultaBDPequenosGastos();
		else if(choice == '3')
			return;
		else if(choice == '4')
			return;
		else if(choice == '0')
			return;
		else
			puts("Digite os números do menu");
	}while(choice != '1' || choice != '2' || choice != '3' || choice != '4' || choice != '0');
}	
	

void insereDadosPequenosGastos(){
	char ano[5], mes[3], dia[3], diaSemana[16], mesExtenso[16], despesa[41], novaData[11], formaPgto[30];
	const char pipe[2] = "-";
	char selDia = ' ', selMes[3];
	char selPgto, choice;
	float valor; 
	puts("\nDigite o ano, com quatro dígitos: ");
	fgets(ano, 5, stdin);
	strcpy(novaData, ano);
	strcat(novaData, pipe);
	getchar();
	puts("Digite o mês, com dois dígitos: ");
	fgets(mes, 3, stdin);
	strcat(novaData, mes);
	strcat(novaData, pipe);
	getchar();
	puts("Digite o dia, com dois digitos: ");
	fgets(dia, 3, stdin);
	strcat(novaData, dia);

	do{
		puts("Selecione o dia da semana: ");
		puts("[1] Domingo");
		puts("[2] Segunda");
		puts("[3] Terça");
		puts("[4] Quarta");
		puts("[5] Quinta");
		puts("[6] Sexta");
		puts("[7] Sábado");
		scanf(" %c%*c", &selDia);
		//printf("\nO dia é %c", selDia);

		if(selDia == '1')
			strcpy(diaSemana, DOM);
		else if(selDia == '2')
			strcpy(diaSemana, SEG);
		else if(selDia == '3')
			strcpy(diaSemana, TER);
		else if(selDia == '4')
			strcpy(diaSemana, QUA);
		else if(selDia == '5')
			strcpy(diaSemana, QUI);
		else if(selDia == '6')
			strcpy(diaSemana, SEX);
		else if(selDia == '7')
			strcpy(diaSemana, SAB);
		else
			puts("Dia inválido. Selecione apenas um número do menu");
	}while(selDia != '1' && selDia != '2' && selDia != '3' && selDia != '4' && selDia != '5' && selDia != '6' && selDia != '7');

	do{
		puts("\nSelecione o mês");
		puts("[01] Janeiro\t[12] Dezembro");
		puts("[02] Fevereiro\t[11] Novembro");
		puts("[03] Março\t[10] Outubro");
		puts("[04] Abril\t[09] Setembro");
		puts("[05] Maio\t[08] Agosto");
		puts("[06] Junho\t[07] Julho");
		fgets(selMes, 3, stdin);
		__fpurge(stdin);

		if(strcmp(selMes, "01") == 0)
			strcpy(mesExtenso, JAN);
		else if(strcmp(selMes, "02") == 0)
			strcpy(mesExtenso, FEV);
		else if(strcmp(selMes, "03") == 0)
			strcpy(mesExtenso, MAR);
		else if(strcmp(selMes, "04") == 0)
			strcpy(mesExtenso, ABR);
		else if(strcmp(selMes, "05") == 0)
			strcpy(mesExtenso, MAI);
		else if(strcmp(selMes, "06") == 0)
			strcpy(mesExtenso, JUN);
		else if(strcmp(selMes, "07") == 0)
			strcpy(mesExtenso, JUL);
		else if(strcmp(selMes, "08") == 0)
			strcpy(mesExtenso, AGO);
		else if(strcmp(selMes, "09") == 0)
			strcpy(mesExtenso, SET);
		else if(strcmp(selMes, "10") == 0)
			strcpy(mesExtenso, OUT);
		else if(strcmp(selMes, "11") == 0)
			strcpy(mesExtenso, NOV);
		else if(strcmp(selMes, "12") == 0)
			strcpy(mesExtenso, DEZ);
		else
			puts("\nMês inválido. Selecione uma opção do menu");	
	}while((!strcmp(selMes, "01")== 0) && (!strcmp(selMes, "02") == 0) && (!strcmp(selMes, "03") == 0) && (!strcmp(selMes, "04") == 0) && (!strcmp(selMes, "05") == 0) && (!strcmp(selMes, "06") == 0) && (!strcmp(selMes, "07") == 0) && (!strcmp(selMes, "08") == 0) && (!strcmp(selMes, "09") == 0) && (!strcmp(selMes, "10") == 0) && (!strcmp(selMes, "11") == 0) && (!strcmp(selMes, "12") == 0));
	
	puts("\nDigite a despesa: ");
	//fgets(despesa, 41, stdin);
	scanf(" %40[^\n]", despesa);
	__fpurge(stdin);
	puts("\nDigite o valor: ");
	scanf("%f", &valor);
	__fpurge(stdin);

	do{
		puts("\nInsira a forma de pagamento: ");
		puts("[1] A vista");
		puts("[2] Cartão de crédito");
		scanf(" %c%*c", &selPgto);
		
		if(selPgto == '1')
			strcpy(formaPgto, VISTA);
		else if(selPgto == '2')
			strcpy(formaPgto, CREDITO);
		else
			puts("\nDigite as opções do menu");
	}while(selPgto != '1' && selPgto != '2');
	
	printf("\n\n\aOs seguintes dados serão inseridos no banco de dados");
	printf("\nData: %s", novaData);
	printf("\nDia da semana: %s", diaSemana);
	printf("\nMês: %s", mesExtenso);
	printf("\nDespesa: %s", despesa);
	printf("\nValor: %.2f", valor);
	printf("\nForma de pagamento: %s\n", formaPgto);
	puts("Você confirma? s/N");
	scanf(" %c%*c", &choice);

	if(choice == 'S' || choice == 's')
		insereBDPequenosGastos(novaData, diaSemana, mesExtenso, despesa, valor, formaPgto);
	if(choice == 'N' || choice == 'n')
		return;	
}


int main(void){
	char c;
	do{
		puts("\nSelecione a opção: ");
		puts("[1] Gastos mensais");
		puts("[2] Pequenos gastos");
		puts("[0] Sair");
		scanf(" %c%*c",&c);
		
		if(c == '1' )
			return;
		else if(c == '2')
			selecionaFuncao();
		else if(c == '0')
			exit(0);
		else if(c != '1' || c != '2')
			puts("\nDigite apenas os números do menu!!!");
	}while(c != '1' || c != '2' || c != '0');
return EXIT_SUCCESS;
}
			
