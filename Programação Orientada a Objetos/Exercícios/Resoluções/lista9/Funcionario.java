/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class Funcionario extends Pessoa {
    private int mat;
    private double salario;

    public Funcionario(){
        
    }

    public Funcionario(int mat, double salario, String nome, String sobrenome) {
        super(nome, sobrenome);
        this.mat = mat;
        setSalario(salario);
    }

    public void setMat(int mat) {
        this.mat = mat;
    }

    public final void setSalario(double salario) {
        if(salario > 0) this.salario = salario;
        else{
            System.out.println("Salario negativo nao e possivel");
            System.exit(0);
        }
    }

    public int getMat() {
        return mat;
    }

    public double getSalario() {
        return salario;
    }
    
    public double getSalarioPrimeiraParcela(double salario){
        return salario * 0.6;
    }
    
    public double getSalarioSegundaParcela(double salario){
        return salario * 0.4;
    }
    
}
