
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 05 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 05 Lab Exercise</span><br/>
    <span class="subheading">Binary Search Trees</span>
  </header>
<h2>Objectives</h2>
<ul>
<li>to investigate balanced tree insertion algorithms experimentally</li>
<li>to add instrumentation to code and use it to analyse performance</li>
</ul>
<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 05 Lab or in the Week 06 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab05 Tree.c Results.txt</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by Sun 20 October 2019 17:00:00</dd>
</dl>

<h2>Background</h2>
<p>
In lectures in Week 04, we will discuss a range of binary search tree insertion
strategies which aimed to improve the balance of the trees and thus reduce
search time.
We incorporated most of the required functions into a "Tree Lab" program.
This week's lab involves you dealing with a modified version of the Tree Lab.

<p>
The Tree Lab allows you to build trees of various sizes, using a range of
insertion methods, and supplying the values to be inserted in several possible
orders.
The Tree Lab program has the following usage (which you can find out simply
by running the program with no command-line arguments):

<pre>
<kbd is="sh">./tlab</kbd>
Usage: ./tlab N Order Insert Seed
0 &lt;= N &lt;= 9999, Seed = a random number
Order = <strong>A</strong>scending|<strong>D</strong>escending|<strong>P</strong>refix|<strong>R</strong>andom
Insert = <strong>L</strong>eaf|<strong>A</strong>t-root|re<strong>B</strong>alance|<strong>R</strong>andom|<strong>S</strong>play|a<strong>V</strong>l
For Order and Insert, use just the upper-case letter
e.g. for AVL, use V; for Rebalancing, use B
</pre>

<p>
Tree Lab has the following command-line parameters:

<dl>
<dt><strong>N</strong> = number of values</dt>
<dd>
<p>
This parameter can be any number in the range 0 to 9999.
If 0, you start with an empty tree.
</dd>

<dt><strong>Order</strong> = order in which values are inserted</dt>
<dd>
<p>Possible values for this parameter:</p>
<ul>
<li> <strong>A</strong> = supply the values 1, 2, ..., N in ascending order, starting at 1 </li>
<li> <strong>D</strong> = supply the values N, N-1, N-2, ..., 1 in descending order, starting from N </li>
<li> <strong>P</strong> = supply values from 1..N in prefix order, to build a balanced tree</li>
<li> <strong>R</strong> = supply N distinct random values in the range 1..9999</li>
</ul>
</dd>

<dt><strong>Insert</strong> = style of tree insertion</dt>
<dd>
<p>Possible values for this parameter:</p>
<ul>
<li> <strong>L</strong> = insert new values at the leaves (standard BST insert) </li>
<li> <strong>A</strong> = insert new values at the root  </li>
<li> <strong>R</strong> = insert values by randomly choosing between L and A </li>
<li> <strong>B</strong> = insert at leaves, but periodically rebalance the tree </li>
<li> <strong>S</strong> = insert using the Splay Tree approach </li>
<li> <strong>V</strong> = insert using the AVL Tree approach </li>
</ul>
</dd>

<dt><strong>Seed</strong> = seed for random number generator (if used)</dt>
<dd>
<p>
You can optionally specify a seed for the random number generator.
This is only relevant for <strong>R</strong> ordering, but is useful for generating
different (and reproducible) random tree configurations.
</dd>
</dl>

<p>
Some examples of usage of the Tree Lab:

<pre>
<kbd is="sh">./tlab 20 R L</kbd>
<span class="comment">... insert 20 random values using standard BST insertion</span>
<kbd is="sh">./tlab 20 R L 2</kbd>
<span class="comment">... insert 20 random values using standard BST insertion</span>
<span class="comment">... uses a different seed to produce a different tree</span>
<kbd is="sh">./tlab 10 A L</kbd>
<span class="comment">... insert 10 ordered values using standard BST insertion</span>
<span class="comment">... guaranteed to produce a degenerate tree with one long branch</span>
<kbd is="sh">./tlab 15 P L</kbd>
<span class="comment">... insert 15 values using standard BST insertion</span>
<span class="comment">... supplies values in prefix order to produce a balanced tree</span>
<kbd is="sh">./tlab 20 R V</kbd>
<span class="comment">... insert 20 random values (in random order) into an AVL tree</span>
<kbd is="sh">./tlab 15 D V</kbd>
<span class="comment">... insert 15 descending values into an AVL tree</span>
<kbd is="sh">./tlab 20 R S</kbd>
<span class="comment">... insert 20 random values (in random order) into a Splay tree</span>
<kbd is="sh">./tlab 15 D S</kbd>
<span class="comment">... insert 15 descending values into a Splay tree</span>
</pre>

