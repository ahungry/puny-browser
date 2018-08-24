/*
 * Puny Browser - The weakest browser around!
 * Copyright (C) 2015, 2018 Matthew Carter <m@ahungry.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// https://developer.gnome.org/gtk3/stable/ch01s04.html#id-1.2.3.12.10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <X11/Xlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <unistd.h>
#include <errno.h>
#include <webkit2/webkit2.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);

static void
print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}

int
main (int argc, char *argv[])
{
  GtkWidget *win, *view;
  GtkWidget *button;
  GtkWidget *button_box;

  gtk_init (&argc, &argv);

  win  = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  view = webkit_web_view_new ();

  g_signal_connect (win, "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  g_signal_connect (win, "key-press-event",
                    G_CALLBACK (on_key_press),
                    NULL);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);

  gtk_container_add (GTK_CONTAINER (win), view);
  gtk_container_add (GTK_CONTAINER (win), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (view), "http://ahungry.com/eqauctions-live");
  webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (view), "alert(1);", NULL, NULL, NULL);

  gtk_widget_show_all (win);

  gtk_main ();

  return 0;
}

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval)
    {
    case GDK_KEY_p:
      printf ("You pushed p\n");
      // webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (widget), "alert(2);", NULL, NULL, NULL);
      break;
    }

  return true;
}
