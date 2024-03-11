/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package Modelo;


public class Funcionario extends Pessoa {
    private int matricula;

    public Funcionario(int matricula, int id, String nome, String sobreNome) {
        super(id, nome, sobreNome);
        this.matricula = matricula;
    }   
    
    public Funcionario(int matricula, String nome, String sobreNome){
        super(nome, sobreNome);
        this.matricula = matricula;
    }
    
    public int getMatricula() {
        return matricula;
    }

    public void setMatricula(int matricula) {
        this.matricula = matricula;
    }
    
    public void atualizaFuncionario(Funcionario novo){
        this.setNome(novo.getNome());
        this.setSobreNome(novo.getSobreNome());
        this.setMatricula(novo.getMatricula());
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
        final Funcionario other = (Funcionario) obj;
        return super.equals(other) && this.matricula == other.matricula;
    }
}
