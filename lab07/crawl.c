	// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "html.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "url_file.h"

#define BUFSIZE 1024
#define strEQ(g, t) (strcmp ((g), (t)) == 0)

static void setFirstURL (char *, char *);

static ssize_t vertexID (char *str, char **names, size_t N)
{
	for (size_t i = 0; i < N; i++)
		if (strEQ (str, names[i]))
			return (ssize_t) i;
	return -1;
}

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
	//    }
	//    close the opened URL
	//    sleep(1)
	// }
	Queue toDo = newQueue();
	enterQueue(toDo, firstURL);
	//Stack toDo = newStack();
	//pushOnto(toDo, firstURL);
	Graph webURLs = newGraph(maxURLs);
	Set seen = newSet();

	while (!emptyQueue(toDo) && nVertices(webURLs) <= maxURLs) {
		char* nextURL = leaveQueue(toDo);
		if (!(handle = url_fopen (nextURL, "r"))) {
			//fprintf (stderr, "Couldn't open %s\n", next);
			//exit (1);
			continue;
		}
		while (!url_feof (handle)) {
			url_fgets (buffer, sizeof (buffer), handle);
			// fputs(buffer,stdout);
			int pos = 0;
			char result[BUFSIZE];
			//memset (result, 0, BUFSIZE);
			while ((pos = GetNextURL (buffer, nextURL, result, pos)) > 0) {
				if (nVertices(webURLs) < maxURLs || 
				(vertexID(result, webURLs->vertex, webURLs->nV) != -1 
				&& vertexID(nextURL, webURLs->vertex, webURLs->nV) != -1)) {
					addEdge(webURLs, nextURL, result);
				}

				if (isElem(seen, result) == 0 && NormalizeURL(result)) {
					insertInto(seen, result);
					enterQueue(toDo, result);
					printf ("Found: '%s'\n", result);
				}			
				memset (result, 0, BUFSIZE);
			}
		}
		url_fclose (handle);
		free(nextURL);
		sleep (1);
	}

	showGraph(webURLs, 0);
	showGraph(webURLs, 1);
	dropGraph(webURLs);
	dropQueue(toDo);
	//dropStack(toDo);
	dropSet(seen);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
