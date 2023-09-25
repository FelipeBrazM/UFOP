/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package Modelo;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Livro {
    private static int contador = 0;
    
    private int id;
    private String titulo;
    private List<Categoria> categoria;
    private List<Autor> autor;

    public Livro(int id, String titulo) {
        this.id = id;
        this.titulo = titulo;
        this.categoria = new ArrayList<>();
        this.autor = new ArrayList<>();
    }
    
    public Livro(String titulo) {
        this.id = ++contador;
        this.titulo = titulo;
        this.categoria = new ArrayList<>();
        this.autor = new ArrayList<>();
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public List<Categoria> getCategoria() {
        return categoria;
    }

    public void setCategoria(List<Categoria> categoria) {
        this.categoria = categoria;
    }

    public List<Autor> getAutor() {
        return autor;
    }

    public void setAutor(List<Autor> autor) {
        this.autor = autor;
    }
    
    public void adicionarCategoria(Categoria categoria){
        this.categoria.add(categoria);
    }
    
    public void removerCategoria(Categoria categoria){
        this.categoria.remove(categoria);
    }
    
    public void adicionarAutor(Autor autor){
        this.autor.add(autor);
    }
    
    public void removerAutor(Autor autor){
        this.autor.remove(autor);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Livro other = (Livro) obj;
        if (this.id != other.id) {
            return false;
        }
        if (!Objects.equals(this.titulo, other.titulo)) {
            return false;
        }
        if (!Objects.equals(this.categoria, other.categoria)) {
            return false;
        }
        return Objects.equals(this.autor, other.autor);
    }
    
    public void atualizaLivro(Livro novo){
        //Copia os dados de uma nova categoria e mantem o id e o endereco de memoria
        
        //Na tela de editar o livro, somente alteramos o titulo, dessa forma, a categoria e o
        //titulo sao alterados por uma tela que modifica a lista em si, nao um valor unico
        this.setTitulo(novo.titulo);
    }

    
}
