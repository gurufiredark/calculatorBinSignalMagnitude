#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BITS 16

int main(){
    int numDecimal1, numDecimal2, resultadoDecimal, binario1[BITS], binario2[BITS], binresult[BITS], maiorBin, i;
    char op;

    printf("Digite o primeiro numero: \n");
    scanf("%d", &numDecimal1);
    fflush(stdin);
    printf("Digite a operacao: (+, -, * ou / ) ou 's' para Sair do Programa\n");
    scanf("%c", &op);
    fflush(stdin);
    printf("Digite o segundo numero: \n");
    scanf("%d", &numDecimal2);


    converteParaBinario(numDecimal1, binario1);
    converteParaBinario(numDecimal2, binario2);

    for (i = 0; i < BITS; i++){            // para iniciar o vetor do resultado com todos valor 0 de inicio
        binresult[i] = 0;          
    }

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
            printf("Selecione uma operacao ou saia do programa");
            break;
    }

}

void menuOpSub(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    int maior = maiorBinario(bin1, bin2);
    if(bin1[0] == 0 && bin2[0] == 0){ //x - y realiza uma subtracao normal                 
        if(maior == 0){            // caso for igual (0) faz uma sub normal e coloca o sinal como 0
            sub(bin1,bin2,binresult);
            binresult[0] = 0;    
        }
        else if(maior == 2){      //caso bin2>bin1 trocamos os valores e fazemos uma sub normal e colocando o sinal como 1
            binresult[0] = 1;
            sub(bin2,bin1,binresult);
        }
        else{
            sub(bin1,bin2,binresult); //bin1>bin2 só faz a sub normal
        }
    }
    else if(bin1[0] == 0 && bin2[0] == 1){ // x - (-y) tem q realizar uma soma, se o bin2 for maior tem que vir primeiro e manter o sinal negativo
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
            binresult[0] = 1;
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
    else if(bin1[0] == 0 && bin2[0] == 1){ // x + (-y) tem q realizar uma subtração
        menuOpSub(bin1,bin2,binresult);
    }
    else if(bin1[0] == 1 && bin2[0] == 0){ // (-x) + y tem q realizar uma subtração
        menuOpSub(bin1,bin2,binresult);
    }
    else if(bin1[0] == 1 && bin2[0] == 1){ // (-x) + (-y) tem q realizar uma soma       
        soma(bin1,bin2,binresult);
        binresult[0] = 1;                   
    }
}

void soma(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    int carry=0;

    imprimeBin(bin1);
    printf("+\n");
    imprimeBin(bin2);

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

void sub(int bin1[BITS], int bin2[BITS], int binresult[BITS]){

    int carry=0;
    
    imprimeBin(bin1);
    printf("-\n");  
    imprimeBin(bin2);
    
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

void multiplicacao(int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    

    
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

void converteParaBinario(int numdec, int vet_binario[BITS]){

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

void verificaZero(int num1, int num2, int numresult, char op, int bin1[BITS], int bin2[BITS], int binresult[BITS]){
    if(op == '*'){
        numresult = num1 * num2;
        if(num1 == 0 || num2 ==0){
            printf("Um dos numeros eh 0, portanto o resultado eh 0.\n");
            printf("%d * %d = %d \n",num1,num2, numresult);
            imprimeBin(bin1);
            imprimeBin(bin2);
            printf("--------------------------------\n");
            imprimeBin(binresult);
        }
        else{
            printf("%d * %d = %d",num1,num2, numresult);
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

void imprimeBin(int bin[BITS]){
    for (int i = 0; i < BITS; i++){
        printf(" %d", bin[i]);
    }
    printf("\n");
}