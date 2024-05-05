#include <gtk/gtk.h>
#include <iostream>
using namespace std;

GtkBuilder* builder;
GtkWidget* window;
GtkTextView* textView;

void activateCSS () {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "facesavio.css", 0);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void on_textBufferPost_insert_text(GtkTextBuffer *buffer) {
    // Conta o numero de linhas no buffer de texto e
    // Verifica se o número de linhas excede o limite permitido
    gint line_count = gtk_text_buffer_get_line_count(buffer);
    const int MAX_LINES = 10;
    if (line_count > MAX_LINES) {
        // Se exceder, cancela a inserção do texto
        g_signal_stop_emission_by_name(buffer, "insert-text");
    }

    // Conta o numero de colunas no buffer de texto e
    // Verifica se o número de colunas excede o limite permitido
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    // Obtém o texto do buffer de texto
    string text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    const int MAX_COLUMNS = 100;

    int caracteres = 0;
    for(char c: text){
        if(c == '\n'){
            caracteres = 0;
        }
        else{
            caracteres++;
        }
        if(caracteres > MAX_COLUMNS){
            g_signal_stop_emission_by_name(buffer, "insert-text");
        }
    }
}

int main(int argc, char* argv[]){
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("facesavio.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    textView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textViewPost"));

    gtk_builder_add_callback_symbols(
		builder,
        "on_main_window_destroy",           G_CALLBACK(gtk_main_quit),
        "on_textBufferPost_insert_text",    G_CALLBACK(on_textBufferPost_insert_text),
 		NULL
	);
    
    gtk_builder_connect_signals(builder, NULL);

    activateCSS();

    gtk_widget_show(window);
    gtk_main();
    
        
    return 0;
}