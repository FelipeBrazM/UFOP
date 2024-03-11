/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "menus.h"

void selecaoMenu(int &opcao, int min, int max){
    opcao = -1;
    do{
        try{
            //Verificando se a entrada eh um numero
            if(!(cin >> opcao)){
                throw invalid_argument("A opção precisa ser um número entre ["+ to_string(min) +" e "+ to_string(max) +"].\n ");
            }
            if(opcao < min || opcao > max){
                throw invalid_argument("A opção precisa ser um número entre ["+ to_string(min) +" e "+ to_string(max) +"].\n ");
            }

        }
        catch(invalid_argument &e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opção: ";
        }
    }while (opcao < min || opcao > max);

    cout << "\n";
}

void telaInicial(int &opcao){
    cout << "TELA INICIAL\n";
    cout << "\t1- Login\n";
    cout << "\t2- Sair do sistema\n";
    cout << "Opção: ";
    selecaoMenu(opcao, 1, 2);
}

bool validacaoLoginFuncionario(Cadastro cadastroLogin, vector<Funcionario*> funcionarios, Funcionario** ptrFunc){

    for (Funcionario * funcionario : funcionarios){
        //Comparando o login e senha passado com o que o cadastro de pessoa possui
        Cadastro * temp = funcionario->getCadastro();
        if(*temp == cadastroLogin){
            *ptrFunc = funcionario;

            return true;
        }
    }
    
    return false;
}

bool validacaoLoginChefe(Cadastro cadastroLogin, const Chefe& chefe){
    Cadastro * temp = chefe.getCadastro();

    return *temp == cadastroLogin;
}

bool telaLoginUsuario(const int &tipoLogin, const Chefe& chefe, Funcionario** funcionario){
    string login, password;
    
    cout << "Usuario: ";
    cin >> login;
    cout << "Senha: "; 
    cin >> password;

    Cadastro cadastroLogin = Cadastro(login, password);

    bool verificacao;

    switch(tipoLogin){
        case 1: //chefe
            verificacao = validacaoLoginChefe(cadastroLogin, chefe);
        break;

        default: //funcionario
            verificacao = validacaoLoginFuncionario(cadastroLogin, chefe.getFuncionarios(), funcionario);
    }

    cout << "\n";
    return verificacao;
}

void escolhaDeLogin(int &tipoLogin){
    cout << "Selecione seu Login:\n";
    cout << "\t1- Chefe\n";
    cout << "\t2- Funcionario\n";
    cout << "Opção: ";
    selecaoMenu(tipoLogin, 1, 2);
}
