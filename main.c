#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16

int main(){
    int numDecimal1, numDecimal2, resultadoDecimal = 0, binario1[BITS], binario2[BITS], binresult[BITS], maiorBin, i;
    char op;

    printf("Digite o primeiro numero: \n");
    scanf("%d", &numDecimal1);
    fflush(stdin);
    printf("Digite a operacao: (+, -, * ou / ) ou 's' para Sair do Programa\n");
    scanf("%c", &op);
    fflush(stdin);
    printf("Digite o segundo numero: \n");
    scanf("%d", &numDecimal2);

    inicializaVetorZerado(binario1);
    inicializaVetorZerado(binario2);
    converteParaBinario(numDecimal1, binario1);
    converteParaBinario(numDecimal2, binario2);
    inicializaVetorZerado(binresult);

    switch(op)
    {
        case '+':
            resultadoDecimal = numDecimal1 + numDecimal2;
            printf("Resultado em Decimal: ");
            printf("%d + %d = %d \n", numDecimal1, numDecimal2, resultadoDecimal);
            printf("Resultado em Binario: \n");
            menuOpSoma(binario1, binario2, binresult);
            break;
        case '-':
            resultadoDecimal = numDecimal1 - numDecimal2;
            printf("Resultado em Decimal: ");
            printf("%d - %d = %d \n", numDecimal1, numDecimal2, resultadoDecimal);
            printf("Resultado em Binario: \n");
            menuOpSub(binario1, binario2, binresult);
            break;
        case '*':
            verificaZero(numDecimal1, numDecimal2, resultadoDecimal, op, binario1, binario2, binresult);
            break;
        case '/':
            verificaZero(numDecimal1, numDecimal2, resultadoDecimal, op, binario1, binario2, binresult);
            break;
        case 's':
            printf("SAINDO DO PROGRAMA...");
            break;
        default:
            printf("RESPOSTA INVALIDA");
            break;
    }

}

void converteParaBinario(int numdec, int vet_binario[BITS]){
    inicializaVetorZerado(vet_binario);
    int i, num_aux = numdec; //num_aux = numdec para ver se era um numero negativo e adicionar 1 no inicio depois
    
    if(numdec < 0){
        numdec = numdec * (-1); // deixar o numero decimal positivo
    }

    for(i = BITS - 1 ; i >= 0; i--){ //bits - 1 pois é do 15 até o 0 (16)
        if(numdec % 2 == 0 ){
            vet_binario[i] = 0;     
        }
        else{
            vet_binario[i] = 1;
        }
        numdec = numdec/2;

    }
    
    if(num_aux < 0){             
        vet_binario[0] = 1;  
    }
    printf("\n");
}

void imprimeBin(int bin[BITS]){
    for (int i = 0; i < BITS; i++){
        printf(" %d", bin[i]);
    }
    printf("\n");
}

void inicializaVetorZerado(int vetor[BITS]){ //zerando o vetor
    for (int i = 0; i < BITS; i++){            
        vetor[i] = 0;          
    }
}

int maiorBinario(int bin1[BITS], int bin2[BITS]){
    for(int i = 1; i < BITS; i++){ // percorre da esq para dir pulando o bit de sinal e compara 1 e 0
        if(bin1[i] > bin2[i]){ 
            return 1; // o primeiro binario veio 1 primeiro entao é maior 
        }
        else if(bin1[i] < bin2[i]){
            return 2; // o segundo binario veio 1 primeiro entao é maior
        }
    }
    return 0; //são iguais
}

void verificaZero(int num1, int num2, int numresult, char op, int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    if(op == '*'){
        numresult = num1 * num2;
        if(num1 == 0 || num2 ==0){
            printf("Um dos numeros eh 0, portanto o resultado eh 0.\n");
            printf("%d * %d = %d \n",num1,num2, numresult);
            imprimeBin(bin1);
            printf("%c\n",op);
            imprimeBin(bin2);
            printf("--------------------------------\n");
            imprimeBin(binresult);
        }
        else{
            printf("%d * %d = %d\n",num1,num2, numresult);
            multiplicacao(bin1,bin2,binresult);
        }
    }
    else if(op == '/'){
        int restodiv;
        if(num2 == 0){
            printf("Nao eh possivel dividir por 0");
        }
        else{
            numresult = num1 / num2;
            restodiv = num1 % num2;
            printf("%d / %d = %d \n",num1,num2, numresult);
            printf("Resto da divisao: %d\n",restodiv);
            //divisao(bin1,bin2,binresult);
        }
    }
}

