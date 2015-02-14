/*
 * Puny Browser - The weakest browser around!
 * Copyright (C) 2015 Matthew Carter <m@ahungry.com>
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

/*
 * Start
 */
int main (int argc, char *argv[])
{
  GtkWidget *win, *view;

  gtk_init (&argc, &argv);

  win  = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  view = webkit_web_view_new ();

  g_signal_connect (win, "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  gtk_container_add (GTK_CONTAINER (win), view);

  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (view), "http://example.com");
  webkit_web_view_run_javascript (WEBKIT_WEB_VIEW (view), "alert(1);", NULL, NULL, NULL);

  gtk_widget_show_all (win);

  gtk_main ();

  return 0;
}
