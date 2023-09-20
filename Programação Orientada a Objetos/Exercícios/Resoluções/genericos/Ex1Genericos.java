/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package genericos;

import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.Iterator;

/**
 *
 * @author felip
 */
public class Ex1Genericos {
    private static final String[] colors = {"MAGENTA", "RED", "WHITE", "BLUE", "CYAN"};
    private static final String[] removeColors = {"RED", "WHITE", "BLUE"};
    
    //cria um ArrayList, adiciona cores e manipula

    public Ex1Genericos() {
        List<String> list = new ArrayList<>();
        List<String> removeList = new ArrayList<>();
        
        //adiciona elementos a lista
        for(String color : colors)
            list.add(color);
        
        //adiciona elementos a lista
        for(String color : removeColors)
            removeList.add(color);
        
        System.out.println("ArrayList: ");
        
        //exibe conteudo
        for(int cont = 0; cont < list.size(); cont++)
            System.out.println(list.get(cont));
        
        //remove elementos
        removeColorMethod(list, removeList);
        
        System.out.println("\n\nArrayList after calling removeColors: ");
        
        //exibe conteudo
        for(String color : list)
            System.out.println(color);
        
    }
    
    //remove elementos especificadores em collection2 de collection1
    private void removeColorMethod(Collection<String> collection1, Collection<String> collection2){
        //retorna o interador
        Iterator<String> iterator = collection1.iterator();
        
        //percorre a colecao enquanto houver itens
        while(iterator.hasNext())
            if(collection2.contains(iterator.next()))
                iterator.remove();//remove
    }
    
    /*public static void main(String args[]){
        new Ex1Genericos();
    }*/
    
}
