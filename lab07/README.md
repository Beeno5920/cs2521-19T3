
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 07 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 07 Lab Exercise</span><br/>
    <span class="subheading"></span>
  </header>
<center><table border='0'>
<tr>
<td> <img align='center' src='Pics/webL.jpg'> </td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td align='center'> <span style='font-size:22pt'>Web Crawling and Directed Graphs</span>
</td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td> <img align='center' src='Pics/webR.jpg'> </td>
</tr></table>
</center>


<h2>Objectives</h2>
<ul>
<li>to implement a Web crawler</li>
<li>to build a directed graph structure</li>
</ul>
<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 07 Lab or in the Week 08 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab07 crawl.c</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by Sun 03 November 2019, 17:00</dd>
</dl>

<h2>Background</h2>
<p>
We can view the World Wide Web as a massive directed graph,
where <em>pages</em> (identified by URLs) are the vertices
and <em>hyperlinks</em> (HREFs) are the directed edges.
Unlike the graphs we have studied in lectures, there is not a single
central representation (e.g. adjacency matrix) for all the edges
in the graph of the web; such a data structure would clearly be
way too large to store.
Instead, the "edges" are embedded in the "vertices".
Despite the unusual representation, the Web is clearly a graph, so
the aim of this lab exercise is to build an in-memory graph structure
for a very, very small subset of the Web.
</p>
<p>
<em>Web crawlers</em> are programs that navigate the Web automatically,
moving from page to page, processing each page they visit.
Crawlers typically use a standard graph traversal algorithm to:
</p>
<ul>
<li> maintain a list of pages to visit (a ToDo list) </li>
<li> "visit" the next page by grabbing its HTML content </li>
<li> scanning the HTML to extract whatever features they are interested in </li>
<li> collecting hyperlinks from the visited page, and adding these to the ToDo list </li>
<li> repeating the above steps (until there are no more pages to visit :-) </li>
</ul>
<p>
You need to implement such a crawler, using a collection of supplied
ADTs and a partially complete main program.
Your crawler processes each page by finding any hyperlinks and inserting
the implied edges into a directed <code>Graph</code> ADT based on an adjacency
matrix.
One difference between this <code>Graph</code> ADT and the ones we have
looked at in lectures is that you dynamically add information about
vertices, as well as edges.
The following diagram shows what an instance of the <code>Graph</code> ADT
might look like:
</p>
<center><img src="Pics/web-graph.png"></center>
<p>
The <code>Graph</code> data structure allows for <code>maxV</code> vertices
(URLs), where <code>maxV</code> is supplied when graph is created.
Initially, there are no vertices or edges, but as the crawler
examines the web, it adds the URLs of any pages that it visits and
records the hyperlinks between them.
This diagram shows what a web crawler might have discovered had it
started crawling from the URL <code>http://x.com/index.html</code>, and
so far examined four web pages.
</p>
<p>
If we number the four pages from 0..3, with
</p>
<ul>
<li> page (vertex) 0 being <code>http://x.com/index.html</code>, </li>
<li> page (vertex) 1 being <code>http://x.com/category/index.html</code> </li>
<li> page (vertex) 2 being <code>http://x.com/products.html</code> </li>
<li> page (vertex) 3 being <code>http://x.com/products/abc.html</code> </li>
</ul>
<p>
The <code>vertices</code> array holds the actual URL strings
and also, effectively, provides the mapping between URLs
and vertex numbers.
The <code>edges</code> array is a standard adjacency matrix.
The top row tells us that page 0 has hyperlinks to pages
1 and 2. The second row tells us that page 1 has a hyperlink
back to page 0. The third row similarly shows a hyperlink
from page 2 back to page 0, but also a hyperlink to page 3.
</p>

<h2>Setting Up</h2>
<p>
The files for this lab are available in the ZIP file:
</p>
<pre>
<a target="_blank" href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week07/lab.zip">/web/cs2521/19T3/labs/week07/lab.zip</a>
</pre>
<p>
You should unzip the contents of this into the directory
you're going to use for this lab.
The ZIP file contains:
</p>

