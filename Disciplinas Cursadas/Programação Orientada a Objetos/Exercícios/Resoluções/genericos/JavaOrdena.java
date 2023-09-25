/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package genericos;

import java.util.Collection;

/**
 *
 * @author felip
 */
public class JavaOrdena {
    public static void print(String titulo, Collection <Conta> collection){
        System.out.println(titulo);
        for(Conta elem : collection)
            System.out.println(elem);
        System.out.println(" ");
    }
    
    public static void insere(Collection <Conta> collection){
        Conta obj = new Conta(266, "Marco", 500.45);
        collection.add(obj);
        
        Conta obj2 = new Conta(29, "Pedro", 1909.00);
        collection.add(obj2);
        
        Conta obj3 = new Conta(101, "Andre", 200.00);
        collection.add(obj3);
    }
}

