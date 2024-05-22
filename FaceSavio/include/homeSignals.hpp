#ifndef __HOME_SIGNALS_HPP__
#define __HOME_SIGNALS_HPP__

#include "Interface.hpp"

void connectHomeSignals(void* newInterface);

void on_textBufferPost_insert_text(GtkTextBuffer *buffer);

void on_buttonPost_clicked(void* interfaceStruct);

void on_homeButton_clicked();

void showPosts(bool resetar = true);

void limparGridPosts();

#endif