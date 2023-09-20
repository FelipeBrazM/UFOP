/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package genericos;

/**
 *
 * @author felip
 */

    //Veiculo
public double precoAluguel(int dias){
    // Diaria * dias
    return this.getDiaria() * dias;
}

//Veiculo Passageiro
public double precoAluguel(int dias){
    // preçoBase+lugares ∗ preco_lugar_dia ∗ dias
    return super.precoAluguel(dias) + this.getLugares() * this.getPreco_lugar_dia() * dias;
}

//VeiculoCarga
public double precoAluguel(int dias){
    return super.precoAluguel(dias) + this.getPeso_max_carga() * this.getPreco_peso_max();
}

//Onibus
public double precoAluguel(int dias){
    return super.precoAluguel(dias) + this.getPreco_lugar()  * this.getLugares();
}

//Caminhao
public double precoAluguel(int dias){
    return super.precoAluguel(dias) + this.getPreco();
}



//Letra b
double valor_arrecadado_caminhoes(){
    
    double valorArrecadado = 0.0;
    Caminhao caminhaoTemp;

    for(Locacao locacao : this.getLocacoes()){

        if(locacao.getVeiculo() instanceof Caminhao){

            caminhaoTemp = (Caminhao) locacao.getVeiculo();
            int dias = this.calcDias();
            valorArrecadado += caminhaoTemp.precoAluguel(dias);
        
        }
    }

    return valorArrecadado;
}


public class Locadora{
    ArrayList <Cliente> clientes;
    ArrayList <Veiculo> alugado;
    ArrayList <Veiculo> disponivel;
    ArrayList <Locacao> locacoes;
    ArrayList <Locacao> locProc;

    public void processaLocacao(Cliente cliente){

        //Procurando qual a locacao do cliente
        Locacao loc;
        for(Locacao locTemp : locacoes){
            if(locTemp.getCliente().equals(cliente)){
                loc = locTemp;
                break;
            }
        }

        //Verificando a quantidade dos valores a pagar
        int dias = loc.calcDias();
        double valorPagar = loc.calcPago(dias);
        loc.setDiarias(valorPagar);

        //Movendo a locacao de locacoes para locProc
        Locacao locacaoRemovida = locacoes.remove(loc);
        this.locProc.add(locacaoRemovida);

        //Movendo o veiculo de alugado para disponivel
        Veiculo veiculoAlugado = locacaoRemovida.getVeiculo();
        Veiculo veiculoRemovido = this.alugado.remove(veiculoAlugado);
        this.disponivel.add(veiculoRemovido);

    }

}

