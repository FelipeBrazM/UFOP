/*import java.util.Scanner;

public class l1exe1 {
    public static void main(String[] args) {
        int a, b, c;
        Scanner input = new Scanner(System.in);
        
        System.out.println("Entre com os valores dos 3 inteiros: ");
        a = input.nextInt();
        b = input.nextInt();
        c = input.nextInt();
        
        int resultadoMaior = Maior(a, b, c);
        System.out.println("O maior numero eh: " + resultadoMaior);
        
        int resultadoMenor = Menor(a, b, c);
        System.out.println("O menor numero eh: " + resultadoMenor);
        
        double resultadoMedia = Media(a, b, c);
        System.out.println("A media dos 3 numeros eh: " + resultadoMedia);
    }

    public static int Maior(int a, int b, int c) {
        int maior = a; // Inicializa 'maior' com o valor de 'a'
        
        if (b > maior) {
            maior = b; // Se 'b' for maior que 'maior', atualiza 'maior' com o valor de 'b'
        }
        
        if (c > maior) {
            maior = c; // Se 'c' for maior que 'maior', atualiza 'maior' com o valor de 'c'
        }
        
        return maior; // Retorna o valor do maior número
    }

    public static int Menor(int a, int b, int c){
        int menor = a;
        
        if(b < menor){
            menor = b;
        }

        if(c < menor){
            menor = c;
        }
        
        return menor;
    }

    public static double Media(int a, int b, int c){
        double media = (a + b + c) / 3.0;
        return media;
    }
}*/