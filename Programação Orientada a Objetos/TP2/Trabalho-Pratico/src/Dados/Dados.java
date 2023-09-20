/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
*/

package Dados;

import Modelo.*;
import java.util.ArrayList;
import java.util.List;


public class Dados {
    public static List<Funcionario> listaFuncionarios;
    public static List<Usuario> listaUsuarios;
    public static List<Autor> listaAutores;
    public static List<Livro> listaLivros;
    public static List<Categoria> listaCategorias;
    public static List<Emprestimo> listaEmprestimos;
  
    
    public Dados(){
        this.listaFuncionarios = new ArrayList<>();
        this.listaUsuarios = new ArrayList<>();
        this.listaAutores = new ArrayList<>();
        this.listaLivros = new ArrayList<>();
        this.listaCategorias = new ArrayList<>();
        this.listaEmprestimos = new ArrayList<>();
    }
}
