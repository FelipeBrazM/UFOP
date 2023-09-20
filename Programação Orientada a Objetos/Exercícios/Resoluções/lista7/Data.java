/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista7;

/**
 *
 * @author felip
 */
public final class Data {
    private int dia, mes, ano;

    public Data() {
    }
    
    public Data(int mes, int dia, int ano) {
        setDia(dia);
        setMes(mes);
        setAno(ano);
    }
    
    public void setDia(int dia){
        if(dia < 0 || dia > 31){
            System.out.println("Nao e possivel ter dias negativos, ou maiores que 31");
            System.exit(0);
        }else{
            this.dia = dia;
        }
    }
    
    public void setMes(int mes){
        if(mes < 0 || mes > 12){
            System.out.println("Nao e possivel ter meses negativos, ou mais que 12 meses");
            System.exit(0);
        }else{
            this.mes = mes;
        }
    }
    
    public void setAno(int ano){
        if(ano < 0){
            System.out.println("Nao e possivel ter anos negativos");
            System.exit(0);
        }else{
            this.ano = ano;
        }
    }

    public int getDia() {
        return dia;
    }

    public int getMes() {
        return mes;
    }

    public int getAno() {
        return ano;
    }
    
    @Override
    public String toString(){
        return "(" + dia + "/" + mes + "/" + ano + ")";
    }
    
    public int somaDia(int mes){
        int soma = 0;
        
        for(int i = 0; i < mes; i++){
            
            if(mes % 2 == 0){
                soma += 30;
            }else{
                soma+= 31;
            }
        }
        return soma;
    }
    
    
}
