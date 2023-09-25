/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package lista9;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import static lista9.CarroOrdena.insere;
import static lista9.CarroOrdena.print;

/**
 *
 * @author felip 
 */
public class mainCarro {
    public static void main(String argv[]){
        List <Carro> carros = new ArrayList<>();
        
        //insere os carros no ArrayList
        insere(carros);
        
        //printa o ArrayList sem ordenacao
        print("ArrayList normal, sem nenhuma ordenacao: ", carros);
       
        //ordena pela quilometragem
        Collections.sort(carros);
        print("ArrayList ordenado pela quilometragem rodada: ", carros);
        
        //comparator que ordena pela velocidade
        Comparator<Carro> com = new Comparator<Carro>(){
            @Override
            public int compare(Carro o1, Carro o2) {
                int velocidade1 = ((Carro)o1).getVel();
                int velocidade2 = ((Carro)o2).getVel();
                
                if(velocidade1 > velocidade2) return 1;
                else if(velocidade1 < velocidade2) return -1;
                else return 0;
            }   
        };
       
        //ordenando pela velocidade
        Collections.sort(carros, com);
        print("ArrayList ordenado pela velocidade: ", carros);
    }
}
