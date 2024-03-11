/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

import java.util.Collection;

/**
 *
 * @author felip
 */
public final class Carro extends Transporte implements Comparable <Carro>{
    private int quilometragem; 

    public Carro() {
    }

    public Carro(int quilometragem, boolean ligado, int vel) {
        super(ligado, vel);
        setQuilometragem(quilometragem);
    }

    public int getQuilometragem() {
        return quilometragem;
    }

    public void setQuilometragem(int quilometragem) {
        if(quilometragem < 0 || quilometragem > 999999){
            System.out.println("Nao e possivel ter essa quilometragem");
            System.exit(0);
        }else{
             this.quilometragem = quilometragem;
        }
    }
    
    @Override 
    public String toString(){
        return "Velocidade: " + getVel() + " Quilometragem: " + quilometragem; 
    }  
    
    @Override
    public int compareTo(Carro o){
        if(this.quilometragem < o.quilometragem)
            return -1;
        if(this.quilometragem > o.quilometragem)
            return 1;
        return 0;
    }
}
