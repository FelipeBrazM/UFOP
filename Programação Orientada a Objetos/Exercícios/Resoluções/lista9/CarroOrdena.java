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
public class CarroOrdena {
    public static void print(String titulo, Collection <Carro> collection){
        System.out.println(titulo);
        for(Carro elem : collection)
            System.out.println(elem);
        System.out.println(" ");
    }
    
    public static void insere(Collection <Carro> collection){
        Carro obj1 = new Carro(26846, true, 120);
        collection.add(obj1);
        
        Carro obj2 = new Carro(85986, true, 125);
        collection.add(obj2);
        
        Carro obj3 = new Carro(10000, true, 100);
        collection.add(obj3);
        
        Carro obj4 = new Carro(1000, false, 80);
        collection.add(obj4);
    }
    
}