void menuOpSub(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    int maior = maiorBinario(bin1, bin2);
    if(bin1[0] == 0 && bin2[0] == 0){ //x - y realiza uma subtracao normal               
        if(maior == 0){            // caso for igual (0) faz uma sub normal e coloca o sinal como 0
            sub(bin1,bin2,binresult);
            binresult[0] = 0;    
        }
        else if(maior == 2){      //caso bin2>bin1 trocamos os valores e fazemos uma sub normal, resultado fica negativo, sinal igual a 1
            binresult[0] = 1;
            sub(bin2,bin1,binresult);
        }
        else{
            sub(bin1,bin2,binresult); //bin1>bin2 só faz a sub normal
        }
    }
    else if(bin1[0] == 0 && bin2[0] == 1){ // x - (-y) tem q realizar uma soma  
        if(maior == 0){            
            soma(bin1,bin2,binresult);
            binresult[0] = 0;    
        }
        else if(maior == 2){      
            binresult[0] = 1;
            soma(bin2,bin1,binresult);
        }
        else{
            soma(bin1,bin2,binresult); 
        }
    }
    else if(bin1[0] == 1 && bin2[0] == 0){ // (-x) - y tem q realizar uma soma, mas o sinal é negativo = 1   
        binresult[0] = 1;
        soma(bin1,bin2,binresult);
    }
    else if(bin1[0] == 1 && bin2[0] == 1){ // (-x) - (-y) tem q realizar uma subtracao       
        if(maior == 0){             //sao iguais
            binresult[0] = 0;
            sub(bin1,bin2,binresult);
        }
        else if(maior == 2){    //bin2>bin1
            sub(bin2,bin1,binresult);
        }
        else{                  //bin1>bin2
            binresult[0] = 1;
            sub(bin1,bin2,binresult);
        }
    }
}

void menuOpSoma(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    if(bin1[0] == 0 && bin2[0] == 0){ //x + y realiza uma soma normal              
        soma(bin1,bin2,binresult);
    }
    else if(bin1[0] == 0 && bin2[0] == 1){ // x + (-y) tem q realizar uma subtração , cai no primeiro caso do menuOpSub x - y
        bin2[0] = 0;
        menuOpSub(bin1,bin2,binresult);
    }
    else if(bin1[0] == 1 && bin2[0] == 0){ // (-x) + y tem q realizar uma subtração , cai no ultimo caso do menuOpSub (-x) + y
        bin2[0] = 1;
        menuOpSub(bin1,bin2,binresult);
    }
    else if(bin1[0] == 1 && bin2[0] == 1){ // (-x) + (-y) tem q realizar uma soma, com sinal negativo = 1 
        binresult[0] = 1;
        soma(bin1,bin2,binresult);      
    }
}

void soma(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    int carry=0;

    imprimeBin(bin1);
    printf("+\n");
    imprimeBin(bin2);
                                                 //for até > 0 para n pegar o bit de sinal
    for(int i = BITS-1; i > 0; i--){             //operador XOR / 0 ^ 0 da 0 / 0 ^ 1 da 1 / 1 ^ 0 da 1 / 1 ^ 1 da 0 / Faz com os numeros dos binarios e dps com Carry
        binresult[i] = bin1[i]^bin2[i]^carry;
        carry = carry + bin1[i] + bin2[i];     //carry recebendo a soma , se for > 1 é pq teve q passar 1 
        if(carry > 1){
            carry = 1;
        }
        else{ 
            carry = 0;
        } 
    }
    printf("--------------------------------\n");
    imprimeBin(binresult);
    
}

/*int somaMult(int bin1[BITS], int bin2[BITS], int Carry){ // VER SE PRECISA
    for(int i = BITS-1; i > 0; i--){             //operador XOR / 0 ^ 0 da 0 / 0 ^ 1 da 1 / 1 ^ 0 da 1 / 1 ^ 1 da 0 / Faz com os numeros dos binarios e dps com Carry
            Carry = bin1[i]^bin2[i]^Carry;
            Carry = Carry + bin1[i] + bin2[i];     //carry recebendo a soma , se for > 1 é pq teve q passar 1 
            if(Carry > 1){
                Carry = 1;
            }
            else{ 
            Carry = 0;
            } 
        }
        return Carry;
}*/

