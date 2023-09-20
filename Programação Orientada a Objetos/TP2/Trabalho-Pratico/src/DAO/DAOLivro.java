/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DAO;

import Dados.Dados;
import Modelo.Autor;
import Modelo.Categoria;
import Modelo.Livro;
import java.util.List;

/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
public class DAOLivro implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Livro livros = (Livro) obj;
        Dados.listaLivros.add(livros);
    }

    @Override
    public Livro localizar(int id) {        
        List<Livro> listaLivros = Dados.listaLivros;
        
        for(int i = 0; i < listaLivros.size(); i++)
            if(listaLivros.get(i).getId() == id)
                return listaLivros.get(i);
    
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Livro original = (Livro) objOriginal;
        Livro novo = (Livro) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.listaLivros.indexOf(original);
        if(index == -1) return;

        Dados.listaLivros.set(index, novo);
        
        //Copiando os dados da lista de autores e categoria
        novo.setAutor(original.getAutor());
        novo.setCategoria(original.getCategoria());
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        Dados.listaLivros.remove((Livro)obj);
    }

    @Override
    public List<Livro> getLista() {
        return Dados.listaLivros;
    }
    
    public void adicionarCategoria(int id, Categoria categoria){
        Livro livro = localizar(id);
        livro.adicionarCategoria(categoria);
    }
    
    public void removerCategoria(int id, Categoria categoria){
        Livro livro = localizar(id);
        livro.removerCategoria(categoria);
    }
    
    public void adicionarAutor(int id, Autor autor){
        Livro livro = localizar(id);
        livro.adicionarAutor(autor);
    }
    
    public void removerAutor(int id, Autor autor){
        Livro livro = localizar(id);
        livro.removerAutor(autor);
    }
    
}
