import java.util.ArrayList;

public class GerenciadorNotificacoes {
    private ArrayList<INotificavel> notificaveis = new ArrayList<INotificavel>();
    private Usuario usuario;

    public GerenciadorNotificacoes(Usuario usuario) {
        this.usuario = usuario;
    }

    public void adicinar(INotificavel notificavel) {
        notificaveis.add(notificavel);
    }

    public void notificarTodos(String msg) {
        for (INotificavel notificavel : notificaveis) {
            notificavel.notificar(msg, this.usuario);
        }
    }
}
