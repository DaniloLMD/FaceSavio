#include <gtk/gtk.h>

GtkBuilder* builder;
GtkWidget* window;

void usar_estilo () {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "facesavio.css", 0);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}


int main(int argc, char* argv[]){
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("facesavio.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    usar_estilo();
    gtk_widget_show(window);
    gtk_main();
    
        
    
    return 0;
}