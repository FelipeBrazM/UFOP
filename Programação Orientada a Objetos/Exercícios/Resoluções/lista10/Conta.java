/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista10;

/**
 *
 * @author felip
 */
public class Conta {
    private double saldo;

    public Conta() {
    }

    public Conta(double saldo) {
        this.saldo = saldo;
    }
    
    public void Credito(double deposito){
        if(deposito < 0){
            System.out.println("Nao e possivel deposito negativo!");
        }else{
            this.saldo = deposito;
        }
    }
    
    public void Debito(double saldo, double debito){
        if(saldo < debito){
            System.out.println("Nao e possivel debitar!");
        }else{
            
        }
    }
    
    public void setSaldo(double saldo){
        if(saldo < 0){
            System.out.println("Esse valor nao e possivel!");
            System.exit(0);
        }else{
            this.saldo = saldo;
        }
    }
    
    public double getSaldo(){
        return saldo;
    }
}
