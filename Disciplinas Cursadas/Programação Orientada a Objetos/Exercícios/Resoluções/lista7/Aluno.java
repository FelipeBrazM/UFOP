/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista7;

/**
 *
 * @author felip
 */
public class Aluno {
    private String nome;
    private int serie;
    private int grau;
    private static int n = 0;
    
    Aluno(){
        n++;
    }
    
    Aluno(String nome, int serie, int grau){
        setNome(nome);
        setSerie(serie);
        setGrau(grau);
        n++;
    }
    
    @Override
    protected void finalize() throws Throwable{
        try{
            n--;
            System.out.println("Finalizou um objeto");
        }
        finally{
            super.finalize();
        }
    }
    
    public void setNome(String nome){
        this.nome = nome;
    }
    
    public void setSerie(int serie){
        this.serie = serie;
    }
    
    public void setGrau(int grau){
        this.grau = grau;
    }
    
    public String getNome(){
        return nome;
    }
    
    public int getSerie(){
        return serie;
    }
    
    public int getGrau(){
        return grau;
    }
    
    public int getN(){
        return n;
    }
    
    @Override 
    public String toString(){
        return "A quantidade de objetos criados da classe Aluno e de: " + getN();
    }
    
    
    
}
