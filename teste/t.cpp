#include <gtk/gtk.h>
#include <iostream>

class MyClass {
public:
    MyClass() {
        // Configurar GTK e criar o text buffer
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        
        // Conectar o callback usando a função estática
        g_signal_connect(buffer, "changed", G_CALLBACK(static_on_textBuffer_changed), this);
        
        gtk_container_add(GTK_CONTAINER(window), gtk_text_view_new_with_buffer(buffer));
        gtk_widget_show_all(window);
        
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    }

    // Método que queremos chamar
    void on_textBuffer_changed(GtkTextBuffer *buffer) {
        g_print("Text buffer changed\n");
    }

private:
    // Função estática que chamará o método da instância
    static void static_on_textBuffer_changed(GtkTextBuffer *buffer, gpointer user_data) {
        MyClass *self = static_cast<MyClass*>(user_data);
        self->on_textBuffer_changed(buffer);
    }
};

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    MyClass myClass;
    
    gtk_main();
    
    return 0;
}
