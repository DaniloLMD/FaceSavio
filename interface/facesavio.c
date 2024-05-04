#include <gtk/gtk.h>

GtkWidget	*window; //janela principal
GtkWidget	*grid1; //grid escrolavel
GtkWidget	*grids[1000]; //grids que serao adicionadas na scrolavel
GtkBuilder	*builder; //builder do arquivo glade

void usar_estilo () {
    //GtkCssProvider o objeto gtk que guarda o arquivo.css 
    GtkCssProvider *css_provider = gtk_css_provider_new();
    //aqui carregar o provider colocando o objeto que vai receber e o caminho para o arquivo .css
    gtk_css_provider_load_from_path(css_provider, "facesavio.css", 0);
    //carregando de fato o css
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

//redimensiona a imagem para o tamanho desejado e adiciona na grid
void add_scaled_image_to_grid(GtkGrid *grid, const gchar *filename, gint row, gint column, gint width, gint height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);
    gtk_grid_attach(grid, image, column, row, 1, 1);
}

typedef struct post{
	GtkWidget* profile; //foto de perfil
	GtkWidget*  name; //nome do usuario
	GtkWidget* text; //texto do post
	GtkWidget*  image; //imagem do post
}post;

//vetor que armazena os posts que irao para a grid scrollavel
post posts[1000];

// imagens, mensagens e nomes de usuarios que eu cadastrei manualmente pra testar
const int qtd_cadastrados = 3;
char imagens[4][500] = {"imagens/caio.png", "imagens/gauloish.png", "imagens/sabino.png", "imagens/route_02.png"};
char mensagens[4][500] = {"ryan vai virar coach", "1+1 = 3", "busca binaria em dp de segtree", "devia tar fazendo calculo mas to aqui"};
char usuarios[4][500] = {"Caio", "Gauloish", "Sabino", "pokemon map"};

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); //iniciando o gtk
 
	builder = gtk_builder_new_from_file ("facesavio.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	grid1 = GTK_WIDGET(gtk_builder_get_object(builder, "grid1"));

	gtk_window_set_title(GTK_WINDOW(window), "FaceSavio");

	gtk_builder_add_callback_symbols(
		builder,
        "on_window_destroy", G_CALLBACK(gtk_main_quit), //botao de fechar a janela X
		NULL
	);

	gtk_builder_connect_signals(builder, NULL);


	const int qtd_posts = 50; //quantidade de posts a serem carregados

	//dimensoes das foto de perfil 
	const int profile_width = 200;
	const int profile_heigth = 150;

	//gtk_grid_attach (GtkGrid* grid, GtkWidget* child, int column, int row,int width,int height);]

	for(int i = 1; i <= qtd_posts; i++){
		//formando a grid que vai armazenar o novo post
		grids[i] = gtk_grid_new();

		//formando os elementos do novo post
		posts[i].name = gtk_label_new(usuarios[i % qtd_cadastrados]);
		posts[i].text = gtk_label_new(mensagens[i % qtd_cadastrados]);

		//adicionando os elementos do novo post na nova grid
		add_scaled_image_to_grid(GTK_GRID(grids[i]), imagens[i % qtd_cadastrados], 1, 1, profile_width, profile_heigth);
		gtk_grid_attach (GTK_GRID(grids[i]), posts[i].name, 2, 1, 1, 1);
		gtk_grid_attach (GTK_GRID(grids[i]), posts[i].text, 1, 2, 1, 1);

		//adicionando uma nova linha na grid scrollavel
		gtk_grid_insert_row (GTK_GRID(grid1), i+1);
		//adicionando a grid que contem o post na grid scrollavel
		gtk_grid_attach (GTK_GRID(grid1), grids[i], 1, i+1, 1, 1);
		
	}

	usar_estilo(); //carregando o css

	gtk_widget_show_all(window);

	gtk_main(); //mostrando a janela na tela

	return 0;
}
