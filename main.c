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
// https://webkitgtk.org/reference/webkit2gtk/stable/WebKitWebView.html

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

/* gboolean */
/* scroll(const Arg *arg) */
/* { */
/*     GtkAdjustment *adjust = (arg->i & OrientationHoriz) ? client.gui.adjust_h : client.gui.adjust_v; */
/*     int max = gtk_adjustment_get_upper(adjust) - gtk_adjustment_get_page_size(adjust); */
/*     float val = gtk_adjustment_get_value(adjust) / max * 100; */
/*     int direction = (arg->i & (1 << 2)) ? 1 : -1; */
/*     unsigned int count = client.state.count; */

/*     if ((direction == 1 && val < 100) || (direction == -1 && val > 0)) { */
/*         if (arg->i & ScrollMove) */
/*             gtk_adjustment_set_value(adjust, gtk_adjustment_get_value(adjust) + */
/*                 direction *      /\* direction *\/ */
/*                 ((arg->i & UnitLine || (arg->i & UnitBuffer && count)) ? (scrollstep * (count ? count : 1)) : ( */
/*                     arg->i & UnitBuffer ? gtk_adjustment_get_page_size(adjust) / 2 : */
/*                     (count ? count : 1) * (gtk_adjustment_get_page_size(adjust) - */
/*                         (gtk_adjustment_get_page_size(adjust) > pagingkeep ? pagingkeep : 0))))); */
/*         else */
/*             gtk_adjustment_set_value(adjust, */
/*                 ((direction == 1) ?  gtk_adjustment_get_upper : gtk_adjustment_get_lower)(adjust)); */
/*         update_state(); */
/*     } */
/*     return TRUE; */
/* } */

int
main (int argc, char *argv[])
{
  GtkWidget *win, *view;
  GtkWidget *button;
  GtkWidget *button_box;

  gtk_init (&argc, &argv);

  // https://webkitgtk.org/reference/webkit2gtk/stable/WebKitWebView.html#webkit-web-view-set-settings
  // Option to send keys?
  win  = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  view = webkit_web_view_new ();

  g_signal_connect (win, "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  g_signal_connect (view, "key-press-event",
                    G_CALLBACK (on_key_press),
                    NULL);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);

  gtk_container_add (GTK_CONTAINER (win), view);
  gtk_container_add (GTK_CONTAINER (win), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (view), "http://ahungry.com/");
  webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (view), "alert(1);", NULL, NULL, NULL);

  gtk_widget_show_all (win);

  gtk_main ();

  return 0;
}

// Return TRUE to stop signal, FALSE to propagate it to browser
// /usr/include/gtk-3.0/gdk/gdkkeysyms.h
gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  int i = 0;
  char ch;
  char content[1024];
  FILE *fp;

  switch (event->keyval)
    {
    case GDK_KEY_p:
      printf ("You pushed p\n");
      webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (widget), "alert(2);", NULL, NULL, NULL);
      break;

    case GDK_KEY_k:
      printf ("You pushed k\n");
      webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (widget), "window.scrollTo(window.scrollX, window.scrollY - 50);", NULL, NULL, NULL);
      break;

    case GDK_KEY_j:
      printf ("You pushed j\n");
      webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (widget), "window.scrollTo(window.scrollX, window.scrollY + 50);", NULL, NULL, NULL);
      break;

    case GDK_KEY_o:
      fp = fopen("lol.js", "r");

      while ((ch = fgetc (fp)) != EOF)
        {
          content[i++] = ch;
        }

      content[i] = '\0';
      fclose (fp);

      // https://stackoverflow.com/questions/6796191/how-to-send-key-events-to-webkit-webview-control?rq=1
      printf ("You pushed o, which means run lol.js on the fly...\n");
      webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (widget), content, NULL, NULL, NULL);
      break;
    }

  return false;
}
