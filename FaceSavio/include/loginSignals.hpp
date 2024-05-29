#ifndef __LOGIN_SIGNALS_HPP__
#define __LOGIN_SIGNALS_HPP__

#include "Interface.hpp"
#include "homeSignals.hpp"

void loadLoginScreen();

void connectLoginSignals(void* newInterface);
void on_login_clicked();
void on_cadastrar_clicked();

void on_remember_toggled();

void on_name_changed();
void on_name_activate();
void on_password_activate();

#endif