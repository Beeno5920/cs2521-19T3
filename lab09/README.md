
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 09 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 09 Lab Exercise</span><br/>
    <span class="subheading"></span>
  </header>
<center><table border='0'>
<tr>
<td> <img align='center' width="130px" src='Pics/map.png'> </td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td align='center'> <span style='font-size:22pt'>Map of Victorian Europe</span>
</td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td> <img align='center' width="130px" src='Pics/map.png'> </td>
</tr></table>
</center>

<h2>Objectives</h2>
<ul>
<li>to manipulate a Graph ADT using adjacency lists</li>
</ul>
<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 09 Lab or in the Week 10 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab09 Map.c</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by Sun 17 November 2019, 17:00</dd>
</dl>

<p>

<h2>Background</h2>
<p>
In this lab we represent the map of Victorian Europe as a graph using an <i>adjacency list</i>
representation.

<!--
<p>
A major part of <i>Assignment-2</i>
involves moving around Victorian Europe.
For the lab this week, we are using one possible representation
of the map of Europe that will be used in the assignment.
The lab represents the map as a graph using an <i>adjacency list</i>
representation.
-->

<p>
The <strong>vertices</strong> in this graph are places (cities, castles, hospitals and seas)
and each is identified by a unique integer value (a location ID).
Each vertex is a node containing the location ID, the name of
the place (both in full and using a two character abbreviation),
and the type of place (LAND or SEA).

<p>
The <strong>edges</strong> in the graph are labelled with the kind of transport (ROAD, RAIL
or BOAT) that exists between the places at either end of the edge.
Edges are non-directional, and each edge is stored twice (an edge between
<i>(v,w)</i> is stored in the adjacency lists for both <i>v</i> and <i>w</i>).


<center><img src="https://cgi.cse.unsw.edu.au/~cs2521/19t3/labs/week09/Pics/map.png"></center>

<p>
Note that the graph representation we have provided for the lab is
only one possibility.
You must use this representation for the lab.
This representation is just to get you started, to get you thinking,
and also to practice using adjacency lists.

<h2>Setting Up</h2>
<p>
Set up a directory for this lab under your <code>cs2521/labs</code> directory,
change into that directory, and run the following command:

<pre><kbd is="sh">unzip /web/cs2521/19T3/labs/week09/lab.zip</kbd></pre>
<p>
If you're working at home, download <code><a href="lab.zip">lab.zip</a></code>
and then work on your local machine.

<p>
If you've done the above correctly,
you should now find the following files in the directory:

<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/Places.h">Places.h</a></code> </dt>
<dd>interface to Places ADT</dd>
<dt><code><a href="files/Places.c">Places.c</a></code> </dt>
<dd>implementation of Places ADT</dd>
<dt><code><a href="files/Map.h">Map.h</a></code> </dt>
<dd>interface to Map/graph ADT</dd>
<dt><code><a href="files/Map.c">Map.c</a></code> </dt>
<dd>almost complete implementation of Map ADT</dd>
<dt><code><a href="files/pl.c">pl.c</a></code> </dt>
<dd>main program to check the Places ADT (<tt>nameToID</tt>, <tt>abbrevToID</tt>)</dd>
<dt><code><a href="files/euro.c">euro.c</a></code> </dt>
<dd>main program to test the Map ADT (<tt>addLink</tt>)</dd>
<dt><code><a href="files/conn.c">conn.c</a></code> </dt>
<dd>main program to test <em>your</em> mods to the Map ADT (<tt>connections</tt>)</dd>
<dt><code><a href="files/euro.txt">euro.txt</a></code> </dt>
<dd>expected output from the <tt>euro</tt> program</dd>
<dt><code><a href="files/links.txt">links.txt</a></code> </dt>
<dd>a text representation of the edges in the Map/graph</dd>
</dl>
<!--
<p>
The <code>Places.*</code> and <code>Map.*</code> files are the same as the ones
supplied for The View phase of the assignment, except that the <code>Map</code>
ADT has one extra function <code>connections()</code>.
-->

<p>
Read the above files to make sure that you understand the interfaces to and
existing implementations of these ADTs.
For example, the <code>Places</code> ADT defines a number of types: <code>LocationID</code>
(a unique location ID), <code>PlaceType</code> (whether a place is on land or is a
body of water), <code>TransportID</code> (modes of transport between places).
It also defines a set of values for each of these types.

