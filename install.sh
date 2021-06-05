#!/bin/sh

sed s/daduser/$USER/g jokes.c | gcc $(pkg-config --cflags --libs libnotify libcurl) -x c - -o jokesd

mkdir -p ~/bin
cp jokesd ~/bin
mkdir -p ~/.local/share/icons/jokesd/
cp icon.png ~/.local/share/icons/jokesd/
