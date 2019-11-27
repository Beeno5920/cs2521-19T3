
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 02 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 02 Lab Exercise</span><br/>
    <span class="subheading"></span>
  </header>
<center><table border='0'>
<tr>
<td> <img align="center" src="Pics/typewriterL.png"> </td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td align="center"> <span style="font-size:22pt">MyEd and DLLs</span>
</td>
<td> &nbsp; &nbsp; &nbsp; &nbsp; </td>
<td> <img align="center" src="Pics/typewriterR.png"> </td>
</tr></table>
</center>

<h2>Objectives</h2>
<ul>
<li>to illustrate file manipulation</li>
<li>to implement a doubly-linked list ADT</li>
<li>to design comprehensive test-cases</li>
<li>to build a simple line-based text editor</li>
</ul>
<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 02 Lab or in the Week 03 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab02 DLList.c testList.c</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by Sun 29 Sept 2019, 17:00:00</dd>
</dl>

<h2>Aims</h2>
<p>
This lab aims to re-examine an idea that we have looked at a few times
in lectures (without being explicit about it): <strong>command interpreters</strong>.
More importantly, it aims to give you practice manipulating a useful
data type: <strong>doubly-linked lists</strong>.
Finally, it aims to demonstrate how files are manipulated in Linux.
These ideas are tied together in a simple
<em>text editor</em>, a program in the style of the classic Unix
text editor <em>ed(1)</em>, an editor which roamed the earth
contemporaneously with the dinosaurs.
</p>

<h2>Background</h2>
<p>
A text editor deals with a file of text, reads it, allows the user
to modify it, and then writes it back.
This implies that the editor has an internal representation that
it deals with in between the reading and the writing.
For this example, we consider that the internal representation is a
sequence of lines, represented by a doubly-linked list of strings.
Each node in the list represents one line in the file being edited.
</p>
<p>
Since a common operation is to "move around" the file, looking for
lines to change, a doubly-linked list with a notion of a current
node provides a convenient way to do this.  The editor itself is
implemented as a loop which: prints a prompt<sup>*</sup>, reads a command,
carries out the command (possibly changing the state of the list),
and then repeats.  Many of the programs that we build for exploring
data structures during this course will have a similar structure.
<br />
<small>
*: That it prints a prompt is
   an improvement on the real <em>ed(1)</em> editor,
   which doesn't (by default).
   Not prompting the user may be minimalist,
   but isn't great interface design.
</small>
</p>

<h3>Doubly-linked Lists</h3>
<p>
Doubly-linked lists are a variation on "standard" linked lists where each
node has a pointer to the previous node as well as a pointer to the next node.
The following diagram shows the differences:
</p>
<div align="center"><img src="Pics/lists/linked-list-types-small.png"></div>
<p>
As shown in the diagram, our version of doubly-linked lists also has a
notion of a "current" node, and current can move backwards and forwards
along the list. Our doubly-linked list does insertions either immediately
before or immediately after the current node. Deletion always causes the
current node to be removed from the list.
</p>
<p>
In this lab, we'll use a doubly-linked list ADT called <code>DLList</code>
whose interface is given in the file
</p>
<pre>
<a target="_blank" href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week02/code/DLList.h">/web/cs2521/19T3/labs/week02/code/DLList.h</a>
</pre>
<p>
The representation of <code>DLList</code> is a doubly-linked list of <code>DLListNode</code>s,
accessed via a record containing the following four fields:
</p>
<ul>
<li><code>nitems</code>: a count of the number of nodes/items in the list</li>
<li><code>first</code>: a pointer to the first node in the list</li>
<li><code>last</code>: a pointer to the last node in the list</li>
<li><code>curr</code>: a pointer to the "current" node in the list</li>
</ul>
<p>
Several important conditions must hold at all times during the lifetime of a
<code>DLList</code>.
Technically, these conditions are called <em>invariants</em>, and are checked
for in the function <code>validDLList()</code>.
</p>
<ul>
<li><p>
Whenever the list is non-empty, it must have a defined current node.
It is not possible for the current node pointer to be NULL if there
is at least one node in the list.
</p></li>
<li><p>
The counter <code>nitems</code> must always contain a value which is the
same as the number of nodes in the list.
</p></li>
</ul>
<p>
The book-keeping operations (e.g. <code>newDLList()</code>, <code>getDLList()</code>, etc.)
 are relatively straightforward, so we'll describe only the operations relevant
