/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package Modelo;

import java.util.Objects;


public class Categoria {
    private static int contador = 0;
    private int id;
    private String titulo;

    public Categoria(String titulo) {
        this.id = ++contador;
        this.titulo = titulo;
    }
    
    public Categoria(String titulo, int id) {
        this.id = id;
        this.titulo = titulo;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public int getId() {
        return id;
    }


    public void setId(int id) {
        this.id = id;
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
        final Categoria other = (Categoria) obj;
        if (this.id != other.id) {
            return false;
        }
        return Objects.equals(this.titulo, other.titulo);
    }

    @Override
    public String toString() {
        return "Categoria{" + "id=" + id + ", titulo=" + titulo + '}';
    }

    public void atualizaCategoria(Categoria nova){
        //Copia os dados de uma nova categoria e mantem o id e o endereco de memoria
        
        this.setTitulo(nova.getTitulo());
    }

       
    
}
