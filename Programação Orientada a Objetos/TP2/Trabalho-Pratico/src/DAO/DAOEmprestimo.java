/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DAO;

import Dados.Dados;
import Modelo.Emprestimo;
import java.util.List;

/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
public class DAOEmprestimo implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Emprestimo emprestimo = (Emprestimo) obj;
        Dados.listaEmprestimos.add(emprestimo);
    }

    @Override
    public Emprestimo localizar(int id) {
        List<Emprestimo> listaEmprestimos = Dados.listaEmprestimos;
        
        for(int i = 0; i < listaEmprestimos.size(); i++){
            if(listaEmprestimos.get(i).getId() == id)
                return listaEmprestimos.get(i);
        }
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Emprestimo original = (Emprestimo) objOriginal;
        Emprestimo novo = (Emprestimo) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.listaEmprestimos.indexOf(original);
        if(index == -1) return;
        
        original.atualizaEmprestimo(novo);
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        
        Dados.listaEmprestimos.remove((Emprestimo)obj);
    }

    @Override
    public List<Emprestimo> getLista() {
        return Dados.listaEmprestimos;
    }
    
}
