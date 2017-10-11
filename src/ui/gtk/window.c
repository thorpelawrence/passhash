#include <gtk/gtk.h>
#include <string.h>
#include "window.h"
#include "../../hashing/argon2.h"
#include "../../hashing/evp.h"

struct Window {
    GtkWidget *window; 
    GtkWidget *grid;
    GtkWidget *password_label;
    GtkWidget *hash_label;
    GtkWidget *hash_value_label;
    GtkWidget *password_entry;
    GtkWidget *algorithm_combobox;
} window;

enum Algorithms {
    argon2,
    md5,
    sha1,
    sha256
};

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static void update_hash(char *password) {
    int selected_algorithm = gtk_combo_box_get_active(GTK_COMBO_BOX(window.algorithm_combobox));
    if (selected_algorithm == argon2) {
        char hash[128];
        hash_password_argon2(password, hash);
        gtk_label_set_text(GTK_LABEL(window.hash_value_label), hash);
    }
    else if (selected_algorithm == md5) {
        unsigned char hash[32];
        digest_message("MD5", (unsigned char*)password, strlen(password), hash);
        gtk_label_set_text(GTK_LABEL(window.hash_value_label), (char*)hash);
    }
    else if (selected_algorithm == sha1) {
        unsigned char hash[40];
        digest_message("SHA1", (unsigned char*)password, strlen(password), hash);
        gtk_label_set_text(GTK_LABEL(window.hash_value_label), (char*)hash);
    }
    else if (selected_algorithm == sha256) {
        unsigned char hash[64];
        digest_message("SHA256", (unsigned char*)password, strlen(password), hash);
        gtk_label_set_text(GTK_LABEL(window.hash_value_label), (char*)hash);
    }
}

static void password_changed(GtkEditable *editable, gpointer data) {
    char *password = gtk_editable_get_chars(editable, 0, -1);
    update_hash(password);
}

static void algorithm_changed(GtkComboBox *combo, gpointer data) {
    char *password = gtk_editable_get_chars(GTK_EDITABLE(window.password_entry), 0, -1);
    update_hash(password);
}

int create_window() {
    gtk_init(NULL, NULL);

    window.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window.window), "Passhash");
    gtk_window_set_default_size(GTK_WINDOW(window.window), 800, 120);
    g_signal_connect(window.window, "destroy", G_CALLBACK(destroy), NULL);

    window.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window.window), window.grid);
    g_object_set(window.grid, "margin", 15, NULL);
    gtk_grid_set_column_spacing(GTK_GRID(window.grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(window.grid), 5);    

    window.password_label = gtk_label_new("Enter password:");
    gtk_widget_set_hexpand(window.password_label, TRUE);
    gtk_widget_set_vexpand(window.password_label, TRUE);
    gtk_grid_attach(GTK_GRID(window.grid), window.password_label, 0, 0, 1, 1);

    window.hash_label = gtk_label_new("Password hash: ");
    gtk_widget_set_hexpand(window.hash_label, TRUE);
    gtk_widget_set_vexpand(window.hash_label, TRUE);
    gtk_grid_attach(GTK_GRID(window.grid), window.hash_label, 0, 2, 2, 1);

    window.hash_value_label = gtk_label_new(NULL);
    gtk_widget_set_hexpand(window.hash_value_label, TRUE);
    gtk_widget_set_vexpand(window.hash_value_label, TRUE);
    gtk_label_set_justify(GTK_LABEL(window.hash_value_label), GTK_JUSTIFY_CENTER);
    gtk_label_set_selectable(GTK_LABEL(window.hash_value_label), TRUE);
    gtk_grid_attach(GTK_GRID(window.grid), window.hash_value_label, 0, 3, 2, 1);

    window.password_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(window.password_entry), 0);
    gtk_widget_set_hexpand(window.password_entry, TRUE);
    gtk_widget_set_vexpand(window.password_entry, TRUE);
    gtk_grid_attach(GTK_GRID(window.grid), window.password_entry, 1, 0, 1, 2);
    g_signal_connect(window.password_entry, "changed", G_CALLBACK(password_changed), NULL);

    window.algorithm_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(window.algorithm_combobox), "Argon2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(window.algorithm_combobox), "MD5");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(window.algorithm_combobox), "SHA1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(window.algorithm_combobox), "SHA256");
    gtk_combo_box_set_active(GTK_COMBO_BOX(window.algorithm_combobox), 0);
    gtk_grid_attach(GTK_GRID(window.grid), window.algorithm_combobox, 0, 1, 1, 1);
    g_signal_connect(window.algorithm_combobox, "changed", G_CALLBACK(algorithm_changed), NULL);

    gtk_widget_show_all(window.window);

    gtk_main();

    return 0;
}
