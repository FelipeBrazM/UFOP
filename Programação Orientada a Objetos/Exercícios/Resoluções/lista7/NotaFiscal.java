/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista7;

import java.util.ArrayList;

/**
 *
 * @author felip
 */
public class NotaFiscal {
    private String NumPeca;
    private String DescricaoPeca;
    private int QntPeca;
    private double Preco;

    public NotaFiscal(){}
    
    public NotaFiscal(String NumPeca, String DescricaoPeca, int QntPeca, double Preco) {
        this.NumPeca = NumPeca;
        this.DescricaoPeca = DescricaoPeca;
        this.QntPeca = QntPeca;
        this.Preco = Preco;
    }

    public void setNumPeca(String NumPeca) {
        this.NumPeca = NumPeca;
    }

    public void setDescricaoPeca(String DescricaoPeca) {
        this.DescricaoPeca = DescricaoPeca;
    }

    public void setQntPeca(int QntPeca) {
        this.QntPeca = QntPeca;
    }

    public void setPreco(double Preco) {
        this.Preco = Preco;
    }

    public String getNumPeca() {
        return NumPeca;
    }

    public String getDescricaoPeca() {
        return DescricaoPeca;
    }

    public int getQntPeca() {
        return QntPeca;
    }

    public double getPreco() {
        return Preco;
    }
    
    /*public static double getTotalNota(ArrayList<NotaFiscal> obj) {
        double sum = 0; 
        for (NotaFiscal nota : obj) {
            sum += nota.getPreco();
        }
        return sum;
    }*/
    
    @Override
    public String toString(){
        return "Codigo: " + NumPeca + "\n" + "Descricao: " + DescricaoPeca + "\n" +
                "Quantidade comprada: " + QntPeca + "\n" + "Preco: " + Preco + "\n\n";
    }   
}


