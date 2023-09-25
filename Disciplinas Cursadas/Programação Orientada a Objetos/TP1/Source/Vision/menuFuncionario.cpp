/*
    Alunos:
    - Felipe Braz Marques
    - Lucas Chagas Mendes
    - Matheus Peixoto Ribeiro Vieira
    - Nicolas Expedito Lana Mendes
    - Pedro Henrique Rabelo Leão de Oliveira
    - Pedro Morais Fernandes
*/
#include "menuFuncionario.h"

void menuFuncionario(Funcionario* funcionario){
    if(typeid(*funcionario) == typeid(class Vendedor)){
        Vendedor* vendedor = dynamic_cast<Vendedor*>(funcionario);
        opcoesVendedor(vendedor);
    }
    else { // typeid(*funcionario) == typeid(class Supervisor)
        Supervisor* supervisor = dynamic_cast<Supervisor*>(funcionario);
        opcoesSupervisor(supervisor);
    }
}

void opcoesSupervisor(Supervisor* supervisor){

    cout << "Olá, supervisor " << supervisor->getNome() << endl;

    int opcao;
    
    do{
        cout << "1 - Cadastrar Ponto \n"
            << "2 - Exibir Salário \n"
            << "3 - Listar Vendas \n"
            << "4 - Retornar a tela inicial\n"
            << "Opção: ";
            
        selecaoMenu(opcao, 1, 5); 

        Ponto* pontoUnico = new Ponto();

        switch(opcao){
            case 1:
                cadastrarPonto(pontoUnico);
                supervisor->registrarPonto(pontoUnico);
            break;

            case 2: 
                cout << "Salário Final: R$" << supervisor->calcularSalarioFinal() << endl;
                cout << "Bonificações: R$" << supervisor->calcularBonificacao() << endl;
            break;

            case 3:
                supervisor->listarVendas();
            break;
        
            default:
                cout << "Deslogando..." << endl;
            break;
        }
           
    }while(opcao != 4);

}

void opcoesVendedor(Vendedor *vendedor){

    int opcao;

    cout << "Olá, vendedor " << vendedor->getNome() << endl;

    do{
        cout << "1 - Cadastrar Ponto \n"
             << "2 - Exibir Salário \n"
             << "3 - Cadastrar Venda \n"
             << "4 - Listar Vendas \n"
             << "5 - Retornar a tela inicial\n"
             << "Opção: ";

        selecaoMenu(opcao, 1, 6);

        Ponto* pontoUnico =  new Ponto();
        Venda* vendaUnica =  new Venda();

        switch (opcao){
            case 1:
                cadastrarPonto(pontoUnico);
                vendedor->registrarPonto(pontoUnico);
            break;

            case 2:
                cout << "Salário Final: R$" << vendedor->calcularSalarioFinal() << endl;
                cout << "Bonificações: R$" << vendedor->calcularBonificacao() << endl;
            break;

            case 3:
                cadastrarVendaUnica(vendaUnica);
                vendedor->cadastrarVenda(vendaUnica);
            break;

            case 4:
                vendedor->listarVendas();
            break;
        
            default:
                cout << "Deslogando..." << endl;
            break;
        }

    }while(opcao != 5);


}

bool validaData(string & data){
    regex pattern(R"(\b(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(\d{4})\b)");
    return regex_match(data, pattern);
}

void lerHora(Hora * horario){
    int hora;

    cout << "Informe a hora (formato a ser digitado: HH): ";
    
    do{
        try{
            //Verificando se a entrada eh um numero
            if(!(cin >> hora))
                throw invalid_argument("A hora precisa ser um valor numérico.\n ");
            
            if(hora < 0 || hora > 23)
                throw invalid_argument("As horas precisam estar entre 0 e 23\n ");
            
            horario->setHora(hora);
        }
        catch(invalid_argument &e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Informe a hora (formato a ser digitado: HH):";
        }
    }while (hora < 0 || hora > 23);
}

void lerMinuto(Hora * horario){
    int minuto;

    cout << "Informe o minuto(formato a ser digitado: MM): ";
    
    do{
        try{
            //Verificando se a entrada eh um numero
            if(!(cin >> minuto))
                throw invalid_argument("O minuto precisa ser um valor numérico.\n ");
            
            if(minuto < 0 || minuto > 59)
                throw invalid_argument("Os minutos precisam estar entre 0 e 59\n ");
            
            horario->setMinuto(minuto);
        }
        catch(invalid_argument &e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Informe o minuto(formato a ser digitado: MM):";
        }
    }while (minuto < 0 || minuto > 59);
}

void cadastrarPonto(Ponto* ponto){
    string data;
    
    //Data
    do{
        cout<< "Informe a data atual (formato DD/MM/YYYY): ";
        cin>>data;
    }while(!validaData(data));
    cout << "\n";

    //Horário de entrada
    cout << "Informe o horario de entrada.\n";
    Hora *horarioE = new Hora();
    lerHora(horarioE);
    lerMinuto(horarioE);
    cout << "\n";

    //Horário de saída
    cout << "Informe o horario de saída.\n";
    Hora *horarioS = new Hora();
    lerHora(horarioS);
    lerMinuto(horarioS);
    cout << "\n";
    
    //Criação do ponto
    ponto->setHorarioEntrada(horarioE);
    ponto->setHorarioSaida(horarioS);
    ponto->setData(data);
    cout << "\n";

}

void cadastrarVendaUnica(Venda* venda){
    double valor = -1.0;
    int quantidade = -1;

    //Quantidade
    do{
        cout << "Informe a quantidade de itens da venda: ";
        cin >> quantidade;
        try{
            venda->setQuantidade(quantidade);
        }
        catch(invalid_argument &e){
            cout<<"Erro: "<<e.what();
        }
    }while(quantidade < 0);

    cout << "\n";

    //Valor
    do{
        cout << "Informe o valor individual do item: ";
        cin >> valor;
        try{
            venda->setValor(valor);
        }
        catch(invalid_argument &e){
            cout<<"Erro: "<<e.what();
        }
    }while(valor < 0);

    cout << "\n";
}