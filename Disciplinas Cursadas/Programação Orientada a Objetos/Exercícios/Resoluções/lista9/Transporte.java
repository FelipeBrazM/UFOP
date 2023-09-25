/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class Transporte {
    private boolean ligado;
    private int vel;

    public Transporte() {
    }
    
    public Transporte(boolean ligado, int vel) {
        this.ligado = ligado;
        setVel(vel);
    }
    
    public void setLigado(boolean ligado) {
        this.ligado = ligado;
    }

    public final void setVel(int vel) {
        if(vel < 0 || vel > 200){
            System.out.println("Velocidade negativa nao existe!");
            System.exit(0);
        }
        this.vel = vel;
    }

    public boolean getLigado() {
        return ligado;
    }

    public int getVel() {
        return vel;
    }
    
    public void liga(){
        ligado = true;
    }
    
    public void desliga(){
        ligado = false;
        vel = 0;
    } 
}
