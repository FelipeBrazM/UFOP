/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class SuperHeroi extends Inseto {
    protected String codinome;
    protected String traumas;
    protected String poderes;

    public SuperHeroi() {
    }
    
    public SuperHeroi(String codinome, String traumas, String poderes, boolean venenoso, boolean alado, boolean ferrao, String nome, String sexo, int idade, String lingua, String etnia) {
        super(venenoso, alado, ferrao, nome, sexo, idade, lingua, etnia);
        this.codinome = codinome;
        this.traumas = traumas;
        this.poderes = poderes;
    }
    
    @Override 
    public String toString(){
        return super.toString() + "Codinome: " + codinome + "\n" + "Traumas: " + traumas + "\n" + "Poderes: " + poderes;   
    }
}
