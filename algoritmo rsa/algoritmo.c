#include<stdio.h>
#include<unistd.h>
#include<locale.h>
#include<math.h> 
#include<stdlib.h>

int analisar_primo(int numero, int d);   //DECLARAÇÃO DE FUNÇÕES
void mdc(int a, int b, double relativo, int aux, int array[]);

int flush(){
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
return 0;
}

int inverso_modulo(int a, int b)
{
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

int powMod(int a, int b, int n) {
	long long x = 1, y = a;

	while (b > 0) {
		if (b % 2 == 1)
			x = (x * y) % n;
		y = (y * y) % n; 
		b /= 2;
	}

	return x % n;
}

int scmdc(double relativo, int array[]){
    int a;
    scanf("%d", &a);
    mdc(a, relativo, relativo, a, array);
    return a;
}

void mdc(int a, int b, double relativo, int aux, int array[]){
    if (b!=0) return mdc(b,a%b, relativo, aux, array);
    else if (a != 1){
        printf("O número escolhido não é relativamente primo a %.2lf\n", relativo);
        printf("Por favor, escolha outro: ");
        scmdc(relativo, array);
    }
    else if (a == 1) {
        array[5] = aux;
        return;
    }
}

int escolher_primo(){
    int n1;
    scanf("%d", &n1);
    analisar_primo(n1, 1);
    return n1;
}

void desencriptar(int array[]){
    int primo1, primo2;
    int e;

    printf("Digite o par de números primos escolhidos ao gerar a chave pública\n");
    scanf("%i%i",&primo1,&primo2);
    
    printf("Digite o número coprimo escolhido: ");
    scanf("%i", &e);

    int totiente=(primo1-1)*(primo2-1);
    int n=primo1*primo2;
    int d;
    d = inverso_modulo(e, totiente);

    int numberArray[100];

    printf("Mensagem desencriptada: ");

    FILE *arq;

    arq = fopen("código.txt" , "r");

        for (int i = 0; !feof(arq) ; i++){

            fscanf(arq, "%d ", &numberArray[i]);

            int valor = powMod(numberArray[i],d,n);
            valor+=95;
            if (valor==123) printf(" ");
            else printf("%c", valor);
        }


    fclose(arq);

    printf("\n\n");
    return;

}

void encriptar(int array[], char frase[], int mi[]){
    int n, e;

    FILE *arq;

    arq = fopen("código.txt", "w");
        printf("\n\nDigite a chave pública previamente recebida.\n");
        scanf("%i%i", &n, &e);
        printf ("Digite a mensagem que deseja encriptar: ");
	    scanf(" %[^\t\n]s", frase);

	    for (int i=0; frase[i]!=0; i++){
	        mi[i] = frase[i];
	        if (mi[i]==97) mi[i] = 2;

	        else if (mi[i]==32) mi[i] = 28;

	        else {mi[i] = mi[i] - 95;}

	        int valor=powMod(mi[i], e, n);
	        fprintf(arq, "%d ", valor);
        }

    fclose(arq);
    
    sleep(1);
    printf("\nMensagem encriptada com sucesso!\nCódigo guardado no arquivo código.txt\n");

    return;
}

int analisar_primo(int numero, int d){
    int i;
    for (i = 2; i<=numero; i++){
        if (numero%i == 0) d++;
    }
    if (d == 2){
        return numero;
    }
    else {
        printf("O número escolhido não é primo.\n");
        printf("Por favor, escolha outro: ");
        escolher_primo(numero, 1);
    }
    return 1;
}

void gerar_chave(int array[]){
    int n1, n2;


    FILE *arq;

    printf("Por favor, digite dois números primos.\n");
    n1 = escolher_primo();
    array[0] = n1;
    n2 = escolher_primo();
    array[1] = n2;
    int n = n1*n2;
    array[2] = n;

    double totiente = (n1-1)*(n2-1);
    array[3] = totiente;
    printf("Por favor, digite um número que seja primo relativo a %.2lf\n", totiente);

    int expoente;
    expoente = scmdc(totiente, array);
    array[4] = expoente;

    printf("\n\n       ******************************************* \n      ******************ATENÇÃO********************\n     ***                                         ***\n     ***    Não divulge os números escolhidos!   ***\n     ***   Anote e guarde-os para uso próprio!!  ***\n     ***                                         ***\n      *********************************************\n       ******************************************* \n\n");

    arq = fopen("ChavePública.txt" , "w");
        printf("Gerando chave...\n");
        sleep(2);
        fprintf(arq,"%i %i", n, expoente);
        fclose(arq);
    
    printf("\nChave gerada com sucesso.\n\n");
    sleep(1);
    return;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    int array[10];
    char frase[100];
    int mi[100];
    int a;

    flush();
    printf("Iniciando programa...\n\n\n\n\n");
    sleep(1);

    printf("Selecione a opção desejada:\n");
    sleep(1);
    printf("1- Gerar chave pública.\n");
    printf("2- Encriptar\n");
    printf("3- Desencriptar\n");
    scanf("%d", &a);

    if (a == 1) gerar_chave(array);
    if (a == 2) encriptar(array, frase, mi);
    if (a == 3) desencriptar(array);
    else if (a != 1 && a!=2 && a!=30) printf("Opção inválida.\n");
    sleep(1);

    int reiniciar;

    printf("\n\nVocê deseja fazer outra operação?\n");
    printf("1 para sim, 0 para não: ");
    scanf("%d", &reiniciar);

    if (reiniciar == 1) return main();
    else return 0;
}