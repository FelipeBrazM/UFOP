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
#include "menuChefe.h"
#include "menuFuncionario.h"

int main(){
    Cadastro * cadastroChefe = new Cadastro("admin", "admin");
    Chefe chefe = Chefe("Admin", cadastroChefe, 5000);

    Supervisor * supervisor = new Supervisor("Marcelo", new Cadastro("marcelo", "123"), 500);
    Vendedor * vendedor = new Vendedor("João", new Cadastro("joao", "123"), 500);
    chefe.cadastrarFuncionario(supervisor);
    chefe.cadastrarFuncionario(vendedor);
    supervisor->cadastrarVendedor(vendedor);

    Funcionario * funcionarioLogado = nullptr;

    int opcao; //opcao selecionada para o menu
    int tipoLogin; //1- Chefe    2- Funcionario

    do{
        telaInicial(opcao);

        switch(opcao){
            case 1:
                escolhaDeLogin(tipoLogin);
                if(telaLoginUsuario(tipoLogin, chefe, &funcionarioLogado)){
                    cout << "Login feito com sucesso!" << endl;
                    
                    if(tipoLogin == 1){
                        menuChefe(chefe);
                    }
                    else{
                        menuFuncionario(funcionarioLogado); //! Fazer dynamic_cast do funcionario dentro da funcao para ter vendedor ou supervisor 
                    }
                }
                else
                    cout << "Usuário de login e/ou senha incorreto(s)!" << endl;
            break;

            default:
                cout << "Saindo do sistema..." << endl;
        }
    }while(opcao != 2);

    return 0;
}

