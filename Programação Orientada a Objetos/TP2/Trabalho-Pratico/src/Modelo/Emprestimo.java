/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package Modelo;

import java.util.Date;
import java.util.Objects;

public class Emprestimo {
    private static int contador = 0;
    private int id;
    private int idFuncionario;
    private int idUsuario;
    private int idLivro;
    private Date dataEmprestimo;

    public Emprestimo(int id, int idFuncionario, int idUsuario, int idLivro, Date dataEmprestimo) {
        this.id = id;
        this.idFuncionario = idFuncionario;
        this.idUsuario = idUsuario;
        this.idLivro = idLivro;
        this.dataEmprestimo = dataEmprestimo;
    }
    
    public Emprestimo(int idFuncionario, int idUsuario, int idLivro, Date dataEmprestimo){
        this(++contador, idFuncionario, idUsuario, idLivro, dataEmprestimo);
    }

    public Date getDataEmprestimo() {
        return dataEmprestimo;
    }

    public void setDataEmprestimo(Date dataEmprestimo) {
        this.dataEmprestimo = dataEmprestimo;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getIdFuncionario() {
        return idFuncionario;
    }

    public void setIdFuncionario(int idFuncionario) {
        this.idFuncionario = idFuncionario;
    }

    public int getIdUsuario() {
        return idUsuario;
    }

    public void setIdUsuario(int idUsuario) {
        this.idUsuario = idUsuario;
    }

    public int getIdLivro() {
        return idLivro;
    }

    public void setIdLivro(int idLivro) {
        this.idLivro = idLivro;
    }
    
    public void atualizaEmprestimo(Emprestimo novo){
        this.setIdFuncionario(novo.getIdFuncionario());
        this.setIdUsuario(novo.getIdUsuario());
        this.setIdLivro(novo.getIdLivro());
        this.setDataEmprestimo(novo.getDataEmprestimo());
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
        final Emprestimo other = (Emprestimo) obj;
        if (this.id != other.id) {
            return false;
        }
        if (this.idFuncionario != other.idFuncionario) {
            return false;
        }
        if (this.idUsuario != other.idUsuario) {
            return false;
        }
        if (this.idLivro != other.idLivro) {
            return false;
        }
        return Objects.equals(this.dataEmprestimo, other.dataEmprestimo);
    }
}