<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/crawl.c">crawl.c</a></code> </dt>
<dd>an (incomplete) program that crawls a web site</dd>
<dt><code><a href="files/url_file.c">url_file.c</a></code> <br/>
<code><a href="files/url_file.h">url_file.h</a></code> <br/>
</dt>
<dd>make a webpage behave like a <code>FILE *</code></dd>
<dt><code><a href="files/html.c">html.c</a></code> <br/>
<code><a href="files/html.h">html.h</a></code> <br/>
</dt>
<dd>get URLs from a HTML document</dd>
<dt><code><a href="files/set.h">set.h</a></code> <br/>
<code><a href="files/set.c">set.c</a></code> <br/>
</dt>
<dd>a Set ADT interface and implementation</dd>
<dt><code><a href="files/queue.h">queue.h</a></code> <br/>
<code><a href="files/queue.c">queue.c</a></code> <br/>
</dt>
<dd>a Queue ADT interface and implementation</dd>
<dt><code><a href="files/stack.h">stack.h</a></code> <br/>
<code><a href="files/stack.c">stack.c</a></code> <br/>
</dt>
<dd>a Stack ADT interface and implementation</dd>
<dt><code><a href="files/graph.h">graph.h</a></code> <br/>
<code><a href="files/graph.c">graph.c</a></code> <br/>
</dt>
<dd>a Graph ADT interface and implementation</dd>
<dt><code><a href="files/ts.c">ts.c</a></code> <br/>
<code><a href="files/tq.c">tq.c</a></code> <br/>
<code><a href="files/tk.c">tk.c</a></code> <br/>
<code><a href="files/tg.c">tg.c</a></code> <br/>
</dt>
<dd>simple tests for Set, Queue, Stack, and Graph ADTs</dd>
</dl>
<p>
The only file you need to modify is <code>crawl.c</code>, but you need
to understand at least the interfaces to the functions in the various
ADTs. This is described in comments at the start of each function in
the <code>.c</code> files. You can also see examples of using the ADT
functions in the <code>t?.c</code> files. Note that there's no test file
for the HTML parsing and URL-extracting code, because the supplied
version of <code>crawl.c</code> effectively provides this.
</p>
<p>
Note that HTML parsing code was borrowed from Dartmouth College.
If you looks at the code, it has quite a different style to the
rest of the code. This provides an interesting comparison with
our code.
<p>
The <code>crawl</code> program is used as follows:
</p>
<pre>
<kbd is="sh">./crawl <var>StartingURL</var> <var>MaxURLsInGraph</var></kbd>
</pre>
<p>
The <var>StartingURL</var> tells you which URL to start the
crawl from, and should be of the form <code>http://x.y.z/</code>.
The crawler uses this URL as both the starting point and uses a
normalised version as the base against which to interpret other
URLs.
The <var>MaxURLsInGraph</var> specifies the maximum number
of URLs that can be stored in the <code>Graph</code>.
Once this many URLs have been scanned, the crawling will stop,
or will stop earlier if there are no more URLs left in the ToDo
list.
</p>
<p>
If you compile then run the supplied crawler on the UNSW handbook,
you would see something like:
</p>
<pre>
<kbd is="sh">./crawl http://www.handbook.unsw.edu.au/2017/ 100</kbd>
Found: 'http://www.unsw.edu.au'
Found: 'https://my.unsw.edu.au/'
Found: 'https://student.unsw.edu.au/'
Found: 'http://www.futurestudents.unsw.edu.au/'
Found: 'http://timetable.unsw.edu.au/'
Found: 'https://student.unsw.edu.au/node/62'
Found: 'http://www.library.unsw.edu.au/'
Found: 'http://www.handbook.unsw.edu.au/2017/'
Found: 'http://www.unsw.edu.au/faculties'
Found: 'https://student.unsw.edu.au/node/4431'
Found: 'https://student.unsw.edu.au/node/128'
Found: 'http://www.unsw.edu.au/contacts'
Found: 'http://www.handbook.unsw.edu.au/general/current/SSAPO/previousEditions.html'
Found: 'http://www.handbook.unsw.edu.au/undergraduate/2017/'
Found: 'http://www.handbook.unsw.edu.au/postgraduate/2017/'
Found: 'http://www.handbook.unsw.edu.au/research/2017/'
Found: 'http://www.handbook.unsw.edu.au/nonaward/2017/'
Found: 'http://www.unsw.edu.au/future-students/domestic-undergraduate'
Found: 'http://www.unsw.edu.au/future-students/postgraduate-coursework'
Found: 'http://research.unsw.edu.au/future-students'
Found: 'http://www.international.unsw.edu.au/#1'
Found: 'https://student.unsw.edu.au/node/1334'
Found: 'https://moodle.telt.unsw.edu.au/login/index.php'
Found: 'https://student.unsw.edu.au/node/943'
Found: 'https://apply.unsw.edu.au/'
Found: 'https://student.unsw.edu.au/node/5450'
Found: 'http://cgi.cse.unsw.edu.au/~nss/feest/'
Found: 'http://www.unsw.edu.au/privacy'
Found: 'http://www.unsw.edu.au/copyright-disclaimer'
Found: 'http://www.unsw.edu.au/accessibility'
</pre>
<p>
The supplied crawler simply scans the URL given on the command line,
prints out any URLs that it finds, and then stops.
It is not attempting to traverse any further than the supplied page.
The second command-line argument, which limits the size of the <code>Graph</code>
is effecitvely ignored here, since the supplied code does not build a
<code>Graph</code>; you need to add the code to do this.
</p>
<p>
If you run the supplied "crawler" on <code>http://www.cse.unsw.edu.au</code>,
you don't get very much, because the CSE website recently moved under
the Engineering Faculty system and the above URL is just a redirection
page to the new site. Copying/pasting the redirection URL gives you
more interesting results.
Before you go running the "crawler" on other websites ... DON'T!
See the comments below.
<p>
HTML is a language which is difficult to parse given the way it is
frequently used, and the <code>GetNextURL()</code> make some approximations
which, while they wouldn't be acceptable in a <em>real</em> Web crawler,
are OK for this lab.
</p>

