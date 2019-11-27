
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 03 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 03 Lab Exercise</span><br/>
    <span class="subheading">Binary Search Trees</span>
  </header>
<h2>Objectives</h2>
<ul>
<li>to explore the implementation of binary search trees</li>
<li>to implement a level-order traversal</li>
<li>to develop test data</li>
</ul>
<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 03 Lab or in the Week 04 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab03 BSTree.c test6.txt test7.txt</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by Sun 06 October 2019 17:00:00</dd>
</dl>

<h2>Background</h2>
<p>
In lectures, we examined a binary search tree data type <code>BSTree</code>
and implemented some operations on it.
In this week's lab, we will add some additional operations to that ADT.
</p>
<p>
Recall that a binary search tree is an ordered binary tree with the following properties:
</p>
<ul>
<li> the tree consists of a (possibly empty) collection of linked <em>nodes</em>
<li> each node contains a single integer value, and has links to two subtrees
<li> either or both subtrees of a given node may be empty
<li> all values in a node's left subtree will be less than the value in the node
<li> all values in a node's right subtree will be greater than the value in the node
</ul>

<h2>Setting Up</h2>
<p>
Set up a directory for this lab under your <code>cs2521/labs</code> directory,
change into that directory, and run the following command:
</p>
<pre>
<kbd is="sh">unzip /web/cs2521/19T3/labs/week03/lab.zip</kbd>
</pre>
<p>
If you're working at home, download <code><a href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week03/lab.zip">lab.zip</a></code>
and then work on your local machine.
</p>
<p>
If you've done the above correctly, you should now find the following files in the directory:
</p>
<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/bst.c">bst.c</a></code> </dt>
<dd>a client program to read values into a tree and then display the tree</dd>
<dt><code><a href="files/mkpref.c">mkpref.c</a></code> </dt>
<dd>a program to print number sequences that produce balanced BSTs</dd>
<dt><code><a href="files/mkrand.c">mkrand.c</a></code> </dt>
<dd>a program to generate random number sequences, for further BST testing</dd>
<dt><code><a href="files/BSTree.h">BSTree.h</a></code> </dt>
<dd>interface for the <code>BSTree</code> ADT</dd>
<dt><code><a href="files/BSTree.c">BSTree.c</a></code> </dt>
<dd>implementation of the <code>BSTree</code> ADT</dd>
<dt><code><a href="files/Queue.h">Queue.h</a></code> </dt>
<dd>interface for the <code>Queue</code> ADT</dd>
<dt><code><a href="files/Queue.c">Queue.c</a></code> </dt>
<dd>implementation of the <code>Queue</code> ADT</dd>
<dt><code><a href="files/tests/">tests/</a></code> </dt>
<dd>a sub-directory containing a collection of test cases</dd>
</dl><p>
There is quite a lot of code provided, but most of it is complete, and you don't
necessarily need to read it ... although reading other people's code is generally
a useful exercise.
The main code to look at initially is <code>bst.c</code>. This is the main program
that will be used for testing the additions you make to the <code>BSTree</code> ADT.
</p>
<p>
The other two small programs (<code>mkpref.c</code> and <code>mkrand.c</code>) are
there simply to provide data to feed into <code>bst</code> for testing.
You can compile the <code>mkpref</code> and <code>mkrand</code> programs and
try running them on a few sample inputs. You may need to read their source
code to find out how to use them properly ... especially if they're not
behaving as you expect.
The <code>bst</code> program will also compile, but won't produce correct output
until you've done your lab tasks.
</p>
<p>
Once you've read <code>bst.c</code>, the next things to look at are the header files
for the ADTs, to find what operations they provide. Finally, you should open an
editor on the <code>BSTree.c</code> file, since that's the file you need to modify
for the tasks below.
</p>
<p>
The supplied <code>BSTree</code> ADT has slightly different operations to the one 
looked at in lectures, although the underlying data representation is the same
in both cases.
Another difference is that it includes four traverse-and-print functions,
one for each of the different traversal orders (infix, prefix, postfix and
level-order).
Finally, it adds a function to count leaf nodes, in addition to the
existing function to count all nodes.
</p>
<p>
The <code>make</code> command will build the supplied versions of the code:
</p>
<pre>
<kbd is="sh">make</kbd>
gcc -Wall -Werror -g   -c -o bst.o bst.c
gcc -Wall -Werror -g   -c -o BSTree.o BSTree.c
gcc -Wall -Werror -g   -c -o Queue.o Queue.c
gcc -o bst bst.o BSTree.o Queue.o
gcc -Wall -Werror -g    mkrand.c   -o mkrand
gcc -Wall -Werror -g    mkpref.c   -o mkpref
</pre>
<p>
You can test your solutions using the supplied script <code>autotest</code>. There are 
5 test cases provided in the directory <code>tests</code>. 

<p>The following command will compile and run autotest for the case 2, 
it produce <code>tests/2.out</code> from your output. 
If <code>tests/2.out</code> is the same as <code>tests/2.exp</code> you pass the test, otherwise you fail the test. 
<p>
As soon as any test fails, it shows you the differences between
your output (*.out) and expected output (*.exp) and then quits.

