/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOCategoria;
import DAO.DAOLivro;
import Modelo.Categoria;
import Modelo.Livro;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
public class TabelaCategoria extends AbstractTableModel{
    
    private DAOCategoria daoCategoria = new DAOCategoria();
    private DAOLivro daoLivro = new DAOLivro();
    private ArrayList<Categoria> categorias;
    private String[] colunas = {"Nome", "id"};
    
    public TabelaCategoria(){
        //Marcando o ponteiro de categorias com o ponteiro do vetor de categorias dos dados
        this.categorias = (ArrayList<Categoria>) daoCategoria.getLista();
        this.fireTableDataChanged();
    }
    
    public TabelaCategoria(ArrayList<Categoria> arr){
        this.categorias = arr;
        this.fireTableDataChanged();
    }
    
    public void addCategoria(Categoria categoria){
        this.daoCategoria.incluir(categoria);
        this.fireTableDataChanged();
    }
        
    public void updateCategoria(Categoria catNova, Categoria catVelha){
        this.daoCategoria.atualizar(catVelha, catNova);
        this.fireTableDataChanged();
    }
    
    public void deletarCategoria(Categoria categoria){
        this.daoCategoria.remover(categoria);
        this.fireTableDataChanged();
    }
    
    
    //Na tela de editar as categorias, adiciona e remove as categorias do livro e altera a tabela de categorias, que pode ter a sua lita vindo de diferentes vetores com base nos construtores
    public void addCategoriaLivro(Categoria categoria, Livro livro){
        //Verificando se o item esta na tabela ou nao. Caso nao esteja, entao adiciona
        if(categorias.indexOf(categoria) == -1){
            daoLivro.adicionarCategoria(livro.getId(), categoria);
            this.fireTableDataChanged();
        }
    }
    
    public void deletarCategoriaLivro(Categoria categoria, Livro livro){
        daoLivro.removerCategoria(livro.getId(), categoria);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return this.categorias.size();
    }

    @Override
    public int getColumnCount() {
        return this.colunas.length;
    }
    
    @Override
    public String getColumnName(int column) {
        return this.colunas[column];
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return switch (columnIndex){
            case 0 -> this.categorias.get(rowIndex).getTitulo();
            default -> this.categorias.get(rowIndex).getId();
        };
    }
    
}
