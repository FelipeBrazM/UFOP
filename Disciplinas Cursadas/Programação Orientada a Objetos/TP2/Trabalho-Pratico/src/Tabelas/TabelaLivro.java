/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOLivro;
import Modelo.Autor;
import Modelo.Categoria;
import Modelo.Livro;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
public class TabelaLivro extends AbstractTableModel{
    
    private DAOLivro daoLivro = new DAOLivro();
    private ArrayList<Livro> livros;
    private String[] colunas = {"Título", "Autor(es)", "Categoria(s)", "id"};
    
    public TabelaLivro(){
        //Marcando o ponteiro de livros com o ponteiro do vetor de livros dos dados
        livros = (ArrayList<Livro>) daoLivro.getLista();
        this.fireTableDataChanged();
    }
    
    public void addLivro(Livro livro){
        daoLivro.incluir(livro);
        this.fireTableDataChanged();
    }
    
    public void updateLivro(Livro livroNovo, Livro livroVelho){
        daoLivro.atualizar(livroVelho, livroNovo);
        this.fireTableDataChanged();
    }
    
    public void deletarLivro(Livro livro){
        daoLivro.remover(livro);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return livros.size();
    }

    @Override
    public int getColumnCount() {
        return colunas.length;
    }
    
    @Override
    public String getColumnName(int column) {
        return colunas[column];
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Object obj;
        
        switch(columnIndex){
            case 0 -> obj = livros.get(rowIndex).getTitulo();
            case 1 -> {
                String strListaAutores = "";
                for(Autor aut : livros.get(rowIndex).getAutor()) 
                    strListaAutores += aut.getNome() + " " + aut.getSobreNome() + ", ";

                if(strListaAutores.length() >= 2)
                    obj = strListaAutores.substring(0, strListaAutores.length() - 2);
                else
                    obj = strListaAutores;
            }
            case 2 -> {
                String strListaCategorias = "";
                for(Categoria cat : livros.get(rowIndex).getCategoria()) 
                    strListaCategorias += cat.getTitulo()+ ", ";

                if(strListaCategorias.length() >= 2)
                    obj = strListaCategorias.substring(0, strListaCategorias.length() - 2);
                else
                    obj = strListaCategorias;
            }
            default -> obj = livros.get(rowIndex).getId();
        }
        
        return obj;
    }
    
}