<p>
When it starts up, the Tree Lab builds a tree according to your specification
and then prints a prompt, to which you can type a number of commands. See the
help message in the example below for details.
At this stage, the most useful command is:

<ul>
<li> <strong>q</strong> = quit the Tree Lab program </li>
</ul>

Here is a more realistic session with the Tree Lab, which simply loads
a small tree, asks for help, and then runs some search tests on the tree.
Note that even though you have specified a seed, you may not get the same
numbers as below, depending on how the random number generator on your
machine works. However, if you run the same command multiple times <em>on
the same machine</em>, you should always get the same results.

<pre>
<kbd is="sh">./tlab 7 R L 5</kbd>
Tree:
#nodes = 7,  depth = 5,  #compares = 15,  #rotates = 0
     683
       \
      8745
       / \
      /   \
     /     \
   1261   8824
   / \
  /   \
996  2738
      /
    2178

&gt; <kbd>?</kbd>
Commands:
i N ... insert N into tree
d N ... delete N from tree
f N ... search for N in tree
s   ... display tree if not big
v   ... print values in tree
t   ... run tests on tree
q   ... quit

&gt; <kbd>t</kbd>
Tree search test
Search for 7 values known to be in tree
Found 7 matches; ok
Search for 2 values known to *not* be in tree
Found 0 matches; ok
Tree:
#nodes = 7,  depth = 5,  #compares = 42,  #rotates = 0
     683
       \
      8745
       / \
      /   \
     /     \
   1261   8824
   / \
  /   \
996  2738
      /
    2178

&gt; <kbd>q</kbd>
<kbd is="sh"></kbd>
</pre>

<p>
Some points to note about the above.
The Tree Lab program creates a tree and then displays information about it,
including the number of nodes in the tree, its depth, and a count of the
number of comparisons and rotations that occurred while building it.
In this case (standard BST insertion) there are no rotations.
The test (<code>t</code>) command in the Tree Lab runs a set of tests on
the tree as follows:

<ul>
<li> <p>Randomly selects N values from the inserted values and searches
for them. This can include repeated searches for the same value. Note that
the random number generator is re-seeded at the start of the tests, so
the same set of tests will always be generated for a given set of
inserted values.</p>
<li> <p>Searches for approximately N/3 values which are guaranteed not
to be in the tree. Two of the values are always 0 and 10000, while the
others are chosen from values known not to be in the list of inserted
values. See the code in <code>tlab.c</code> for details on how this is done.</p>
</ul>

<p>
In the above example, you can see that before the tests <code>#compares=11</code>
and after the tests <code>#compares=38</code>.
The 11 comparisons occurred during the insertion of the 7 values.
The counts for rotations and comparisons accumulate over the lifetime of
the tree, and you can use the difference between the first and second
values of the comparisons to work out that the 9 searches (7 successful,
2 unsuccessful) required 38-11=27 comparisons.
Note that if you run tests on the supplied code, you will always get
zero for <code>#compares</code> and <code>#rotates</code>.
The code for doing the counts is what you need to implement for the
first task in this lab.


<h2>Setting Up</h2>
<p>
Set up a directory for this lab under your <code>cs2521/labs</code> directory,
change into that directory, and run the following command:

<pre>
unzip /web/cs2521/19T3/labs/week05/lab.zip</pre>

<p>
If you're working at home,
download <code><a href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week05/lab.zip">lab.zip</a></code>
and then work on your local machine.

<p>
If you've done the above correctly, you should now find the following files in the directory:

