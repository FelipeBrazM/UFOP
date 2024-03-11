#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução
            
    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt
    
    // 22 => significa um endereço da RAM (10 endereço) 
    // 13 => significa 2o endereço
    // 45 => significa 3o endereco
    //ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM

    Instruction* instructions = (Instruction*) malloc(10 * sizeof(Instruction));

    for (int i=0; i<9; i++){
        instructions[i].opcode = rand() % 4; //0, 1, 2, 3
        instructions[i].info1 = rand() % ramSize; //0 ... RAM_SIZE
        do {
            instructions[i].info2 = rand() % ramSize; //0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; //0 ... RAM_SIZE
    }
    
    //inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode =-1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;
    
    return instructions;
}

Instruction* generateMultiplicationInstructions(int n1, int n2, int execHalt, int salvarValorNaRam){
    //Vetor de instrucoes contendo as duas instrucoes de levar informacao na RAM e o comando de finalizacao mais a quantidade de vezes que o n1 sera multiplicado, ou seja, o n2
    int qtdInstrucoesExtras = execHalt ? 3 : (salvarValorNaRam == 1 ? 2 : 0);
    
    printf("Tamanho Vetor: %d\n\n", qtdInstrucoesExtras + n2);
    Instruction* instrucoes = (Instruction*) malloc((qtdInstrucoesExtras + n2) * sizeof(Instruction));

    if(salvarValorNaRam == 1){
        //Levando o n1 para a RAM e colocando no endereco 0
        instrucoes[0].opcode = 0;
        instrucoes[0].info1 = n1;//Valor para ser salvo na RAM
        instrucoes[0].info2 = 0;//Posicao na RAM      

        //Levando o valor 0 (termo neutro da soma) para a RAM na posicao 1
        instrucoes[1].opcode = 0;
        instrucoes[1].info1 = 0;//Valor para ser salvo na RAM
        instrucoes[1].info2 = 1;//Posicao na RAM  
    }


    int instrucaoInicial = salvarValorNaRam == 1 ? 2 : 0;

    for(int i = instrucaoInicial; i < n2+instrucaoInicial; i++){
        instrucoes[i].opcode = 1; //Operacao de soma
        instrucoes[i].info1 = 0; //Posicao do n1
        instrucoes[i].info2 = 1; //Posicao do n2
        instrucoes[i].info3 = 1; //Onde irá salvar a soma
    }

    if(execHalt){
        instrucoes[2+n2].opcode = -1;
        instrucoes[2+n2].info1 = -1;
        instrucoes[2+n2].info2 = -1;
        instrucoes[2+n2].info3 = -1;
    }

    return instrucoes;

}

Instruction* generateExponentiationInstructions(int base, int expoente){

    int qtdInstrucoes = 0;
    for(int i=0; i<expoente-1; i++){
        qtdInstrucoes += (base+3);//Colocar 0 na P0, somar P0 + P1 e colocar 0 na P1
    }
    qtdInstrucoes+= 3;//Executar o halt e levar os valores iniciais para a RAM

    Instruction* instrucoes = malloc(qtdInstrucoes * sizeof(Instruction));

    //Levando a base para a RAM
    instrucoes[0].opcode = 0;
    instrucoes[0].info1 = expoente != 0 ? base : 1;//Valor para ser salvo na RAM
    instrucoes[0].info2 = 0;//Posicao na RAM      

    //Levando o valor 0 (termo neutro da soma) para a RAM na posicao 1
    instrucoes[1].opcode = 0;
    instrucoes[1].info1 = 0;//Valor para ser salvo na RAM
    instrucoes[1].info2 = 1;//Posicao na RAM  

    Instruction* instrucoesTemp;

    for(int i=2; i<qtdInstrucoes-1;){

        instrucoesTemp =  generateMultiplicationInstructions(base, base, 0, 0);

        int j;
        for(j=0; j<base; j++){
            instrucoes[i+j] = instrucoesTemp[j];
        }
        i+=j;

        free(instrucoesTemp);

        //Trocando o valor que está no P1 (resultado da multiplicacao) para o P0 para continuar fazendo as multiplicacoes com os valores corretos. Ex: 2⁴ estava fazendo 8+2+2, e nao 8+0+8

        //Levando 0 para p0
        instrucoes[i].opcode = 0;
        instrucoes[i].info1 = 0;//Valor para ser salvo na RAM
        instrucoes[i].info2 = 0;//Posicao na RAM 

        //Levando o valor de p1 para p0
        instrucoes[i+1].opcode = 1; //Operacao de soma
        instrucoes[i+1].info1 = 0; //Posicao do n1
        instrucoes[i+1].info2 = 1; //Posicao do n2
        instrucoes[i+1].info3 = 0; //Onde irá salvar a soma

        //Levando 0 para p1
        instrucoes[i+2].opcode = 0;
        instrucoes[i+2].info1 = 0;//Valor para ser salvo na RAM
        instrucoes[i+2].info2 = 1;//Posicao na RAM 

        i+=3;

    }

    instrucoes[qtdInstrucoes-1].opcode = -1;
    instrucoes[qtdInstrucoes-1].info1 = -1;
    instrucoes[qtdInstrucoes-1].info2 = -1;
    instrucoes[qtdInstrucoes-1].info3 = -1;

    return instrucoes;

} 

