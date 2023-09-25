/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class Humano {
    protected String nome;
    protected String sexo;
    protected int idade;
    protected String lingua;
    protected String etnia;

    public Humano() {
    }

    public Humano(String nome, String sexo, int idade, String lingua, String etnia) {
        this.nome = nome;
        this.sexo = sexo;
        this.idade = idade;
        this.lingua = lingua;
        this.etnia = etnia;
    }
    
    public String getNome() {
        return nome;
    }

    public String getSexo() {
        return sexo;
    }

    public int getIdade() {
        return idade;
    }

    public String getLingua() {
        return lingua;
    }

    public String getEtnia() {
        return etnia;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setSexo(String sexo) {
        this.sexo = sexo;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public void setLingua(String lingua) {
        this.lingua = lingua;
    }

    public void setEtnia(String etnia) {
        this.etnia = etnia;
    }
    
    
}