<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/tlab.c">tlab.c</a></code> </dt>
<dd>The Tree Lab main program</dd>
<dt><code><a href="files/Tree.h">Tree.h</a></code> </dt>
<dd>Interface to the <code>Tree</code> ADT</dd>
<dt><code><a href="files/Tree.c">Tree.c</a></code> </dt>
<dd>Implementation of the <code>Tree</code> ADT</dd>
<dt><code><a href="files/runtests">runtests</a></code> </dt>
<dd>A shell script to run a collection of tests</dd>
<dt><code><a href="files/expected">expected</a></code> </dt>
<dd>Sample outputs from running tests</dd>
<dt><code><a href="files/Results.txt">Results.txt</a></code> </dt>
<dd>A template for your results</dd>
</dl>
<p>
Note that <code>Tree.c</code> includes an implementation of red-black trees,
but we are not considering red-black trees in this lab.

<p>
Running <code>make</code> will give you an executable <code>tlab</code> that you
can use to run some of the above examples.
You should also try other examples, and examine the trees in order to
convince yourself that the insertion and search algorithms are working
correctly.
Since we'll be generating large trees later, which are too big to print,
you <em>need to be certain</em> that the trees will actually be correct
even in the tests where you don't see them.
There is no point doing performance analysis on algorithms that produce
incorrect results.

<p>
After running some tests, you should read the code to make sure that you
understand the precise data structures being used.
Note that the <code>Tree</code> representation uses a <code>TreeRep</code> data
structure that holds the counters for comparisons and rotations.
Note also that every <code>Node</code> contains a pointer to the <code>TreeRep</code>
into which it is inserted; this is critical for being able to maintain
the counts, since you need to access the <code>TreeRep</code> structure from
places in the code where you only have access to a <code>Node</code>.

<p>
You will also see that the <code>TreeRep</code> contains a field to hold
the style of insertion to be used for that tree.
This is supplied when the tree is initialised, and is used to determine
precisely which insert and search functions to use.


<h2>Task 1</h2>
<p>
Add code to count rotations and comparisons for the all of the insertion
and search functions.

<p>
This is simple for rotations; you simply add code to the
<code>rotateL()</code> and <code>rotateR()</code> functions.
The fact that in those functions, you have a pointer to a node makes
it easy to access the relevant <code>Tree</code> object to update its
rotation counter.

<p>
Counting comparisons is trickier. At the point of making the comparison,
all you have access to is two <code>Key</code> values. Even if <code>cmp()</code>
was a "proper function" (its a macro), you wouldn't be able to access
the relevant <code>Tree</code> object from within the function.
This means that you need to find all uses of <code>cmp()</code> (and its
associated macros <code>eq()</code> and <code>less()</code>) in the code,
and add appropriate counter updates there.

<p>
You can check that you are counting correctly by running the supplied
<code>runtests</code> script and comparing your output against the results
in the <code>expected</code> file.
The supplied <code>runtests</code> only runs <code>tlab</code> for ascending
order input sequences of size 200. However, it uses all of the insertion
strategies.
The output from <code>runtests</code> has the following format
for each test:

<pre>
Test: ./tlab 200 A L
#nodes = 200,  depth = 200,  #compares = 19900,  #rotates = 0

Search for 200 values known to be in tree
Found 200 matches; ok
Search for 66 values known to *not* be in tree
Found 0 matches; ok
#nodes = 200,  depth = 200,  #compares = 54990,  #rotates = 0
</pre>

<p>
The first line in each test tells you what parameters were used;
in the above example, we are feeding in 200 values in ascending
order and inserting each value at the leaf.
The next line gives you stats about the tree that was built.
As we saw in lectures, inserting an ascending sequence at the
leaves is a worst-case scenario for binary search trees and
results in a single branch with all 200 nodes in it (#nodes=200,
depth=200).
The stats also tell you how many comparison were done while
the tree.
Since each insert requires us the scan from the root, along all
of the previously inserted nodes to the leaf, the number of
comparisons will be 0+1+2+3+4+...+199 = 19900.
Since insertion at the leaves doesn't use rotation, the number
of rotations is zero.

