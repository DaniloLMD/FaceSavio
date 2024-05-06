#include <iostream>
#include "../include/homeSignals.hpp"

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
     std::string text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
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

