/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista7;

import java.util.Random;

/**
 *
 * @author felip
 */
public class MoedaViciada {
    private boolean cara = false;
    private boolean coroa = false;
    Random aleatorio = new Random();

    public MoedaViciada() {
    }

    public void setCara(boolean cara) {
        this.cara = cara;
    }

    public void setCoroa(boolean coroa) {
        this.coroa = coroa;
    }

    public boolean isCara() {
        return cara;
    }

    public boolean isCoroa() {
        return coroa;
    }
      
    public void userCoroa(){
        if(aleatorio.nextInt(10) < 3){
            coroa = true;
        }
        else{
            cara = true;
        }
    }
    
    public void userCara(){
        if(aleatorio.nextInt(10) < 3){
            cara = true;
        }else{
            coroa = true;
        }
    }
    
    @Override
    public String toString(){
        return "\n" + "cara e: " + cara +"\n" + "coroa e: " + coroa;
    }
}