<p>
The second part of each test does \( N \) searches (one for
each value stored in the tree) and \( N/3 \) searches for
values that are <em>not</em> in the tree.
In this example, there are 200 successful searches and 66
unsuccessful searches (and, obviously, 266 total searches).
The second stats line gives the tree dimensions (unchanged
from the initial tree), and gives the accumulated comparisons,
which includes the comparisons which occurred when the tree
was built.
Ultimately, we want to know just the comparisons for searching,
so we need to subtract the build comparisons from the total
comparisons.

<p>
Note that you execute the <code>runtests</code> script via the command:

<pre>
<kbd is="sh">sh runtests</kbd>
</pre>

<p>
It is useful to pipe it through the <code>less</code> command because
it produces a lot of output and this would otherwise scroll out
of the terminal window.

<p>
<strong>Warning:</strong>
different random number generators can produce different
results to what's in the <code>expected</code> file, so you may end up
seeing different numbers for the <code>R</code> tests.
As long as the numbers for the non-random-order insertions match,
that's okay.
The differences between your random-value insertions and the ones
in <code>expected</code> should be relatively small, in any case.


<h2>Task 2</h2>
<p>
Once you've got your counters working properly, you need to do some
experimentation by modifying the <code>runtests</code> script and
collating the results into a table in the <code>Results.txt</code> file.
To do this, modify the
<code>runtests</code> script so that it runs the following tests:

<ul>
<li> it should test all insertion methods (<code>L, A, B, R, S, V</code>)
<li> it should test each method for different data orders (<code>A, P, R</code>)
<li> it should test for larger numbers of input values (<code>5000</code>)
</ul>

<!--
<p>
Another way of checking whether your rotation counters are correct
would be to enable profiling and check the numbers after running
the Tree Lab with the relevant parameters. If you wanted to use
the same trick for checking comparison counter, you would need to
turn it into a function (rather than being a macro).
Note that you are not required to do profiling checking of counters.
-->

<p>
Summarise the results for the 5000-value tests in the file <code>Results.txt</code>.
For each test, note the depth of the tree, and compute the average number
of comparisons for the search tests.
The information that you'll need for computing the average number of comparisons
is available for each test:

<ul>
<li> \( N_b \)     = number of comparisons required for building the tree
<li> \( N_{b+s} \) = total number of comparisons for both building and searching
<li> \( N_k \)     = number of searches for values in tree
<li> \( N_u \)     = number of searches for values <em>not</em> in tree
</ul>

<p>
The formula for computing the average number of comparisons is:
$$ \frac{N_{b+s} - N_b}{N_k + N_u} $$

<p>
Type your results into the slots in the <code>Results.txt</code> file,
and <em>add some analysis</em> after the results table to indicate
what the results tell you about the relative efficiency of the
insertion/search methods.
Quote average number of comparisons as an integer value (i.e.
round the real number result).
Note that simply describing the numbers does <em>not</em>
constitute analysis; you need to <em>explain</em> why the
observed numbers occurred in the <strong>Notes</strong> section of
<code>Results.txt</code>.

<p>
If you're finding it tedious to compute the averages, feel free
to modify the output that <code>tlab</code> produces and then write
a simple C/Perl/Python program to take the simplified output and
compute the results to go in the table.


<h2>Challenge</h2>
<p>
The above analysis isn't really sufficient, since you are only working
with one set of random values.
A more effective test would use 5-10 different sets of random values
(i.e. 5-10 different seeds).
Modify the <code>runtests</code> script to do this.
There is no need to add the results to the <code>Results.txt</code> file,
but you should check that the results for the original Random order
tests are consistent with what you observe here (i.e. check that the
original tests are not an anomaly).


<h2>Submission</h2>
<p>
Make the relevant changes to <code>Tree.c</code> to complete the first task,
then run your test cases and report your observations and analysis
in the <code>Results.txt</code> file.

<p>
You need to submit two files: <code>Tree.c</code>, <code>Results.txt</code>,
via <code>give</code> or WebCMS, and then show your tutor,
who'll give you feedback on your coding style, your analysis, and award a grade.

<p>
The files must be submitted by the deadline at the start of this page,
but can be demoed to your tutor in either the Week04 or Week05 lab class.

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
