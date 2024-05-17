public class Usuario implements INotificavel {
    private String nome;
    private GerenciadorNotificacoes gerenciadorNotificacoes = new GerenciadorNotificacoes(this);

    public Usuario(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return this.nome;
    }

    public void publicar(String msg) {
        System.out.println("Eu " + this.nome + ", publiquei a mensagem '" + msg + "'.");
        gerenciadorNotificacoes.notificarTodos(msg);
    }

    public void adicionarAmigo(Usuario usuario) {
        gerenciadorNotificacoes.adicionar(usuario);
    }

    public void notificar(String msg, Usuario autor) {
        System.out.println("Sou o usuário " + this.nome + " e o usuário " + autor.getNome() + " publicou a mensagem: '" + msg + "'.");
    }

}
