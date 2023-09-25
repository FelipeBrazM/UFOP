/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class Inseto extends Humano{
    protected boolean venenoso, alado, ferrao;

    public Inseto() {
    }
    
    public Inseto(boolean venenoso, boolean alado, boolean ferrao, String nome, String sexo, int idade, String lingua, String etnia) {
        super(nome, sexo, idade, lingua, etnia);
        this.venenoso = venenoso;
        this.alado = alado;
        this.ferrao = ferrao;
    }

    public boolean isVenenoso() {
        return venenoso;
    }

    public boolean isAlado() {
        return alado;
    }

    public boolean isFerrao() {
        return ferrao;
    }

    public void setVenenoso(boolean venenoso) {
        this.venenoso = venenoso;
    }

    public void setAlado(boolean alado) {
        this.alado = alado;
    }

    public void setFerrao(boolean ferrao) {
        this.ferrao = ferrao;
    }
    
    @Override 
    public String toString(){
        return "Nome: " + nome + "\n" +"Sexo: " + sexo + "\n" + "Idade: " + idade + "\n" + "Lingua: " + lingua + "\n" +
                "Etnia: " + etnia + "\n" + "Venenoso? " + venenoso + "\n" + "Alado? " + alado + "\n" + "Ferrao? " + ferrao + "\n";
    }
    
}