for this lab in detail.
</p>
<dl>
<dt><strong>char *DLListCurrent(DLList L)</strong></dt>
<dd><p>
Return a pointer to the string value for the current node.
It is an error to call this function if the list contains no nodes.
</p></dd>
<dt><strong>bool DLListMove(DLList L, int n)</strong></dt>
<dd><p>
Move the current pointer either backwards or forwards <code>n</code> positions
from the current position.
Move forwards in <code>n</code> is positive, and move backwards if <code>n</code>
is negative.
If current reaches either end of the list before it has moved <code>n</code>
positions, it stops at the end node.
If the movement stops with current at either the first or last node, return
a value of 1; otherwise, return a value of 0.
</p></dd>
<dt><strong>bool DLListMoveTo(DLList L, int n)</strong></dt>
<dd><p>
Set the current pointer to point to the <code>n</code><sup>th</sup> node in
the list, where nodes are indexed starting from 1.
If <code>n </code> is smaller than 1, the current node will be set to the first node.
If <code>n </code> is larger than the number of nodes in the list, the current
node will be set to the last node.
The return value has the same behaviour as the return value of <code>DLListMove()</code>.
</p></dd>
<dt><strong>void DLListBefore(List, char *)</strong></dt>
<dd><p>
Insert a new node in the list immediately before the current node.
The new node becomes the current node.
If the node is inserted before the first node, it also becomes the
new first node.
</p></dd>
<dt><strong>void DLListAfter(List, char *)</strong></dt>
<dd><p>
Insert a new node in the list immediately after the current node.
The new node becomes the current node.
If the node is inserted after the last node, it also becomes the
new last node.
</p></dd>
<dt><strong>void DLListDelete(List)</strong></dt>
<dd><p>
Remove the current node from the list (and free its memory,
including the memory used to hold the string).
The current node becomes the node immediately following the node
that was removed.
If the removed node is the last node (i.e. the node at the end of
the list), then the current node is set to the new last node.
If the node removed was the only node in the list, then current
becomes NULL.
If <code>DLListDelete()</code> is called with an
empty list, it should simply return without making any changes
to the list.
</p></dd>
</dl>
<p>
Note that the supplied <code>DLList</code> ADT implements a doubly-linked
list of strings.
The strings are created outside the list nodes, as in the diagram below:
</p>
<div align="center"><img src="Pics/lists/dllist-strings-small.png"></div>
<p>
The storage used by the strings needs to be managed separately to the
storage used by the list nodes, although still as part of the
implementation of the <code>DLList</code> ADT.
</p>

