/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista8;

import java.util.Scanner;

/**
 *
 * @author felip
 */
public class mainEstaciona {
    public static void main (String argv[]){
        Estacionamento carro = new Estacionamento();
        Hora entrada = new Hora();
        Hora saida = new Hora();
        
        Scanner input = new Scanner(System.in);
        double valor;
        
        System.out.println("Cadastre a placa e o modelo do carro: ");
        carro.setPlaca(input.nextInt());
        input.nextLine();
        carro.setModelo(input.nextLine());
        
        System.out.println("Coloque a hora de entrada: ");
        entrada.setHora(input.nextInt());
        entrada.setMin(input.nextInt());
        entrada.setSeg(input.nextInt());
    
        System.out.println("\nEsperando o dono do carro voltar.....\n");
        
        System.out.println("Coloque a hora de saida: ");
        saida.setHora(input.nextInt());
        saida.setMin(input.nextInt());
        saida.setSeg(input.nextInt());
        
        System.out.println("Calculando o valor a ser pago espere.....\n");
        saida.subtrair(entrada);
        valor = carro.pagamento(saida.getHora());
        
        System.out.println(carro);
        System.out.println("Este carro tera que pagar: " + valor + " reais");
        System.out.println("Fechando o estacionamento.....");
        System.out.println("----------------------");
    }
}
