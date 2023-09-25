/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista8;

/**
 *
 * @author felip
 */
public class Estacionamento {
    private int placa;
    private String modelo;

    public Estacionamento() {
    }

    public void setPlaca(int placa) {
        this.placa = placa;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public int getPlaca() {
        return placa;
    }

    public String getModelo() {
        return modelo;
    }
    
    @Override 
    public String toString(){
        return "Placa: " + placa + " " + "Modelo: " + modelo;
    }
    
    public double pagamento(int hora){
        return 1.50 * (double)hora;
    }
}