Instruction* generateDivisionInstructions(int dividendo, int divisor){
    //n1 = Dividendo
    //n2 = DIvisor

    int qtdInstrucoes = 4;

    Instruction* instrucoes = malloc(qtdInstrucoes * sizeof(Instruction));

    //Levando o n1 para a RAM e colocando no endereco 0
    instrucoes[0].opcode = 0;
    instrucoes[0].info1 = dividendo;//Valor para ser salvo na RAM
    instrucoes[0].info2 = 0;//Posicao na RAM      

    //Levando n2 para a RAM e colocando no endereco 1
    instrucoes[1].opcode = 0;
    instrucoes[1].info1 = divisor;//Valor para ser salvo na RAM
    instrucoes[1].info2 = 1;//Posicao na RAM  

    //Levando o valor 0 para a posicao 2 da RAM para ser o quociente
    instrucoes[2].opcode = 0;
    instrucoes[2].info1 = 0;//Valor para ser salvo na RAM
    instrucoes[2].info2 = 2;//Posicao na RAM 

    //Levando o valor 1 para a posicao 3 da RAM para somar mais um ao quociente
    instrucoes[3].opcode = 0;
    instrucoes[3].info1 = 1;//Valor para ser salvo na RAM
    instrucoes[3].info2 = 3;//Posicao na RAM 

    int i;
    for(i=divisor; i <= dividendo; i+=divisor){
        
        qtdInstrucoes+=2;

        instrucoes = realloc(instrucoes, qtdInstrucoes*sizeof(Instruction));

        //Subtraindo n2 de n1
        instrucoes[qtdInstrucoes- 2].opcode = 2; //Operacao de subtracao
        instrucoes[qtdInstrucoes- 2].info1 = 0; //Posicao do n1
        instrucoes[qtdInstrucoes- 2].info2 = 1; //Posicao do n2
        instrucoes[qtdInstrucoes- 2].info3 = 0; //Onde ira salvar a subtracao

        //Somando a quantidade de subtracoes feitas
        instrucoes[qtdInstrucoes - 1].opcode = 1; //Operacao de soma
        instrucoes[qtdInstrucoes - 1].info1 = 2; //Posicao do n1
        instrucoes[qtdInstrucoes - 1].info2 = 3; //Posicao do n2
        instrucoes[qtdInstrucoes - 1].info3 = 2; //Onde ira salvar a soma

    }

    //Resto sera a posicao 0
    //O resultado sera a posicao 2

    instrucoes = realloc(instrucoes, (qtdInstrucoes+1) * sizeof(Instruction));

    instrucoes[qtdInstrucoes].opcode = -1;
    instrucoes[qtdInstrucoes].info1 = -1;
    instrucoes[qtdInstrucoes].info2 = -1;
    instrucoes[qtdInstrucoes].info3 = -1;

    return instrucoes;
}

