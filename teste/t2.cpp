#include <gtk/gtk.h>
#include <functional>

class MyClass {
public:
    MyClass() {
        // Configurar GTK e criar o text buffer
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);

        // Conectar o callback usando uma lambda
        g_signal_connect_data(buffer, "changed", G_CALLBACK(+[](GtkTextBuffer *buffer, gpointer user_data) {
            // Converter o ponteiro user_data de volta para MyClass*
            MyClass *self = static_cast<MyClass*>(user_data);
            self->on_textBuffer_changed(buffer);
        }), this, NULL, G_CONNECT_AFTER);

        gtk_container_add(GTK_CONTAINER(window), gtk_text_view_new_with_buffer(buffer));
        gtk_widget_show_all(window);

        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    }

    // Método que queremos chamar
    void on_textBuffer_changed(GtkTextBuffer *buffer) {
        g_print("Text buffer changed\n");
    }
};

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    MyClass myClass;

    gtk_main();

    return 0;
}
