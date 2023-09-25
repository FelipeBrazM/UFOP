/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista7;

/**
 *
 * @author felip
 */
public class Conta {
    
    private double saldo;
    
    Conta(){}
    
    Conta(double saldo){
        if(saldo < 0){
            this.saldo = 0;
        }else{
            this.saldo = saldo;
        }
    }
    
    public void setSaldo(double saldo){
        this.saldo = saldo;
    }
    
    public double getSaldo(){
        return saldo;
    }
    
    public void Deposito(double valor){
        this.saldo = getSaldo() + valor;
    }
    
    public void Sacar(double valor){
        if(saldo < valor){
            System.out.println("O valor do saque e maior que o saldo em conta.");
        }else{
            this.saldo = getSaldo() - valor;
        }
    }
    
    @Override
    public String toString(){
        return ("O saldo atual e de: " + getSaldo());
    }
}
