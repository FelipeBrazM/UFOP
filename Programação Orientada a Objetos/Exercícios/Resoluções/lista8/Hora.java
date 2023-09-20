/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista8;

/**
 *
 * @author felip
 */
public class Hora {
    private int hora;
    private int min;
    private int seg;

    public Hora() {
    }

    public Hora(int hora, int min, int seg) {
        this.hora = hora;
        this.min = min;
        this.seg = seg;
    }

    public void setHora(int hora) {
        this.hora = hora;
    }

    public void setMin(int min) {
        this.min = min;
    }

    public void setSeg(int seg) {
        this.seg = seg;
    }

    public int getHora() {
        return hora;
    }

    public int getMin() {
        return min;
    }

    public int getSeg() {
        return seg;
    }
    
    @Override 
    public String toString(){
        return hora + ":" + min + ":" + seg;
    }
    
    public void subtrair(Hora obj) {
        // Converte os hora em seg para facilitar a subtração
        int totalsegEsteHora = this.hora * 3600 + this.min * 60 + this.seg;
        int totalsegobj = obj.hora * 3600 + obj.min * 60 + obj.seg;

        int diferencaseg = totalsegEsteHora - totalsegobj;

        if (diferencaseg >= 0) {
            // Calcula a diferença em hora, min e seg
            this.hora = diferencaseg / 3600;
            this.min = (diferencaseg % 3600) / 60;
            this.seg = diferencaseg % 60;
        } else {
            // Se a diferença for negativa, significa que o obj é maior, então definimos todos os atributos como 0.
            this.hora = 0;
            this.min = 0;
            this.seg = 0;
        }
    }
    
    public void somar(Hora outroHora) {
        // Converte os hora em seg para facilitar a soma
        int totalsegEsteHora = this.hora * 3600 + this.min * 60 + this.seg;
        int totalsegOutroHora = outroHora.hora * 3600 + outroHora.min * 60 + outroHora.seg;

        int somaseg = totalsegEsteHora + totalsegOutroHora;

        // Calcula a soma em hora, min e seg
        this.hora = somaseg / 3600;
        this.min = (somaseg % 3600) / 60;
        this.seg = somaseg % 60;
    }      
}