Instruction* generateFactorialInstructions(int n1){

    int qtdInstrucoes = 4;
    Instruction* instrucoes = malloc(qtdInstrucoes * sizeof(Instruction));

    //Levando o n1 para a RAM e colocando no endereco 0
    instrucoes[0].opcode = 0;
    instrucoes[0].info1 = n1;//Valor para ser salvo na RAM
    instrucoes[0].info2 = 0;//Posicao na RAM      

    //Levando 0 para a RAM e colocando no endereco 1
    instrucoes[1].opcode = 0;
    instrucoes[1].info1 = 0;//Valor para ser salvo na RAM
    instrucoes[1].info2 = 1;//Posicao na RAM  

    //Parte do código apenas para mostrar o número que está sendo multiplicado do fatorial:
    //Levando o n1 para a RAM e colocando no endereco 2
    instrucoes[2].opcode = 0;
    instrucoes[2].info1 = n1-1;//Valor para ser salvo na RAM
    instrucoes[2].info2 = 2;//Posicao na RAM     

    //Levando o 1 para a RAM e colocando no endereco 3 para ser o subtraendo
    instrucoes[3].opcode = 0;
    instrucoes[3].info1 = 1;//Valor para ser salvo na RAM
    instrucoes[3].info2 = 3;//Posicao na RAM    

    Instruction* instrucoesTemp;

    for (int i = n1-1; i > 1; i--){
        qtdInstrucoes += i+4;
        instrucoes = realloc(instrucoes, qtdInstrucoes * sizeof(Instruction));

        instrucoesTemp = generateMultiplicationInstructions(i, i, 0, 0);
        
        for (int j = i; j > 0; j--){
            instrucoes[qtdInstrucoes - j - 4] = instrucoesTemp[i-j];
        }

        free(instrucoesTemp);
        
        //Trocando o valor que está no P1 (resultado da multiplicacao) para o P0 para continuar fazendo as multiplicacoes com os valores corretos

        //Levando 0 para p0
        instrucoes[qtdInstrucoes-4].opcode = 0;
        instrucoes[qtdInstrucoes-4].info1 = 0;//Valor para ser salvo na RAM
        instrucoes[qtdInstrucoes-4].info2 = 0;//Posicao na RAM 

        //Levando o valor de p1 para p0
        instrucoes[qtdInstrucoes-3].opcode = 1; //Operacao de soma
        instrucoes[qtdInstrucoes-3].info1 = 0; //Posicao do n1
        instrucoes[qtdInstrucoes-3].info2 = 1; //Posicao do n2
        instrucoes[qtdInstrucoes-3].info3 = 0; //Onde irá salvar a soma

        //Levando 0 para p1
        instrucoes[qtdInstrucoes-2].opcode = 0;
        instrucoes[qtdInstrucoes-2].info1 = 0;//Valor para ser salvo na RAM
        instrucoes[qtdInstrucoes-2].info2 = 1;//Posicao na RAM 


        //Subtraindo 1 (posicao 3) da posicao 2
        instrucoes[qtdInstrucoes-1].opcode = 2; //Operacao de subtracao
        instrucoes[qtdInstrucoes-1].info1 = 2; //Posicao do n1
        instrucoes[qtdInstrucoes-1].info2 = 3; //Posicao do n2
        instrucoes[qtdInstrucoes-1].info3 = 2; //Onde irá salvar a soma
    }

    //o resultado do fatorial fica armazenado na posicao 0
    //os números do fatorial que estao sendo multiplicados ficam na posicao 2, mas o primeiro de todos começa na posicao 0
    //ex: 4!: comeca com 4 na posicao 0, e 3 na posicao 2. A partir dai, na posicao 2 ficara salvo os outros numeros do fatorial

    instrucoes = realloc(instrucoes, (qtdInstrucoes+1) * sizeof(Instruction));

    instrucoes[qtdInstrucoes].opcode = -1;
    instrucoes[qtdInstrucoes].info1 = -1;
    instrucoes[qtdInstrucoes].info2 = -1;
    instrucoes[qtdInstrucoes].info3 = -1;

    return instrucoes;
}

Instruction* generateAritmeticProgressionInstructions(int a1, int n, int razao){

    //an = (n-1)*razao + a1

    Instruction* instrucoes = malloc((7 + razao) * sizeof(Instruction)); //Num de instrucoes padrao mais a multiplicacao

    //Levando n e 1 para a RAM
    instrucoes[0].opcode = 0;
    instrucoes[0].info1 = n; //Valor
    instrucoes[0].info2 = 0; //Posicao

    instrucoes[1].opcode = 0;
    instrucoes[1].info1 = 1; //Valor
    instrucoes[1].info2 = 1; //Posicao

    //Subtraindo 1 de n
    instrucoes[2].opcode = 2;
    instrucoes[2].info1 = 0; //Posicao do valor 1
    instrucoes[2].info2 = 1; //Posicao do valor 2
    instrucoes[2].info3 = 0; //Posicao onde sera salvo o resultado

    //Levando o 0 para a posicao 1, pois e o termo neutro da soma, que e a base da multiplicacao
    instrucoes[3].opcode = 0;
    instrucoes[3].info1 = 0; //Valor
    instrucoes[3].info2 = 1; //Posicao

    Instruction* temp = generateMultiplicationInstructions(0, razao, 0, 0);

    //Adicionando no vetor de instrucoes as geradas pela multiplicacao
    int proximaInstrucao = 4;
    for(int i = 0; i < razao; i++){
        instrucoes[proximaInstrucao + i] = temp[i];
    }

    free(temp);

    proximaInstrucao += razao;

    //Multiplicacao deixa o resultado na posicao 1

    //Levando a1 para a posicao 0 da RAM
    instrucoes[proximaInstrucao].opcode = 0;
    instrucoes[proximaInstrucao].info1 = a1; //Valor
    instrucoes[proximaInstrucao].info2 = 0;  //Posicao

    proximaInstrucao++;

    //Fazendo a soma de a1 com o termo anterior
    instrucoes[proximaInstrucao].opcode = 1;
    instrucoes[proximaInstrucao].info1 = 0; //Posicao do valor 1
    instrucoes[proximaInstrucao].info2 = 1; //Posicao do valor 2
    instrucoes[proximaInstrucao].info3 = 0; // Posicao onde sera salvo o resultado

    proximaInstrucao++;

    //Halt
    instrucoes[proximaInstrucao].opcode = -1;
    instrucoes[proximaInstrucao].info1 = -1;
    instrucoes[proximaInstrucao].info2 = -1;
    instrucoes[proximaInstrucao].info3 = -1;

    //Resultado final fica na posicao 0
    return instrucoes;

}

Instruction* readInstructions(char* fileName, int* ramSize) {
    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction* instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}