<p>
For this lab, you will be required to add code to complete the function
<code>connections()</code> in <code>Map.c</code>.
The three programs (<code>pl.c</code>, <code>euro.c</code> and <code>conn.c</code>)
are supplied as test-beds for the function <code>connections()</code> that
you need to write, and you don't need to modify these programs.
However, it would be useful to read them find out how they invoke
the <code>connections()</code> and how they use the function return values.


<p>
In our map, we know the following information about each place:

<ul>
<li> its location ID (a number in the range 0 .. <code>NUM_PLACES</code>-1)
<li> its full name (e.g. "London", "North Sea" or "Castle Dracula")
<li> its two-character abbreviation (e.g. "LO", "NS", "CD")
<li> whether it's located on the land or is a body of water
</ul>

<p>
Places are uniquely identified by their LocationID, and place information
is stored in a private array of <code>Place</code> structs called <code>Places</code>.
Users of this ADT do not know about the internal structure of this array;
they access information about places via some interface functions:

<ul>
<li> <code>idToName(int)</code> takes a location ID and returns the place's full name</li>
<li> <code>idToType(int)</code> takes a location ID and returns the place's location (<code>LAND</code> or <code>SEA</code></li>
<li> <code>nameToID(char *)</code> takes a place's name and returns its location ID</li>
<li> <code>abbrevToID(char *)</code> takes a place's two-char abbreviation and returns its location ID</li>
</ul>

<p>
The functions that take a location ID as parameter, check whether the ID
is valid and fail an <code>assert</code> if it's not
The functions that take strings as parameters return a special location ID
<code>NOWHERE</code> if the string is not the name or abbreviation of any
known place.
Strings are matched in a case-sensitive manner, so that "london"
would <strong>not</strong> be recognised as being the same as "London".

<p>
The program <code>pl</code> (code in <code>pl.c</code>) is a test bed for
the functions that extract information from the <code>Places</code> table.
Some example of how the <code>pl</code> program might be used:

<pre>
<span class="comment"># if the argument is a full place name, it prints the ID</span>
<kbd is="sh">./pl London</kbd>
London has ID 39
<kbd is="sh">./pl Zagreb</kbd>
Zagreb has ID 69
<span class="comment"># if the argument is an abbreviation, it prints the full name and ID</span>
<kbd is="sh">./pl LO</kbd>
LO is London (39)
<span class="comment"># the quotes are necessary if using names which contain spaces</span>
<kbd is="sh">./pl "North Sea"</kbd>
North Sea has ID 48
<kbd is="sh">./pl "Castle Dracula"</kbd>
Castle Dracula has ID 17
<span class="comment"># if you don't use quotes, ./pl only sees the first word</span>
<kbd is="sh">./pl Castle Dracula</kbd>
Invalid place 'Castle'
<span class="comment"># using a valid abbreviation</span>
<kbd is="sh">./pl CD</kbd>
CD is Castle Dracula (17)
<span class="comment"># using an invalid abbreviation</span>
<kbd is="sh">./pl XX</kbd>
Invalid place 'XX'
<span class="comment"># using an invalid place name</span>
<kbd is="sh">./pl Hello</kbd>
Invalid place 'Hello'
<span class="comment"># remember that name matching is case-sensitive</span>
<kbd is="sh">./pl london</kbd>
Invalid place 'london'
</pre>

<p>
In the <code>Map</code>, edges are <em>non-directional</em> and <em>labelled</em>.
When the <code>addLink()</code> function in <code>Map.c</code> adds an edge from A to B
with transport type T, it also adds an edge from B to A with type T.
This reflects the fact that if there is a road from Rome to Florence, then
there is also a road from Florence to Rome.
Also, you can have multiple edges between a given pair of places if they are
labelled with different transport types.
This reflects the fact that there may be be both a road and rail link between
two cities (e.g. Rome and Florence).

<p>
The <code>euro</code> program (code in <code>euro.c</code>) displays the links
in the Map, although admittedly not in a particularly attractive format.
You can use it to check the output from the <code>conn</code> program.


<h2>Exercise: <span class="h2tt">connections()</span></h2>
<p>
In this lab, you are to implement the following function 
which returns the links (if any) between two places.

<p>
The function:

<pre>
int connections(Map map, LocationID start, LocationID end, TransportID ways[])
</pre>