<h2>Exercise</h2>
<p>
Your task is to modify <code>crawl.c</code> so that it follows any URLs
it finds and builds a <code>Graph</code> of the small region of the Web
that it traverses before bumping in to the <code>MaxURLsInGraph</code> limit.
</p>
<p>
<b>Important:</b> running crawlers outside the UNSW domain is
problematic. Running crawlers that make very frequent URL requests
is problematic. So ...
</p>
<ul>
<li> DO NOT run your crawler on any website outside UNSW </li>
<li> YOU MUST include a delay (<code>sleep(1)</code>) between each URL access</li>
</ul>
<p>
If you don't do the above, there's a chance that angry sites that are
being hammered by your crawler will block UNSW from future access to
those sites. Breaches of the above will result in disciplinary action.
</p>
<p>
Your crawler can do either a breadth-first or depth-first search,
and should follow roughly the graph traversal strategy described
in lectures and tutes:
</p>
<pre>
add firstURL to the ToDo list
initialise Graph to hold up to maxURLs
initialise set of Seen URLs
while (ToDo list not empty and Graph not filled) {
	grab Next URL from ToDo list
	if (not allowed) continue
	foreach line in the opened URL {
		foreach URL on that line {
			if (Graph not filled  or both URLs in Graph)
				add an edge from Next to this URL
			if (this URL not Seen already) {
				add it to the Seen set
				add it to the ToDo list
			}
		}
	}
	close the opened URL
	sleep(1)
}
</pre>
<p>
This does not give all the details. You need to work them out yourself,
based on the supplied ADT functions and your understanding of
generic graph traversal.
If you use a <code>Stack</code> for the ToDo list,
you'll do a depth-first search.
If you use a <code>Queue</code> for the ToDo list,
you'll do a breadth-first search.
</p>
<p>
A couple more things to note:
</p>
<ul>
<li> <code>(not allowed)</code> refers to not using URLs outside UNSW </li>
<li> the <code>ToDo list</code> is a <code>Stack</code> or <code>Queue</code> rather than a List</li>
<li> if you don't include the <code>sleep(1)</code> you will smash whatever web server you access
</ul>
<p>
If you test the crawler out on <code>www.cse.unsw.edu.au</code>,
you don't get particularly interesting results, because you'll
build a large adjacency matrix, most of which is empty, before
you bump into <code>MaxURLsInGraph</code>.
To assist in doing some feasible crawling and getting some more
interesting output, I have set up a tiny set of self-contained
web pages that you can crawl, starting from:
</p>
<pre>
<kbd is="sh">./crawl https://www.cse.unsw.edu.au/~cs2521/19T3/mini-web/ 30</kbd>
</pre>
<p>
You should use the output of <code>showGraph()</code> to check whether
you are building a plausible <code>Graph</code>.
Note that <code>showGraph()</code> has two modes:
</p>
<ul>
<li> <code>showGraph(<em>g</em>,0)</code> shows the URL for each vertex, followed by an
indented list of connected vertices </li>
<li> <code>showGraph(<em>g</em>,1)</code> shows just the adjacency matrix in a very
compact form; it does not show the stored URLs </li>
</ul>

<h2>Challenges</h2>
<p>
There are several aspects of the crawler that you could look to improve:
</p>
<ul>
<li><p>
The existing crawler grabs all sorts of URLs that do not represent
Web pages. Modify the code so that it filters out non-HTML output.
</p></li>
<li><p class="red">
The supplied <code>GetNextURL()</code> function does a reasonable job
on finding URLs, but doesn't handle relative URLs. Find online
or write your own, or modify the existing code, to make a new
<code>GetNextURL()</code> that handles a wider range of URLs.
<li><p>
Modify <code>showGraph()</code> so that it can (also) produce output
(JSON) that could be fed into a graph drawing tool such as
<a href="http://sigmajs.org">sigmajs</a>, to produce beautiful
graph diagrams.
</p></li>
</ul>

<h2>Demonstration/Submission</h2>
<p>
Once you have completed the above task,
you should demonstrate your work to your tutor.
Ideally, you would do this in the Week 07 Lab.
If you can't finish the tasks in the lab,
you have until midnight on Sunday to complete and submit them.
You should then demonstrate your work
at the start of the Week 08 Lab;
your tutor will give you feedback
and award a mark.
</p>

<p>
Have fun, <i>jas</i>
</p>
<footer><p>
  <strong>COMP2521 19T3: Data Structures and Algorithms</strong>
  is brought to you by <br />
  the <a href="https://www.cse.unsw.edu.au/">School of Computer Science and Engineering</a>
  at the <a href="https://www.unsw.edu.au/">University of New South Wales</a>, Sydney.<br />
  For all enquiries, please email the class account at
  <a href="mailto:cs2521@cse.unsw.edu.au">cs2521@cse.unsw.edu.au</a><br />
  <small>CRICOS Provider 00098G</small>
</p></footer><script src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/latest.js?config=TeX-MML-AM_CHTML" async></script></body>
</html>
