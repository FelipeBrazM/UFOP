/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class Professor extends Funcionario {

    public Professor(int mat, double salario, String nome, String sobrenome) {
        super(mat, salario, nome, sobrenome);
    }
    
    @Override
    public double getSalarioPrimeiraParcela(double salario){
       return salario; 
    }
    
    @Override
    public double getSalarioSegundaParcela(double salario){
        return salario * 0;
    }
     
    public String toSTring(){
        return getNome() + getSobrenome() + getMat() + getSalario(); 
    }
}
