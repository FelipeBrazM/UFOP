/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

/**
 *
 * @author felip
 */
public class EquipamentoSonoro extends Equipamento {
    private short volume;
    private boolean stereo;

    public EquipamentoSonoro(){
        
    }
    
    public void setVolume(short volume) {
        this.volume = volume;
    }

    public void setStereo(boolean stereo) {
        this.stereo = stereo;
    }

    public short getVolume() {
        return volume;
    }

    public boolean getStereo() {
        return stereo;
    }
    
    public void mono(){
        stereo = false;
    }
    
    public void stereo(){
        stereo = true;
    }
    
    @Override
    public void liga(){
        setLigado(true);
        volume = 5;
    }
    
    @Override
    public String toString(){
        return "Volume: " + volume + " Stereo ligado? " + stereo;
    }
    
}
