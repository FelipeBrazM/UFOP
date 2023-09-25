/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package genericos;

/**
 *
 * @author felip
 */
public class Conta implements Comparable <Conta> {
    private int num;
    private String nome;
    private double saldo;
    
    public Conta(){
    }
    
    public Conta(int num, String nome, double saldo){
        this.num = num;
        this.nome = nome;
        this.saldo = saldo;
    }

    public int getNum() {
        return num;
    }

    public void setNum(int num) {
        this.num = num;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public double getSaldo() {
        return saldo;
    }

    public void setSaldo(double saldo) {
        this.saldo = saldo;
    }
    
    @Override
    public int compareTo(Conta o){
        if(this.num < o.num)
            return -1;
        if(this.num > o.num)
            return 1;
        return 0;
    }
    
    @Override 
    public String toString(){
        return String.format("%d %s %f", num, nome,saldo);
    }
}



