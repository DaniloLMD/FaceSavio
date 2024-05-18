public class Main {
    public static void main(String[] args) {
        Usuario caio = new Usuario("caio");
        Usuario danilo = new Usuario("danilo");
        Usuario tiago = new Usuario("tiago");

        caio.adicionarAmigo(danilo);
        caio.adicionarAmigo(tiago);
        caio.publicar("Olá, essa é uma mensagem!");
    }
}
