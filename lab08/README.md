
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 08 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 08 Lab Exercise</span><br/>
    <span class="subheading"></span>
  </header>
<center><table border='0'>
<tr>
<td> <img align='center' src='Pics/small-world.png'> </td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td align='center'> <span style='font-size:22pt'>Weighted Graphs and Geo Data</span>
</td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td> <img align='center' src='Pics/small-world.png'> </td>
</tr></table>
</center>

<h2>Objectives</h2>
<ul>
<li>to implement a variant of path finding in a weighted graph</li>
<li>to see how graphs might be used with real-world data</li>
</ul>
<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 08 Lab or in the Week 09 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab08 Graph.c</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by Sun 10 November 2019, 17:00:00</dd>
</dl>

<h2>Background</h2>
<p>
Geographic data is widely available, thanks to sites such as
<a href="http://www.geonames.org/">GeoNames</a>.
For this lab, we have downloaded data files from 
<a href="http://people.sc.fsu.edu/~jburkardt/datasets/cities/cities.html">City Distance Dataset</a>
by John Burkardt in the Department of Scientific Computing
at Florida Statue University.
The dataset that we will use contains information about distances between 30
prominent cities/locations around the world.
It measures "great circle" distances; we'll assume that these
measure the distances that an aircraft might fly between the two cities.
The data that we have forms a complete graph in that there is a distance
recorded for every pair of cities.
</p>
<p>
The following diagram shows a subset of the data from the City Distance Dataset.
</p>
<center>
<img src="Pics/world.png" />
<br>
<small>
Map from <a href="http://commons.wikimedia.org/wiki/File:BlankMap-World-v2.png#mediaviewer/File:BlankMap-World-v2.png">
"BlankMap-World-v2"</a> by original uploader: Roke <br>
Own work. Licensed under Creative Commons Attribution-Share Alike 3.0 via Wikimedia Commons
</small>
</center>

<p>
The data comes in two files:
</p>
<dl>
<dt><b><code>ha30_dist.txt</code></b></dt>
<dd><p>
This file contains a matrix of distances between cities.
This is essentially the adjacency matrix for a weighted graph
where the vertices are cities and the edge weights correspond
to distances between cities.
As you would expect for an adjacency matrix, the leading diagonal
contains all zeroes (in this case, corresponding to the fact that
a city is zero distance from itself).
</p></dd>
<dt><b><code>ha30_name.txt</code></b></dt>
<dd><p>
This file contains one city name per line.
If we number the lines starting from zero, then the line number
corresponds to the vertex number for the city on that line.
For example, the Azores is on line 0, so vertex 0 corresponds to
the Azores, and the first line in the distance file gives distances
from the Azores to the other 29 cities.
The last line (line 29) tells us that Tokyo is vertex 29, and
the last line in the distance files gives distances between
Tokyo and all other cities.
</p></dd>
</dl>

<h2>Setting Up</h2>
<p>
Set up a directory for this lab under your COMP2521 labs directory,
change into that directory, and run the following command:
</p>
<pre><kbd is="sh">unzip <a href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week08/lab.zip">/web/cs2521/19T3/labs/week08/lab.zip</a></kbd></pre>
<p>
If you're working at home, download <code><a href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week08/lab.zip">lab.zip</a></code>
and then work on your local machine.
</p>
<p>
If you've done the above correctly, you should now find the following files in the directory:
</p>

