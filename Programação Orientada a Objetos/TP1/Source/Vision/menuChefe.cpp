/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "menuChefe.h"

void cadastrarSupervisor(Chefe& chefe){
    string nome, login, senha;
    double salarioHora;

    cout << "Nome: ";
    cin >> nome;
    cout << "Login: ";
    cin >> login;
    cout << "Senha: ";
    cin >> senha;
    
    cout << "Salário Hora: ";
    while(!(cin >> salarioHora)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Salário Hora precisa ser um valor numérico.\nSalário Hora: ";
    }


    Cadastro * cadTemp = new Cadastro(login, senha);
    Supervisor * tempSuper = new Supervisor(nome, cadTemp, salarioHora);

    chefe.cadastrarFuncionario(tempSuper);

}

//Seleciona o supervisor que o vendedor sera adicionado
Supervisor * selecionarSupervisor(Chefe &chefe){
    
    cout << "\nListando todos os supervisores disponíveis.\n";

    vector<Supervisor *> supervisores;
    Supervisor * supervisorTemp;

    //Gerando o vetor de supervisores e exibindo seus valores
    for(auto funcionario : chefe.getFuncionarios()){ 

        if(typeid(*funcionario) == typeid(Supervisor)){

            supervisorTemp = dynamic_cast<Supervisor*>(funcionario);
            supervisores.push_back(supervisorTemp);

            cout << "Id: " << supervisorTemp->getId() << " - Nome: " << supervisorTemp->getNome() << endl;
        }
    }
    cout << "\n";

    //Selecionado o supervisor
    int opcaoId;

    while(true){
        cout << "Coloque o Id do supervisor responsável por este vendedor: ";
        while(!(cin >> opcaoId)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "O Id precisa ser um valor numérico.\n";
            cout << "Coloque o Id do supervisor responsável por este vendedor: ";
        }
        
        //Verificando se o ID do supervisor existe
        for (auto *supervisor : supervisores)
            if(opcaoId == supervisor->getId())
                return supervisor;
        
        cout << "Id de supervisor inválido.\n";
    }
}

void cadastrarVendedor(Chefe& chefe){

    if(chefe.getQtdFuncionarios()== 0){
        cout << "Não é possível cadastrar um vendedor, pois não há nenhum supervisor cadastrado.\n";
        return;
    }

    //Criando o vendedor
    string nome, login, senha;
    double salarioHora;

    cout << "Nome: ";
    cin >> nome;
    cout << "Login: ";
    cin >> login;
    cout << "Senha: ";
    cin >> senha;

    cout << "Salário Hora: ";
    while(!(cin >> salarioHora)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Salário Hora precisa ser um valor numérico.\nSalário Hora: ";
    }

    
    //Adicionando as informacoes do vendedor e colocando de inicio seu salario total com valor 0
    Vendedor *novoVendedor = new Vendedor(nome, new Cadastro(login, senha), salarioHora);

    //Adicionando o vendedor no vetor de funcionarios do chefe
    chefe.cadastrarFuncionario(novoVendedor);

    //Gerando uma lista com todos os supervisores disponíveis
    Supervisor * supervisorTemp = selecionarSupervisor(chefe);
    supervisorTemp->cadastrarVendedor(novoVendedor);

    cout << "\n";

}

void cadastrarFuncionario(Chefe& chefe){

    int opcao = -1;
    
    do{
        cout << "1 - Cadastrar Supervisor \n" 
        << "2 - Cadastrar Vendedor \n" 
        << "3 - Voltar\n"
        << "Opção: ";
        selecaoMenu(opcao, 1, 3);

        switch(opcao){
            case 1:
                cadastrarSupervisor(chefe);
                break;
        
            case 2:
                cadastrarVendedor(chefe);
                break;
                
            default:
                break;     
        }

    }while(opcao != 3);
}

bool compare(Funcionario *f1, Funcionario *f2){
    return f1->getMinutosPendentes() > f2->getMinutosPendentes();
}

void checarPontoFuncionarios(Chefe &chefe){
    
    vector<Funcionario*> funcTemp;
    funcTemp = chefe.getFuncionarios();

    //Ordenando o vetor para mostrar os funcionarios com mais minutos pendentes
    sort(funcTemp.begin(), funcTemp.end(), compare);
    
    for(auto func : funcTemp){
        cout << func->getNome() << "\n";
        
        int minutosPendentes = func->getMinutosPendentes();

        if(minutosPendentes < 0){
            //horas extras
            int horasExtras = abs(minutosPendentes)/60;
            int minutosExtras = abs(minutosPendentes) - (horasExtras * 60);

            cout << CARGA_HORARIA_MENSAL <<" horas trabalhadas + " << horasExtras << "h e " << minutosExtras << "min extras" << endl;
        }
        else if(minutosPendentes == 0)
            //0 horas extras e 0 horas pendentes
            cout << CARGA_HORARIA_MENSAL <<" horas trabalhadas + 0 horas pendentes e 0 horas extras" << endl;
            
        else {
            //horas pendentes
            int minutosTrabalhados = CARGA_HORARIA_MENSAL - minutosPendentes;
            int horasTrabalhadas = minutosTrabalhados / 60;
            minutosTrabalhados -= horasTrabalhadas*60;
            
            int horasPendentes = minutosPendentes/60;
            minutosPendentes -= (horasPendentes * 60);
            
            cout << horasTrabalhadas << "h e " << minutosTrabalhados << "min trabalhados + " << horasPendentes << "h e " << minutosPendentes << "min pendentes" << endl;
        }

        cout << "====================\n";
    }
}

void salariosFuncionarios(Chefe &chefe){
    vector<Funcionario*> funcTemp = chefe.getFuncionarios();

    for(auto func : funcTemp){
        cout << "====================\n";
        cout << "Nome: " << func->getNome() << endl;

        cout << "\nSalário Final: R$" << func->calcularSalarioFinal() << endl;
        cout << "Bonificações: R$" << func->calcularBonificacao() << endl;
    }

    cout << "====================\n";
}

//Fazer o cadastro do funcionario e listar funcionarios
void menuChefe(Chefe& chefe){
    cout << "Olá, chefe " << chefe.getNome() << endl;
    int opcao;
    do{
        cout << "1 - Cadastrar Funcionários \n" 
             << "2 - Listar Funcionarios \n" 
             << "3 - Checar Ponto dos Funcionarios \n"
             << "4 - Cálculo de salarios e bonificações \n" 
             << "5 - Retornar a tela inicial\n"
             << "Opção: ";
        
        selecaoMenu(opcao, 1, 5);

        switch(opcao){
            case 1:
                cadastrarFuncionario(chefe);
                break;
                
            case 2:
                chefe.listarFuncionarios();
                break;
            
            case 3:
                checarPontoFuncionarios(chefe);
                break;

            case 4:
                salariosFuncionarios(chefe);
                break;
            
            default:
                cout << "Deslogando..." << endl;
                break;
        }
        
    }while(opcao != 5);
}