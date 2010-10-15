#include <stdio.h>

#include "lj_dbus.c"

int
main (int argc, char **argv)
{
	JamDBus *jd;
	GList *list;
	MediaPlayer *player;
	GError *error = NULL;
	gchar *music;

	/* init.c */
	g_type_init ();

	jd = lj_dbus_new();
	if (!lj_dbus_mpris_update_list(jd, &error)) {
		g_printerr("Error: %s\n", error->message);
		g_error_free(error);
	} else {
		for (list = g_list_first(jd->player); list; list = g_list_next(list)) {
			player = (MediaPlayer *) list->data;
			printf("'%s' '%s'\n", player->name, player->dest);
			if (player->version)
				printf("Version of player: %s\n", player->version);
			jd->player = list;
			lj_dbus_mpris_update_info(jd, jd->player, &error);
			if (error) {
				g_printerr("Error: %s\n", error->message);
				g_error_free(error);
				error = NULL;
				continue;
			}

			player = (MediaPlayer *) jd->player->data;
			printf("%d '%s' '%s' '%s'\n",
				player->info.status,
				player->info.artist,
				player->info.album,
				player->info.title);
		}

		music = lj_dbus_mpris_current_music(jd, &error);
		if (error) {
			g_printerr("Error: %s\n", error->message);
			g_error_free(error);
		} else {
			printf("Now playing: %s\n", music);
		}
		g_free(music);
	}

	lj_dbus_close(jd);
	return 0;
}

