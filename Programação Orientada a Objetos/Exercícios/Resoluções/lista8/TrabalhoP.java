/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista8;

/**
 *
 * @author felip
 */
public class TrabalhoP {
    private float nota;
    private int qntProblema;
    private float pResolvido;
    private boolean relatorio = false;
    private String site;

    public TrabalhoP() {
    }

    public void setNota(float nota) {
        this.nota = nota;
    }

    public void setQntProblema(int qntProblema) {
        this.qntProblema = qntProblema;
    }

    public void setpResolvido(float pResolvido) {
        this.pResolvido = pResolvido;
    }

    public void setRelatorio(boolean relatorio) {
        this.relatorio = relatorio;
    }
    
    public void setSite(String site){
        this.site = site;
    }

    public float getNota() {
        return nota;
    }

    public int getQntProblema() {
        return qntProblema;
    }

    public float getpResolvido() {
        return pResolvido;
    }

    public boolean getRelatorio() {
        return relatorio;
    }
    
    public String getSite(){
        return site;
    }
    
    public void calculaNota(int qntProblema){
        //Se a nota for maior que 6, ele está aprovado, se não significa que ele reprovou
        if(qntProblema >= 6){
            nota = (float)qntProblema;
            System.out.println("A nota do aluno com o ponto extra foi de: " + nota);
        }else{
            nota = (float)qntProblema;
            System.out.println("A sua nota na disciplina foi de: " + nota + "\n" + "Voce foi reprovado!");
        }
    }
    
    public void calculaNota(float pResolvido, boolean relatorio){
        if(pResolvido >= 6.0 && relatorio == true){
            nota = pResolvido + 1;
            System.out.println("A nota do aluno com o ponto extra foi de: " + nota);
        }else if(pResolvido >= 6.0 && relatorio == false){
            nota = pResolvido;
            System.out.println("A sua nota na disciplina foi de: " + nota);
        }else{
            nota = pResolvido;
            System.out.println("A sua nota na disciplina foi de: " + nota + "\n" + "Voce foi reprovado!");
            
        }
    }
    
    public void calculaNota(String site){
        nota = 0;
        System.out.println("Devido ao plagio a nota do aluno foi zerada!");
    }
    
    
    
            
            
            
            
            
}
