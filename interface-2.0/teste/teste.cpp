#include <gtk/gtk.h>
#include <iostream>
using namespace std;

GtkBuilder* builder;
GtkWidget* window;
GtkTextView* textView;

void usar_estilo () {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "teste.css", 0);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void on_botaoClickMe_clicked(){
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    // Obtém o início e o fim do buffer de texto
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    // Obtém o texto do buffer de texto
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    // Imprime o texto
    g_print("Texto lido:\n%s\n", text);
    // Libera a memória alocada para o texto
    g_free(text);
}

void on_textViewPost_check_resize(){
    cout << "oi\n";
}

void on_textViewPost_add(){
    cout << "tchau\n";
}

int main(int argc, char* argv[]){
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("teste.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    textView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textViewPost"));

    gtk_builder_add_callback_symbols(
		builder,
        "on_main_window_destroy",               G_CALLBACK(gtk_main_quit),
        "on_botaoClickMe_clicked",              G_CALLBACK(on_botaoClickMe_clicked),
        "on_textViewPost_check_resize",         G_CALLBACK(on_textViewPost_check_resize),
        "on_textViewPost_add",                  G_CALLBACK(on_textViewPost_add),
 		NULL
	);

    gtk_builder_connect_signals(builder, NULL);
    
    usar_estilo();
    gtk_widget_show(window);
    gtk_main();
    
        
    
    return 0;
}