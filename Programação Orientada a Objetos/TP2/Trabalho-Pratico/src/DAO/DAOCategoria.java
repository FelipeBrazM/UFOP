/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
package DAO;

import Dados.Dados;
import Modelo.Categoria;
import java.util.List;


public class DAOCategoria implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Categoria categoria = (Categoria) obj;
        Dados.listaCategorias.add(categoria);
    }

    @Override
    public Categoria localizar(int id) {
        List <Categoria> listaCategoria = Dados.listaCategorias;
        
        for(int i = 0; i < listaCategoria.size(); i++)
            if(listaCategoria.get(i).getId() == id)
                return listaCategoria.get(i);
        
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Categoria original = (Categoria) objOriginal;
        Categoria novo = (Categoria) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.listaCategorias.indexOf(original);
        if(index == -1) return;
               
        original.atualizaCategoria(novo);
        
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        Dados.listaCategorias.remove((Categoria)obj);
    }

    @Override
    public List<Categoria> getLista() {
        return Dados.listaCategorias;
    }
    
}