<pre>
<kbd is="sh">./autotest  2 </kbd>
***                  ***
***  Testing lab03  ***
------------------------------ 
** Failed Test 2
 
> Your output (in tests/2.out): 
Tree:
      5
     / \
    /   \
   /     \
  3       7
 / \     / \
1   4   6   9

#nodes = 7,  #leaves = 0
Infix  : 1 3 4 5 6 7 9 
Prefix : 5 3 1 4 7 6 9 
Postfix: 1 4 3 6 9 7 5 
ByLevel: 
 
> Expected output (in tests/2.exp): 
Tree:
      5
     / \
    /   \
   /     \
  3       7
 / \     / \
1   4   6   9

#nodes = 7,  #leaves = 4
Infix  : 1 3 4 5 6 7 9 
Prefix : 5 3 1 4 7 6 9 
Postfix: 1 4 3 6 9 7 5 
ByLevel: 5 3 7 1 4 6 9 
 
> Compare files tests/2.exp and tests/2.out to see differences
------------------------------ 
</pre>

<p>
Similarly you can test other cases, using commands like -  
<code>./autotest 1</code>, <code>./autotest 2</code>, <code>./autotest 3</code>,
<code>./autotest 4</code> and <code>./autotest 5</code>.
Alternatively, run the command <code>./autotest</code> to test all the test cases. 

<p>
Note that it will actually pass the first test (an empty tree),
because the empty tree has no leaves and no values, which
happens to be what the supplied code assumes. When you
implement your code, make sure that you handle the empty tree
correctly, or else this test might also start failing.
</p>

<h2>Task 1</h2>
<p>
Implement the <code>BSTreeNumLeaves()</code> which returns a count of the number of leaf
nodes in the <code>BSTree</code>. A leaf node is any node with empty left and right subtrees.
The following diagram shows some sample trees, with the leaf nodes highlighted in red.
</p>

<center><img src="Pic/leaves.png" alt="[tree]" /></center>

<h2>Task 2</h2>
<p>
Implement the <code>BSTreeLevelOrder()</code> function which prints the values in the
<code>BSTree</code> in level-order on a single line separated by spaces (i.e. the same
format as the other traverse-and-print functions).
The following diagram aims to give an idea of how level-order traversal scans
the nodes in a tree:
</p>
<center><img src="Pic/levels.png" alt="[tree]" /></center>
<p>
The output from this traversal would be  &nbsp; <code>5  3  7  2  4  6  9  1  8</code>.
</p>
<p>
Level-order traversal cannot be done recursively (at least not easily)
and is typically implemented using a queue.
The algorithm is roughly as follows:
</p>
<pre>
Level Order Traversal (BSTree T):
	initialise queue
	add T's root node to queue
	WHILE the queue still has some entries DO
		take the head of the queue
		print the value from its BSTree node
		add the left child (if any) to the queue
		add the right child (if any) to the queue
	END
END
</pre>
<p>
You must implement this algorithm for the <code>BSTree</code> data type by making use
of the <code>Queue</code> ADT provided. This implements a queue of pointers to
<code>BSTree</code> nodes.
</p>
<p>
Note that you may <em>not</em> change any of the ADT interfaces.
The <em>only</em> file you are allowed to change is <code>BSTree.c</code>.
You can added extra local functions and data to <code>BSTree.c</code> if you wish.
</p>

<h2>Task 3</h2>
<p>
As discussed earlier,the <code>tests</code> directory cpntains 5 test cases and you can test them
using the command <code>autotest</code>. 
You should use these to test your <code>BSTree</code> additions.
</p>
<p>
If the tests fail, you shouldn't rely solely on the test outputs to
try and work out what the problem is.
You will most likely need to add some diagnostic output or use GDB to try to
work out <em>why</em> the tests failed.

<p>
Once your code is working OK, think of two more <em>interesting</em>
test cases and put them in the files <code>tests/6.in</code> and <code>tests/7.in</code>.
What you <em>are</em> required to do is to collect the output from running <code>bst</code>
with your code on these two test cases.
From within the main lab directory (not from within the <code>tests</code> directory)
run the following commands to collect this output:
</p>
<pre>
<kbd is="sh">./bst &lt; tests/6.in &gt; test6.txt</kbd>
<kbd is="sh">./bst &lt; tests/7.in &gt; test7.txt</kbd>
</pre>
<p>
Include the above two <code>test6.txt</code> and <code>test7.txt</code> 
files in your submission.
</p>

<h2>Submission</h2>
<p>
Make the relevant changes to <code>BSTree.c</code> to complete the first two tasks,
and then run your <code>bst</code> program on your new test cases to produce the
<code>test6.txt</code> and <code>test7.txt</code> files.
You need to submit three files: <code>BSTree.c</code>, <code>test6.txt</code> and
<code>test7.txt</code>.
Submit them from the command line via <code>give</code>, and then show your tutor,
who'll give you feedback on your coding style, your test quality, and award a mark.
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
