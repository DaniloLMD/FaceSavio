#include <gtk/gtk.h>
#include <stdio.h>
#define MAX_LINES 5

// Função chamada quando a janela é fechada
void on_window_closed(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

// Função chamada quando o texto é inserido no buffer de texto
void on_insert_text(GtkTextBuffer *buffer, GtkTextIter *location, gchar *text, gint len, gpointer data) {
    printf("eai!\n");
    // Conta o número de linhas no buffer de texto
    gint line_count = gtk_text_buffer_get_line_count(buffer);

    // Verifica se o número de linhas excede o limite permitido
    if (line_count > MAX_LINES) {
        // Se exceder, cancela a inserção do texto
        g_signal_stop_emission_by_name(buffer, "insert-text");
    }
}

int main(int argc, char *argv[]) {
    // Inicializa o GTK
    gtk_init(&argc, &argv);

    // Cria uma nova janela
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Limitar Linhas no TextView");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    // Cria um GtkTextView
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR); // Define quebra de palavras e caracteres

    // Obtém o buffer de texto associado ao GtkTextView
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Conecta-se ao sinal "insert-text" do buffer de texto
    g_signal_connect(buffer, "insert-text", G_CALLBACK(on_insert_text), NULL);

    gtk_container_add(GTK_CONTAINER(window), text_view);

    // Exibe tudo
    gtk_widget_show_all(window);

    // Inicia o loop principal
    gtk_main();

    return 0;
}