<p>
uses the Map to work out all of the different types of transport
that exist as direct connections between the two specified locations,
as well as any sea connections that you could use to move from one
to the other.
It sets one value in the <code>ways[]</code> array for each connection
and returns the number of connections that it found (and placed in the
array).
Naturally, it first checks the validity of its parameters (and fails
<code>assert</code>s if they're not valid).

<p>Notes:
<ul>
<li><p>
a sea connection involves moving onto the sea and then moving
to the destination; it has connection type <code>BOAT</code>
</p></li>
<li><p class="red">
<em>sea connections</em> (from one port city to another on the same
sea) are unusual in that they involve two graph edges; all other
connections in this exercise involve a single edge
</p></li>
<li><p>
you are required to find direct edges between the two locations,
and also to determine whether the locations are both port cities
on the same sea (and count that as a sea connection of type <code>BOAT</code>)
</p></li>
<li><p>
the <code>ways[]</code> array is supplied by the caller,
who must allocate sufficient space
</p></li>
</ul>
<p>
Clearly, the maximum number edges that can exist between two places
is determined by the number of transportation types.

<p>
Once you have implemented the <code>connections()</code> function, you
can test it using the <code>conn</code> program, which takes the names
(or abbreviations) of two places and displays a list of all the
connections between them. It gets the list by calling the
<code>connections()</code> function.
Some examples on how to test your <code>connections()</code> function
using the <code>conn</code> program are below.
Make sure that you conduct more extensive tests than just these
(your tutor will ask to see your tests).

<pre>
<span class="comment"># both road and rail ... order doesn't matter</span>
<kbd is="sh">./conn London Manchester</kbd>
Between London and Manchester ...
Rail connection
Road connection
<span class="comment"># only way to get into the Channel from London is by boat</span>
<kbd is="sh">./conn London "English Channel"</kbd>
Between London and English Channel ...
Boat connection
<span class="comment"># from London to rest of Europe is typically via Le Havre</span>
<kbd is="sh">./conn "Le Havre" "English Channel"</kbd>
Between Le Havre and English Channel ...
Boat connection
<span class="comment"># direct road connection but no direct rail</span>
<kbd is="sh"> ./conn Leipzig Hamburg</kbd>
Between Leipzig and Hamburg ...
Road connection
<span class="comment"># direct rail connection but no direct road</span>
<kbd is="sh">./conn Paris Marseilles</kbd>
Between Paris and Marseilles ...
Rail connection
<span class="comment"># port cities are connected to their sea by boat</span>
<kbd is="sh">./conn Marseilles "Mediterranean Sea"</kbd>
Between Marseilles and Mediterranean Sea ...
Boat connection
<span class="comment"># two cities with all three connections</span>
<kbd is="sh">./conn Rome Naples</kbd>
Between Rome and Naples ...
Rail connection
Road connection
<span class="red">Boat connection</span>
<span class="comment"># direct connection between two seas must be by boat</span>
$ ./conn "Black Sea" "Ionian Sea"
Between Black Sea and Ionian Sea ...
Boat connection
<span class="comment"># no direct rail/road/sea connection between Munich and Berlin</span>
<kbd is="sh">./conn Munich Berlin</kbd>
Between Munich and Berlin ...
No direct connection
<span class="comment"># no direct connection between London and Castle Dracula ... probably a good thing</span>
<kbd is="sh">./conn London "Castle Dracula"</kbd>
Between London and Castle Dracula ...
No direct connection
</pre>

<p>
While implementing the above function, you are free to introduce any auxiliary
functions that you think are useful.
However, these should all be declared as <code>static</code> because they are not
visible outside the ADTs.


<h2>Challenge: Speed up <code>nameToID()</code></h2>
<p>
The <code>nameToID()</code> function searches for names in the
<code>places[]</code> table using a simple linear search.
Since the table is sorted by name, the search could be done
more efficiently.
Re-implement the <code>nameToID()</code> function so that it
uses binary search on the place names.


<h2>Demonstration/Submission</h2>
<p>
Once you have completed the above task, you should demonstrate your work to
your tutor.
Ideally, you would do this in the Week 09 Lab. If you can't finish the tasks
in the lab, you have until 5pm  on Sunday to complete and submit them.
You should then demonstrate your work at the start of the Week 10 Lab.

<p>
Have fun ... <i>jas</i>
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
