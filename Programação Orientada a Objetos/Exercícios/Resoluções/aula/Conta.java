package aula;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author felip
 */
public class Conta {
    private double saldo;
    private String nome;
    
    public Conta(){}
    
    public Conta(String nome, double saldo){
        this.nome = nome;
        setSaldo(saldo);
    }
    
    public void print(){
        System.out.println("Nome: " + getNome() + "\nSaldo: " + getSaldo());
    }
    
    public final void setSaldo(double saldo){
        this.saldo = saldo;
    } 
    
    public double getSaldo(){
        return saldo;
    }
    
    public final void setNome(String nome){
        this.nome = nome;
    }
    
    public String getNome(){
        return nome;
    }
    
    
    
    
    
}
