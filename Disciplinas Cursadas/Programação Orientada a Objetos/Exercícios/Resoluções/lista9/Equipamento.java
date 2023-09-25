/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class Equipamento {
    private boolean ligado;
    
    public Equipamento(){
        
    }
    
    public Equipamento(boolean ligado){
        this.ligado = ligado;
    }

    public void setLigado(boolean ligado) {
        this.ligado = ligado;
    }

    public boolean getLigado() {
        return ligado;
    }
    
    public void liga(){
        this.ligado = true;
    }
    
    public void desliga(){
        this.ligado = false;
    }
    
    
}
