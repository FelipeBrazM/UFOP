/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */

package Modelo;

import java.util.Objects;

public class Autor extends Pessoa {
    private String biografia;

    public Autor(String biografia, int id, String nome, String sobreNome) {
        super(id, nome, sobreNome);
        this.biografia = biografia;
    }
    
    public Autor(String biografia, String nome, String sobreNome) {
        super(nome, sobreNome);
        this.biografia = biografia;
    }

    public String getBiografia() {
        return biografia;
    }

    public void setBiografia(String biografia) {
        this.biografia = biografia;
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
        final Autor other = (Autor) obj;
        return super.equals(other) && Objects.equals(this.biografia, other.biografia);
    }

    @Override
    public String toString() {
        return super.toString() + " | Autor{" + "biografia=" + biografia + '}';
    }
    
    public void atualizaAutor(Autor novo){
        //Copia os dados do autor e mantem o id e o endereco de memoria
        //O clone para um autor velho tornar o novo daria problemas com o endereco de memoria, que iria mudar
        
        this.setBiografia(novo.getBiografia());
        this.setNome(novo.getNome());
        this.setSobreNome(novo.getSobreNome());

    }
}