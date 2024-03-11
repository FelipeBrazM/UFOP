/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package Principal;

import DAO.DAOAutor;
import DAO.DAOCategoria;
import DAO.DAOFuncionario;
import DAO.DAOLivro;
import DAO.DAOUsuario;
import Dados.Dados;
import Modelo.Autor;
import Modelo.Categoria;
import Modelo.Funcionario;
import Modelo.Livro;
import Modelo.Usuario;
import Telas.MenuPrincipal;


public class TrabalhoPratico {


    public static void main(String[] args) {
        Dados dados = new Dados();
        
        DAOCategoria daoCategoria = new DAOCategoria();
        DAOAutor daoAutor = new DAOAutor();
        DAOLivro daoLivro = new DAOLivro();
        DAOFuncionario daoFuncionario = new DAOFuncionario();
        DAOUsuario dAOUsuario = new DAOUsuario();
        
        //Criando categorias
        Categoria cat1 = new Categoria("Programação"); daoCategoria.incluir(cat1);
        Categoria cat2 = new Categoria("Banco de dados"); daoCategoria.incluir(cat2);

        //Criando autores
        Autor autor1 = new Autor("Lorem Ipsum is simply", "Alan", "Kay"); daoAutor.incluir(autor1);
        Autor autor2 = new Autor("Lorem Ipsum is simply", "Alan", "Turing"); daoAutor.incluir(autor2);
       
        //Criando livros
        Livro livro1 = new Livro("POO"); livro1.adicionarAutor(autor1); livro1.adicionarCategoria(cat1); daoLivro.incluir(livro1);
        Livro livro2 = new Livro("Programação"); livro2.adicionarAutor(autor2); livro2.adicionarCategoria(cat1); daoLivro.incluir(livro2);

        //Criando Funcionario
        Funcionario func1 = new Funcionario(123, "Fulano", "Beltrano"); daoFuncionario.incluir(func1);
        Funcionario func2 = new Funcionario(456, "Ciclano", "Deltrando"); daoFuncionario.incluir(func2);
        
        //Criando Usuario
        Usuario usuario1 = new Usuario(123, "Pedro", "Leão"); dAOUsuario.incluir(usuario1);
        Usuario usuario2 = new Usuario(546, "Felipe", "Braz"); dAOUsuario.incluir(usuario2);
        
        //Iniciando a tela
        MenuPrincipal menuPrincipal = new MenuPrincipal();
        menuPrincipal.setVisible(true);
    }
    
}