<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/travel.c">travel.c</a></code> </dt>
<dd>main program to load and manipulate the graph</dd>
<dt><code><a href="files/Graph.h">Graph.h</a></code> </dt>
<dd>interface to Graph ADT</dd>
<dt><code><a href="files/Graph.c">Graph.c</a></code> </dt>
<dd>implementation of Graph ADT</dd>
<dt><code><a href="files/Queue.h">Queue.h</a></code> </dt>
<dd>interface to Queue ADT</dd>
<dt><code><a href="files/Queue.c">Queue.c</a></code> </dt>
<dd>implementation of Queue ADT</dd>
<dt><code><a href="files/Item.h">Item.h</a></code> </dt>
<dd>definition of Items (Edges)</dd>
<dt><code><a href="files/ha30_name.txt">ha30_name.txt</a></code> </dt>
<dd>the city name file described above</dd>
<dt><code><a href="files/ha30_dist.txt">ha30_dist.txt</a></code> </dt>
<dd>the distance matrix file described above</dd>
</dl>
<p>
The <code>Makefile</code> produces a file called <code>travel</code> based on the
main program in <code>travel.c</code> and the functions in <code>Graph.c</code>.
The <code>travel</code> program takes either zero or two command line arguments.
</p>
<pre>
<kbd is="sh">./travel</kbd>
<span class="comment">... displays the entire graph ...</span>
<span class="comment">... produces lots of output, so either redirect to a file or use less ...</span>
<kbd is="sh">./travel <var>from-city</var> <var>to-city</var></kbd>
<span class="comment">... display a route to fly between specified cities ...</span>
</pre>
<p>
If given zero arguments, it simply displays the graph (in the format described
below).
If given two arguments, it treats the first city as a starting point and the
second city as a destination, and determines a route between the
two cities, based on "hops" between cities with direct flights.
</p>
<p>
Read the <code>main()</code> function so that you understand how it works, and,
in particular, how it invokes the functions that you need to implement.
</p>
<p>
The <code>Graph</code> ADT in this week's lab has a <code>GraphRep</code>
data structure that is a standard adjacency matrix representation
of the kind we looked at in lectures.
However, some aspects of it are different to the <code>GraphRep</code>
from lectures.
</p>
<p>
Note that city names are not stored as part of the <code>GraphRep</code>
data structure.
The <code>Graph</code> ADT deals with vertices using their numeric id.
The <code>main</code> program maintains the list of city names and
passes this list to the <code>showGraph()</code> function when it is
called to display the graph.
This means that the calling interface for the <code>showGraph()</code>
function is different to the <code>showGraph()</code> function
from the <code>Graph</code> ADT in lectures.
</p>
<p>
Another difference between this <code>Graph</code> ADT and the one
used in lectures is that the values stored in the matrix are not simply
zero and one, but represent the distances between vertices.
In other words, we're dealing with a <em>weighted</em> graph.
Note, however, that we are not actually using the weights <em>except</em>
to indicate the existence of an edge. A weight value of zero indicates
no edge between two vertices, while a non-zero weight indicates an edge.
</p>
<p>
The <code>Graph</code> ADT includes a sub-ADT for <code>Edge</code>s.
The implementation of <code>insertEdge()</code> in lectures only
required the vertices at the endpoints of the <code>Edge</code>
(i.e. <code>insertEdge(g,v,w)</code>).
The version of <code>insertEdge()</code> for this lab also
requires a weight for the edge (i.e. <code>insertEdge(g,v,w,weight)</code>).
</p>
<p>
The main program makes some changes to the edges implied by the distance matrix
as it copies them into the <code>Graph</code>.
The values in the <code>ha30_dist.txt</code> file are given in units of
"hundreds of miles"; we want them in units of kilometres so each distance
is converted before it is added to the graph as the weight of an edge.
Since every city has a distance to every other city (except itself),
this gives us a <em>complete graph</em>.
</p>
<p>
As supplied, the <code>Graph.c</code> file is missing implementations
for the <code>findPath()</code> function.
If you compile the <code>travel</code> program and try to find any
route, it will simply tell you that there isn't one.
If you run <code>travel</code> with no arguments, it will print a
representation of the graph (you can see what this should look
like in the file <a href="graph.txt">graph.txt</a>.
</p>

<h2>Exercise</h2>
<p>
Implement the <code>findPath(g,src,dest,max,path)</code> function.
This function takes a graph <code>g</code>, two vertex numbers <code>src</code> and <code>dest</code>,
a maximum flight distance, and fills the <code>path</code> array with a sequence of vertex
numbers giving the "shortest" path from <code>src</code> to <code>dest</code> where no edge
on the path is longer than <code>max</code>.
The function returns the number of vertices stored in the <code>path</code> array;
if it cannot find a path, it returns zero.
The <code>path</code> array is assumed to have enough space to hold the longest possible
path (which would include all vertices).
</p>
<p>
This could be solved with a standard BFS graph traversal algorithm,
but there are two twists for this application:
</p>
<ul>
<li><p>
The edges in the graph represent real distances, but the user of the
<code>travel</code> program (the traveller) isn't necessarily worried about
real distances.
They are more worried about the number of take-offs and landings (which
they find scary), so the length of a path is measured in terms of the
number of edges, <em>not</em> the sum of the edge weights. Thus, the
"shortest" path is the one with the minimum number of edges.
</p>
<li><p>
While the traveller isn't worried about how far a single flight goes,
aircraft <em>are</em> affected by this (e.g. they run out of fuel).
The <code>max</code> parameter for <code>findPath()</code> allows a user to
specify that they only want to consider flights whose length is at
most <code>max</code> kilometres (i.e. only edges whose weight is not more
than <code>max</code>).
</p>
</ul>
<p>
Your implementation of <code>findPath()</code> must satisfy both of the above.
</p>
<p>
In implementing <code>findPath()</code>, you can make use of the <code>Queue</code>
ADT that we've supplied.
This will create a queue of <code>Vertex</code> numbers.
<p>
Note that the default value for <code>max</code>, set in the <code>main</code>
program is 10000 km.
Making the maximum flight distance smaller produces more interesting
paths (see below), but if you make it too small (e.g. 5000km)
you end up isolating Australia from the rest of the world.
With maximum flights of 6000km, the only way out of Australia in
this data is via Guam.
If you make the maximum flight length large enough (e.g. aircraft
technology improves significantly), every city will be reachable
from every other city in a single hop.
</p>
<p>
Some example routes (don't expect them to closely match reality):
</p>
<pre>
<span class="comment"># when no max distance is given on the command line,</span>
<span class="comment"># we assume that planes can fly up to 10000km before refuelling</span>
<kbd is="sh">./travel Berlin Chicago</kbd>
Least-hops route:
Berlin
->Chicago
<kbd is="sh">./travel Sydney Chicago</kbd>
Least-hops route:
Sydney
->Honolulu
->Chicago
<kbd is="sh">./travel Sydney London</kbd>
Least-hops route:
Sydney
->Shanghai
->London
<kbd is="sh">./travel London Sydney</kbd>
Least-hops route:
London
->Shanghai
->Sydney
<kbd is="sh">./travel Sydney 'Buenos Aires'</kbd>
Least-hops route:
Sydney
->Honolulu
->Chicago
->Buenos Aires
<span class="comment"># if no plane can fly more than 6000km without refuelling</span>
<kbd is="sh">./travel Sydney London 6000</kbd>
Least-hops route:
Sydney
->Guam
->Manila
->Bombay
->Baghdad
->London
<span class="comment"># if no plane can fly more than 5000km without refuelling</span>
<span class="comment"># you can't leave Australia under this scenario</span>
<kbd is="sh">./travel Sydney 'Buenos Aires' 5000</kbd>
No route from Sydney to Buenos Aires
<span class="comment"># if no plane can fly more than 7000km without refuelling</span>
<kbd is="sh">./travel Sydney 'Buenos Aires' 7000</kbd>
Least-hops route:
Sydney
->Guam
->Honolulu
->Chicago
->Panama City
->Buenos Aires
<span class="comment"># planes can fly up to 8000km without refuelling</span>
<kbd is="sh">./travel Sydney 'Buenos Aires' 8000</kbd>
Least-hops route:
Sydney
->Guam
->Honolulu
->Mexico City
->Buenos Aires
<span class="comment"># planes can fly up to 11000km without refuelling</span>
<kbd is="sh">./travel Sydney 'Buenos Aires' 11000</kbd>
Least-hops route:
Sydney
->Bombay
->Azores
->Buenos Aires
<span class="comment"># planes can fly up to 12000km without refuelling</span>
<span class="comment"># can reach Buenos Aires on a single flight</span>
<kbd is="sh">./travel Sydney 'Buenos Aires' 12000</kbd>
Least-hops route:
Sydney
->Buenos Aires
<kbd is="sh">./travel Bombay Chicago 5000</kbd>
Least-hops route:
Bombay
->Istanbul
->Azores
->Montreal
->Chicago
<kbd is="sh">./travel Sydney Sydney</kbd>
Least-hops route:
Sydney
</pre>
<p>
The above routes were generated using an algorithm that checked vertices
in order (vertex 0 before vertex 1 before vertex 2, etc.). If you check
in a different order, you may generate different, but possibly equally valid,
routes.
</p>


<h2>Demonstration/Submission</h2>
<p>
Once you have completed the above task,
you should demonstrate your work to your tutor.
Ideally, you would do this in the Week 08 Lab.
If you can't finish the tasks in the lab,
you have until midnight on Sunday to complete and submit them.
You should then demonstrate your work
at the start of the Week 09 Lab;
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
