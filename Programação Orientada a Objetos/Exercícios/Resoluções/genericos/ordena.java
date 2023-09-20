/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package genericos;

import static genericos.JavaOrdena.insere;
import static genericos.JavaOrdena.print;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 *
 * @author felip
 */
public class ordena {
    public static void main(String[] args){
        List<Conta> contas = new ArrayList<>();
        
        //insere caontas na colecao
        insere(contas);
        
        //(1) ordena pelo codigo
        Collections.sort(contas);
        print("Ordena pelo numero de conta", contas);
        
        //comparator que ordena pelo nome
        Comparator<Conta> com = new Comparator<Conta>(){
            @Override 
            public int compare(Conta c1, Conta c2){
                String nome1 = c1.getNome();
                String nome2 = c2.getNome();
                return nome1.compareTo(nome2);
            }
        };
        
        //(2)sort ordena pelo nome
        Collections.sort(contas, com);
        print("Ordena pelo nome de conta", contas);
        
        //(3)sort comparator que ordena pelo saldo 
        Collections.sort(contas, new Comparator(){
            @Override
            public int compare(Object o1, Object o2){
                double saldo1 = ((Conta)o1).getSaldo();
                double saldo2 = ((Conta)o2).getSaldo();
                if(saldo1 > saldo2) return 1;
                else if(saldo1 < saldo2) return -1;
                else return 0;
            }
        });
        print("Ordena pelo saldo de conta", contas);
        
    }
}
