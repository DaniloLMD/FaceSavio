#include "../include/Post.hpp"

Post::Post(int id, std::string texto, std::string username) : id(id), texto(texto), username(username) {}

/**
 * @brief forma e retorna uma imagem com o tamanho desejado
 * @param filePath caminho da imagem
 * @param width largura da imagem
 * @param heigth altura da imagem
 * @return GtkWidget que é um GtkImage
*/
GtkWidget* newScaledImage(const gchar *filePath, gint width, gint height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filePath, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);
    return image;
}

/**
 * @brief adapta uma imagem para as dimensoes desejadas
 * @param filePath caminho da imagem
 * @param width largura da imagem
 * @param heigth altura da imagem
 * @return void
*/
void setScaledImage(GtkImage* image, const gchar *filePath, gint width, gint height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filePath, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(image, pixbuf);
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);
}