<h3><code>myed</code>: a Text Editor</h3>
<p>
Text editors are programs that allow you to manipulate text files interactively;
they provide a user interface where you can load a file, make changes to it, and
then save an updated version of the file.
Text editors like <code>myed</code> are seriously retro and hark back to the 60's,
when screen-based editors like <code>vi</code> and <code>emacs</code> didn't exist,
and graphical editors like <code>gedit</code> weren't even a gleam in some
inventor's eye (except maybe
<a target="_blank" href="http://en.wikipedia.org/wiki/Douglas_Engelbart">Doug Engelbart</a>).
</p>
<p>
The <code>myed</code> program provides an extremely simple command-line interface
where you enter one-letter commands to manipulate the loaded file.
Despite its primitive interface, <code>myed</code> can actually make changes to
text files.
Here's an example session with the editor (using the normal notational
conventions: what the system prints is in <code>this font</code>, what you type
is in <code><strong>this font</strong></code>, comments are in <code class="comment">small grey font</code>).
</p>
<pre>
<kbd is="sh">./myed text</kbd>              <span class="comment">// start the editor, loading a file called "text"</span>
&gt; <kbd>%</kbd>                        <span class="comment">// show all of the lines in the file</span>
this is                    <span class="comment">// the current line is the first line</span>
a small file
containing a few lines
of boring text
&gt; <kbd>.</kbd>                        <span class="comment">// show the current line</span>
this is
&gt; <kbd>i</kbd>                        <span class="comment">// insert a line before the first line</span>
<kbd>new first line</kbd>             <span class="comment">// you type the new line here</span>
&gt; <kbd>%</kbd>                        <span class="comment">// show all of the lines again, so you can see the changes</span>
new first line             <span class="comment">// note that the new line is now the current line</span>
this is
a small file
containing a few lines
of boring text
&gt; <kbd>n</kbd>                        <span class="comment">// move to the next line</span>
this is
&gt; <kbd>n</kbd>                        <span class="comment">// move to the next line</span>
a small file
&gt; <kbd>n</kbd>                        <span class="comment">// move to the next line</span>
containing a few lines
&gt; <kbd>-2</kbd>                       <span class="comment">// move back two lines</span>
this is
&gt; <kbd>w</kbd>                        <span class="comment">// save a copy of the modified file</span>
&gt; <kbd>q</kbd>                        <span class="comment">// quit the editor</span>
<kbd is="sh">ls</kbd>                       <span class="comment">// list the files in the current directory</span>
...  text  text.new ...    <span class="comment">// should see the original file and the new version</span>
<kbd is="sh">cat text.new</kbd>             <span class="comment">// look at the contents of the new text file</span>
new first line
this is
a small file
containing a few lines
of boring text
<kbd is="sh"></kbd>
</pre>
<p>
The best way to get a feeling for how the editor works is to play with it.
There's a working version in the class directory, which you can execute on
the CSE lab machines via the command:
<pre>
<kbd is="sh">/web/cs2521/19T3/labs/week02/myed <var>filename</var></kbd>
</pre>
<p>
Choose any old text file you like as the filename.
Once you have an editor prompt, the command <code>?</code>
will tell you what other commands are available.
</p>
<p>
If you play with the supplied <code>myed</code>, I can guarantee that you will
run the <kbd>%</kbd> command a lot. Editing is better when you get
immediate feedback on the changes you've made, which led to the development
of screen-based editors like <em>vi</em> and <em>emacs</em> soon after the
novelty of editing in the <em>ed(1)</em> style wore off (and once graphical
displays were available).
If you're keen to experience the original <em>ed(1)</em>, it's still available
under Linux.
</p>

<h2>Setting Up</h2>
<p>
Set up a directory for this lab under your <code>cs2521/labs</code> directory,
change into that directory, and run the following command:
</p>
<pre>
<kbd is="sh">unzip /web/cs2521/19T3/labs/week02/lab.zip</kbd>
</pre>
<p>
If you're working at home, download <code><a target="_blank" href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week02/lab.zip">lab.zip</a></code>,
unzip it there, and then work on your local machine.
</p>
<p>
If you've done the above correctly, you should now find the following files in the directory:
</p>
<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/DLList.h">DLList.h</a></code> </dt>
<dd>interface definition for the List ADT</dd>
<dt><code><a href="files/DLList.c">DLList.c</a></code> </dt>
<dd>(partial) implementation for the List ADT</dd>
<dt><code><a href="files/testList.c">testList.c</a></code> </dt>
<dd>main program for testing the List ADT</dd>
<dt><code><a href="files/myed.c">myed.c</a></code> </dt>
<dd>main program for a simple line-based text editor</dd>
<dt><code><a href="files/text">text</a></code> </dt>
<dd>a simple text file that you can use to test <code>myed</code></dd>
</dl><p>
Once you've got these files, the first thing to do is to run the command
</p>
<pre>
<kbd is="sh">make</kbd>
</pre>
<p>
This will produce messages about compiling, and will put
two executable files in your directory (along with some <code>.o</code> files).
</p>
<dl>
<dt><code>testList</code></dt>
<dd>
<p>
This is the executable for the <code>testList.c</code> program.
As supplied, it runs a number of simple tests on the <code>DLList</code> datatype.
You can use it by running <code>./testList</code>, typing in a few lines of text and
then using control-D to end the input; the program should display all of the
lines you typed and not produce any <code>assert</code> errors.
You will need to add more extensive tests as part of this Lab.
</p>
</dd>
<dt><code>myed</code></dt>
<dd>
<p>
This is the executable for the <code>myed.c</code> program, which implements
a very simple line-based text editor.
It takes as argument a file name, reads this file into a doubly-linked
list of lines, and then supports various actions on the lines.
See the <code>myed.c</code> file for details on what commands are available,
or type the <kbd>?</kbd> command inside the editor to get help.
</p>
<p>
Since <code>myed</code> is a text editor, it needs to be invoked by giving it
a file to edit. The <code>lab.zip</code> archive contains a small text file
(called <code>text</code>) that you can use with the editor.
Invoke the editor using a command like:
</p>
<pre><kbd is="sh">./myed text</kbd></pre>
</dd>
</dl>

