#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string {
	char *ptr;
	size_t len;
};

void init_string(struct string *s) {
	s->len = 0;
	s->ptr = malloc(s->len + 1);
	if (s->ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
	size_t new_len = s->len + size * nmemb;
	s->ptr = realloc(s->ptr, new_len + 1);
	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->ptr + s->len, ptr, size * nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size * nmemb;
}

char *get_joke(void) {
	CURL *curl = curl_easy_init();
	if (curl) {
		CURLcode res;
		struct string joke;
		init_string(&joke);
		curl_easy_setopt(curl, CURLOPT_URL,
				 "https://icanhazdadjoke.com/");
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.7.0");
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "*/*");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &joke);
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		return joke.ptr;
	}
}