void sub(int bin1[BITS], int bin2[BITS], int binresult[BITS]){

    int carry=0;
    
    imprimeBin(bin1);
    printf("-\n");  
    imprimeBin(bin2);
                                                //for até > 0 para n pegar o bit de sinal
    for(int i = BITS-1; i > 0; i--){             //operador XOR / 0 ^ 0 da 0 / 0 ^ 1 da 1 / 1 ^ 0 da 1 / 1 ^ 1 da 0 / Faz com os numeros dos binarios e dps com Carry
        binresult[i] = bin1[i]^bin2[i]^carry;
        carry = (bin1[i] - carry) - bin2[i];     //carry recebendo sub (tem q ser o bin1 - carry primeiro) , se for < 1 é pq teve q "emprestar" 1 
        if(carry < 0){
            carry = 1;
        }
        else{ 
            carry = 0;
        }
    }
    printf("--------------------------------\n");
    imprimeBin(binresult);
    
}

void multiplicacao(int binQ[BITS], int binM[BITS], int binresult[BITS]){ // É FEITA SEM REPRESENTAR O SINAL, ADICIONA NO FINAL SÓ
    int C = 0; //carry
    int sinalmult;
    int A[BITS];
    int AUX[BITS]; // para fazer a soma de A + M e depois passar o valor para A novamente
    inicializaVetorZerado(A);
    inicializaVetorZerado(AUX);

    imprimeBin(binQ);
    printf("*\n");
    imprimeBin(binM);
    printf("\n--------------------------------\n");
    printf("\nPasso a passo:\n");

    if(binQ[0] == 1 || binM[0] == 1){ //se algum dos dois sinais for 1, guardar o sinal para colocar no final
        sinalmult = 1;
    }
    else{
        sinalmult = 0;
    }

    for(int i = BITS-1; i > 0; i--){ // começando do 15 e indo até o 1, o 0 é o bit de sinal
        if(binQ[BITS-1] == 1){      // o bit mais a direita de Q é 1, então A = A + M
            printf("C = %d\n", C);  // imprime os vetores iniciais
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);
            
            printf("\n");

            printf("Bit mais a direita de Q: %d\n", binQ[BITS-1]); // Somando A + M
            printf("Entao, A = A + M\n");
            printf("A = \n");
            imprimeBin(A);
            printf("M = \n");
            imprimeBin(binM);
            printf("\n");

            soma(A,binM,AUX);
            transfereBin(AUX,A);
            
            printf("\nBinario A depois de somar com M : \n");
            imprimeBin(A);

            printf("\nC, A e Q serao deslocados um bit para a direita \n"); // Antes de todos deslocar para direita
            printf("C = %d\n", C);
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);

            printf("\nDeslocando C, A e Q um bit para a direita\n");   // Apos o deslocamento para a direita
            C = DeslocaParaDireita(A,C);
            C = DeslocaParaDireita(binQ,C);
            printf("C = %d\n", C);
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);      
        }
        else{
            printf("C = %d\n", C);               // imprime os vetores iniciais
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);

            printf("\n");

            printf("Bit mais a direita de Q: %d\n", binQ[BITS-1]);    
            printf("Entao, A = A, ou seja, nao eh alterado\n");
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);

            printf("\nC, A e Q serao deslocados um bit para a direita \n"); // Apos o deslocamento para a direita
            printf("C = %d\n", C);
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);

            printf("\nDeslocando C, A e Q um bit para a direita\n"); // Apos o deslocamento para a direita
            C = DeslocaParaDireita(A,C);
            C = DeslocaParaDireita(binQ,C);
            printf("C = %d\n", C);
            printf("A = \n");
            imprimeBin(A);
            printf("Q = \n");
            imprimeBin(binQ);
            printf("M = \n");
            imprimeBin(binM);
        }
    }
}

void transfereBin(int bin1[BITS], int bin2[BITS]){
    for(int i = 0; i < BITS; i++){
        bin2[i] = bin1[i];
    }
}

int DeslocaParaDireita(int bin[BITS], int C){
    int aux, i;
    if(bin[BITS - 1] == 1){
        aux = 1;
    }
    else{
        aux = 0;
    }
    for (i = BITS - 1; i > 0; i--){
    bin[i] = bin[i - 1];
    }
    bin[i] = C;
    
    return aux;
}