<h2>Task 1 </h2>
<p>
The <code>myed</code> program is complete, but doesn't work because some of
the functions in <code>DLList.c</code> are not complete.
You should complete these functions so that the behaviour of your
<code>myed</code> program is the same as the behaviour of the sample
solution:
</p>
<pre>
<kbd is="sh">/web/cs2521/19T3/labs/week02/myed  text</kbd>
</pre>
<p>
You can execute the sample solution on the CSE workstations (only),
by typing the full path name exactly as above.
It would be a good idea to play with the sample solution at least
briefly to get an idea of how it is supposed to work.
</p>
<p>
Note that since the two <code>myed</code> programs read from <code>stdin</code>
and write to <code>stdout</code>, one automatic way of testing them would
be to devise a set of editing scripts (files containing sequences of
<code>myed</code> commands), and then apply each script with both your
<code>myed</code> and the sample <code>myed</code> and using <code>diff</code> to
ensure that they both produce the same output, e.g.
</p>
<pre>
<kbd is="sh">./myed text &lt; <var>FileContainingEditCommands</var> &gt; out1</kbd>
<kbd is="sh">/web/cs2521/19T3/labs/week02/myed text &lt; <var>FileContainingEditCommands</var> &gt; out2</kbd>
<kbd is="sh">diff out1 out2</kbd>
</pre>
<p>
In order to establish the correctness of your <code>myed</code>, you should
develop a number of editing scripts, each one being more devious than the
previous in attempting to crash your editor (and the sample one, if you can ...
if you do work out how to crash the sample editor, let me know, and I'll
fix it).

<!--
If you come up with a particularly clever test script, add it as code to
the WebCMS page:
</p>
<pre>
<a target="_top" href="https://webcms3.cse.unsw.edu.au/COMP1927/16s2/resources/4729">Week02: MyEd and Doubly-Linked Lists</a>
</pre>
-->

<h2>Task 2</h2>
<p>
Implementing the <code>DLList</code> functions to make <code>myed</code> work
serves two purposes: (a) getting a complete editor, (b) <code>myed</code>
providing a simple test harness for the <code>DLList</code> ADT.
However, the way that <code>myed</code> exercises the ADT is by no means
complete, and more testing is needed.
</p>
<p>
The <code>testList.c</code> program provides a skeleton in which to build
a more serious testing framework. At present, it is minimal; it simply
uses the <code>getDLList()</code> function to read some strings from standard
input into a <code>List</code>, displays the <code>List</code> and then does a
sanity check on the representation.
You should expand <code>testList.c</code> to provide a more complete set of
tests to exercise the <code>DLList</code> functions.
</p>
<p>
Note that writing a detailed test suite for all functions in the ADT
is quite time consuming.
You should at least write comprehensive test cases for the three functions
that you implemented.
This means that you should have a test for each of the possible states in
which each function might be invoked (e.g. empty list, list with one node,
etc.).
At the least, each test should:
</p>
<ul>
<li> show the state of the list before the operation (including <code>curr</code> and <code>nitems</code>)
<li> indicate what operation is about to be performed
<li> invoke the operation
<li> display the state of the list after the operation
<li> run the <code>validDLList()</code> check on the list
</ul>
<p>
You can simply use visual inspection of the output to check whether the
operations have worked correctly, and, of course, check with <code>validDLList()</code>
after each operation. It is not necessary to write automatic checks of
the precise state, since this would require writing multiple functions
almost as complex as <code>validDLList()</code>.
If you wish to modify <code>putDLList()</code> to give a better display of
the <code>DLList</code> state (e.g. use short lines and display all of them
on a single output line), that would be useful (but not essential).
</p>

<h2>Submission</h2>
<p>
You need to submit two files: <code>DLList.c</code> and <code>testList.c</code>.
Submit these either via the <code>give</code> command in a terminal window
or from WebCMS, and then show your tutor, who'll give
you feedback on your coding style, your test quality, and award a mark.
</p>
<p>
Have fun, <em>jas</em>
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
