#include "jokes.h"
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int timeout = 600;
	char *ptr;
	if (argc >= 3 && strncmp(argv[1], "-t", 16) == 0)
		timeout = 60 * strtol(argv[2], &ptr, 0);

	pid_t id = fork();

	if (id < 0) {
		fprintf(stderr, "failed to fork\n");
		exit(1);
	}

	else if (id == 0) {
		while (1) {
			char name[] = "jokesd";
			notify_init(name);
			notify_set_app_name("jokes");

			NotifyNotification *joke;
			char *random_joke = get_joke();
			joke = notify_notification_new(
			    "dad jokez", random_joke,
			    "/home/daduser/.local/share/icons/jokesd/icon.png");
			notify_notification_set_category(joke, "jokes");
			notify_notification_set_timeout(joke, 5000);
			notify_notification_set_urgency(joke,
							NOTIFY_URGENCY_NORMAL);

			GError *error = NULL;
			notify_notification_show(joke, &error);

			sleep(timeout);
		}
	}

	else {
		printf("pid: %d\n", id);
	}

	return 0;
}
