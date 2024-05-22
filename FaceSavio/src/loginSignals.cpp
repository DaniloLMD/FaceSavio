#include <iostream>
#include "../include/loginSignals.hpp"

Interface* interface = NULL;

void connectLoginSignals(void* newInterface){
    interface = (Interface*) newInterface;
    connectHomeSignals(newInterface);
}

void on_login_clicked(){
    GtkStack* stack = GTK_STACK(gtk_builder_get_object(interface->getBuilder(), "stack"));
    loadHomeScreen();
    gtk_stack_set_visible_child_name(stack, "home");   
}
