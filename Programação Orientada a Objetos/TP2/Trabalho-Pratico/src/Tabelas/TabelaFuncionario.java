/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOFuncionario;
import Modelo.Funcionario;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
public class TabelaFuncionario extends AbstractTableModel{
    
    private DAOFuncionario daoFuncionario = new DAOFuncionario();
    private ArrayList<Funcionario> funcionarios;
    private String[] colunas = {"Nome", "Sobrenome", "Matrícula", "ID"};
    
    public TabelaFuncionario(){
        //Marcando o ponteiro de funcionarios com o ponteiro do vetor de funcionarios dos dados
        funcionarios = (ArrayList<Funcionario>) daoFuncionario.getLista();
        this.fireTableDataChanged();
    }
    
    public void addFuncionario(Funcionario funcionario){
        daoFuncionario.incluir(funcionario);
        this.fireTableDataChanged();
    }
    
    public void updateFuncionario(Funcionario funcNovo, Funcionario funcVelho){
        daoFuncionario.atualizar(funcVelho, funcNovo);
        this.fireTableDataChanged();
    }
    
    public void deletarFuncionario(Funcionario funcionario){
        daoFuncionario.remover(funcionario);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return funcionarios.size();
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
        return switch (columnIndex){
            case 0 -> funcionarios.get(rowIndex).getNome();
            case 1 -> funcionarios.get(rowIndex).getSobreNome();
            case 2 -> funcionarios.get(rowIndex).getMatricula();
            default -> funcionarios.get(rowIndex).getId();
        };
    }
    
}
