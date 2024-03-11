/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DAO;

import Dados.Dados;
import Modelo.Usuario;
import java.util.List;

/**
 *
 * @author Felipe Marques, Lucas Chagas, Matheus Peixoto, Nicolas Mendes, Pedro Henrique de
Oliveira, Pedro Morais
 */
public class DAOUsuario implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Usuario usuario = (Usuario) obj;
        Dados.listaUsuarios.add(usuario);
    }

    @Override
    public Usuario localizar(int id) {
        List<Usuario> listaUsuarios = Dados.listaUsuarios;
        
        for(int i = 0; i < listaUsuarios.size(); i++){
            if(listaUsuarios.get(i).getId() == id)
                return listaUsuarios.get(i);
        }
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Usuario original = (Usuario) objOriginal;
        Usuario novo = (Usuario) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.listaUsuarios.indexOf(original);
        if(index == -1) return;
        
        original.atualizaUsuario(novo);
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        Dados.listaUsuarios.remove((Usuario)obj);
    }

    @Override
    public List<Usuario> getLista() {
        return Dados.listaUsuarios;
    }
    
}
