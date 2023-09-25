/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package DAO;

import java.util.List;


public interface DAOInterface {
    public void incluir(Object obj);
    public Object localizar(int id);
    public void atualizar(Object original, Object novo);
    public void remover(Object obj);
    public List<?> getLista();
}
