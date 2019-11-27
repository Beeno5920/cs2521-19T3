
<!DOCTYPE html>
<html>
<head>
  <title>COMP2521 19T3 - Week 01 Lab Exercise</title>
  <link href="https://fonts.googleapis.com/css?family=Lato|Open+Sans:400,600" rel="stylesheet" />
  <link rel="stylesheet" type="text/css" href="/~cs2521/19T3/course.css" /></head>
<body>
  <nav>  
    <div class="left"> <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">COMP2521 19T3</a></div>
    <div class="right"><a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/">Data Structures and Algorithms</a></div>
  </nav>
  <header>
    <span class="heading">Week 01 Lab Exercise</span><br/>
    <span class="subheading">Linked Lists, Performance</span>
  </header>
<h2>Objectives</h2>
<ul>
<li>to re-acquaint you with C programming and ADTs</li>
<li>to manipulate a linked-list data structure</li>
<li>to learn about COMP2521 programming style</li>
<li>to learn (or remind yourself) about Makefiles</li>
<li>to learn about shell scripts to automate repetitive tasks</li>
<li>to do some simple performance analysis</li>
</ul>

<h2>Admin</h2>
<dl class="dl-horizontal">
<dt>Marks</dt><dd>5=outstanding, 4=very good, 3=adequate, 2=sub-standard, 1=hopeless</dd>
<dt>Demo</dt><dd>in the Week 01 Lab or in the Week 02 Lab</dd>
<dt>Submit</dt><dd><code>give cs2521 lab01 IntList.c timing.txt</code> or via WebCMS</dd>
<dt>Deadline</dt><dd>submit by 5pm Sunday of Week-01</dd>
</dl>
<p><small>
Note: you need to do something <em>truly</em> outstanding,
above and beyond the "call of duty" to get 5 marks.
Doing the exercise just as specified will generally get you 4-4.5 marks.
</small></p>

<h2>Background</h2>
<p>
At the end of COMP1511, you dealt with linked lists.  Over the break,
you haven't forgotten linked lists (have you?), but a bit of revision never hurts,
especially when many of the data structures we'll deal with later are
based on linked lists. So ... on with this simple linked list exercise ...
</p>

<h2>Setting Up</h2>
<p>
To keep your files manageable, it's worth doing each lab exercise in a separate directory
(folder).
I'd suggest creating a subdirectory in your home directory called "cs2521",
and then creating a subdirectory under that called "labs",
and then subdirectories "week01", "week02", etc.
Let's assume that the directory you set up for this lab is <em>Week01LabDir</em>.
</p>
<p>
Change into your <em>Week01LabDir</em> directory and run the following command:
</p>
<pre>
<kbd is="sh">unzip <a href="https://www.cse.unsw.edu.au/~cs2521/19T3/labs/week01/lab.zip">/web/cs2521/19T3/labs/week01/lab.zip</a></kbd>
</pre>
<p>
If you're working at home, download <code>lab.zip</code> by right-clicking on the above link
and then run the above command on your local machine.
</p>
<div class="note">
  In the example interactions,
  we assume that you are working at a Linux shell,
  and the shell is giving you a <code>$</code> prompt.
  All the text that you type is in <code><strong>monospace bold</strong></code> font
  and all the text that the shell types at you is in <code>monospace</code> font.
</div>
<p>
If you've done the above correctly, you should now find the following files in the directory:
</p>
<dl class="dl-horizontal">
<dt><code><a href="files/Makefile">Makefile</a></code> </dt>
<dd>a set of dependencies used to control compilation</dd>
<dt><code><a href="files/IntList.h">IntList.h</a></code> </dt>
<dd>interface definition for the IntList ADT</dd>
<dt><code><a href="files/IntList.c">IntList.c</a></code> </dt>
<dd>implementation for the IntList ADT</dd>
<dt><code><a href="files/useIntList.c">useIntList.c</a></code> </dt>
<dd>main program for testing the IntList ADT</dd>
<dt><code><a href="files/randList.c">randList.c</a></code> </dt>
<dd>main program for generating random sequences of numbers</dd>
<dt><code><a href="files/timing.txt">timing.txt</a></code> </dt>
<dd>template for your results file; you need to add more rows</dd>
</dl><p>
Before you start using these programs, it's worth looking at the code.
Are there any constructs that you don't understand? Try to work them out
with your lab partner, or ask your tutor.
</p>
<p>
Once you've understood the programs, the next thing to do is to run the command:
</p>
<pre>
<kbd is="sh">make</kbd>
</pre>
<p>
It's worth taking a look at the <code>Makefile</code> to see if you can work out
what it's doing. Don't worry if you don't understand it all; we'll be taking
a longer look at <code>make</code> in later labs.
Note: you will need to run <code>make</code> to recompile the system each time
you make changes to the source code file and are ready to test the program again.
</p>
<p>
The <code>make</code> command will produce messages,
which show the commands it is running,
and will eventually leave two executable files
in your working directory
(along with some <code>.o</code> files).
</p>
<dl>
<dt><code>useIntList</code></dt>
<dd>
This is the executable for the <code>useIntList.c</code> program.
It reads a list of integers from standard input, then attempts to
make a sorted (ascending order) copy of the list, and then prints
both the original and the sorted lists.
It doesn't work at the moment because the function to produce the
sorted list is incomplete.
</dd>
<dt><code>randList</code></dt>
<dd>
This is the executable for the <code>randList.c</code> program.
It writes, on its standard output, a list of random numbers
in the range 1..999999.
It takes one command-line argument to indicate how many
numbers it should write, and another optional argument to
give a seed for the random number generator.
Note that it does not attempt to eliminate any duplicate
values produced; if you generate a large enough number of
values, duplicates are inevitable.
</dd>
</dl>
<p>
You can run the <code>useIntList</code> command by typing the command name, followed by return.
It will then patiently wait for you to type some numbers, and will store them in a
list, display the list, then call the function that is supposed to sort the list,
and then display the "sorted" list.
Of course, this doesn't currently work, because the list sorting function is incomplete.
You can, however, fake it by typing the numbers in in order, e.g.
</p>
<pre>
<kbd is="sh">./useIntList -v</kbd>
<kbd>1 2 3 4</kbd>
<span class="comment">... type control-D to finish your input</span>
Original:
1
2
3
4
Sorted:
1
2
3
4
</pre>
<p>
When <code>useIntList</code> eventually works properly, this is the kind of output you'll
expect to see ... except that you won't be giving it sorted lists as input.
To see the existing behaviour on an unsorted list, type a few numbers not sorted
in ascending order, e.g.
</p>
<pre>
<kbd is="sh">./useIntList -v</kbd>
<kbd>1 3 2</kbd>
<span class="comment">once again, type control-D to finish your input</span>
Original:
1
3
2
Sorted
1
3
2
useIntList: useIntList.c:20: main: Assertion `IntListIsSorted(myOtherList)' failed.
Aborted
</pre>
<p>
If you omit the <code>-v</code> command-line parameter, the <code>useIntList</code>
program only displays the final sorted list (which is not yet sorted, of course).
</p>
<pre>
<kbd is="sh">./useIntList</kbd>
<kbd>1 3 2</kbd>
<span class="comment">once again, type control-D to finish your input</span>
1
3
2
useIntList: useIntList.c:20: main: Assertion `IntListIsSorted(myOtherList)' failed.
Aborted
</pre>
<p>
Now it's time to play with the list generator.
If you execute the command:
</p>
<pre>
<kbd is="sh">./randList 10</kbd>
</pre>
<p>
it should display a list of 10 random numbers.
If you run it again, you'll get a different list of random numbers.
Enjoy generating small lists of random numbers until you are bored.
</p>
<p>
If you then execute the command:
</p>
<pre>
<kbd is="sh">./randList 10 | ./useIntList</kbd>
</pre>
<p>
the <code>randList</code> command will generate 10 random numbers and give them
to the <code>useIntList</code> command which will print the list of numbers twice
(separated by the word <code>Sorted</code>) and then fail the assertion as
above.
</p>
<div class="note">
If you're not familiar with Unix/Linux conventions, the <code>|</code> is a "pipe" that
connects two commands, e.g. <code><var>C<sub>1</sub></var>|<var>C<sub>2</sub></var></code>.
The standard output (<code>stdout</code>) of the command <code><var>C<sub>1</sub></var></code>
will be directly connected to the standard input (<code>stdin</code>) of the command
<code><var>C<sub>2</sub></var></code>, so that whatever <code><var>C<sub>1</sub></var></code> writes,
<code><var>C<sub>2</sub></var></code> reads.
</div>
<p>
You can adjust the number of numbers that <code>randList</code> generates via the command-line argument, e.g.
</p>
<pre>
<kbd is="sh">./randList 100 | less</kbd>
</pre>
<p>
will produce 100 random numbers. If you want to change the range of numbers produced
(e.g. to only make numbers in the range 1..10) edit the <code>randList.c</code> code
and add extra command-line arguments to set the range.
</p>
<p>
If you supply only one command-line argument, <code>randList</code> will generate a completely
random (well, pseudo-random) sequence each time you run it. If you want to generate a
large sequence of pseudo-random numbers, and be able to generate the same sequence
consistently, you can use the second command-line argument to specify a seed for the
random number generator. If you give the same seed each time you run <code>randList</code>,
you'll get the same sequence each time. To see the difference between using and not
using the second command-line argument, try the following commands:
</p>
<pre>
<kbd is="sh">./randList 10</kbd>
<kbd is="sh">./randList 10</kbd>
<kbd is="sh">./randList 10</kbd>
<kbd is="sh">./randList 10 13</kbd>
<kbd is="sh">./randList 10 13</kbd>
<kbd is="sh">./randList 10 13</kbd>
</pre>
<p>
The first three commands will generate different sequences.
The second three commands all generate the same sequence.
</p>
<p>
While <code>./randList</code> is useful for producing large amounts of data,
you don't need to use <code>./randList</code> to produce input to <code>./useIntList</code>.
An alternative is to use the <code>echo</code> command and enter the numbers
yourself, e.g.
</p>
<pre>
<kbd is="sh">echo 5 4 3 2 1 | ./useIntList</kbd>
</pre>
<p>
Another alternative, which will be more useful for testing, is to use the
<code>seq</code> command, in combination with the <code>sort</code> command, e.g.
</p>
<pre>
<kbd is="sh">seq 10</kbd>
<span class="comment"># gives 1 2 3 4 5 6 7 8 9 10</span>
<kbd is="sh">seq 10 | sort -n</kbd>
<span class="comment"># gives 1 2 3 4 5 6 7 8 9 10</span>
<kbd is="sh">seq 10 | sort -nr</kbd>
<span class="comment"># gives 10 9 8 7 6 5 4 3 2 1</span>
<kbd is="sh">seq 10 | sort -R</kbd>
<span class="comment"># gives 1..10 in a random order</span>
</pre>
<p>
The <code>-nr</code> argument to the <code>sort</code> command tells it to
treat the input as numbers and sort them in reverse order.
The <code>-R</code> argument to the <code>sort</code> command tells it to
put the input in random order.
You can find more details about <code>sort</code> via the command
<code>man&nbsp;sort</code>.
</p>
<p>
One thing to remember is that <code>sort</code> orders items lexically,
not numerically, by default. The following pipeline may not produce
what you expect. Try it.
</p>
<pre>
<kbd is="sh">seq 10 | sort</kbd>
</pre>

<h2>Task 1</h2>
<p>
The <code>IntListInsertInorder()</code> function is incomplete. In fact,
it's just a <em>stub</em> function that invokes the <code>IntListInsert()</code>
function, which inserts the number, but not in order. You should re-write
the <code>IntListInsertInorder()</code> function
so that it takes an <code>IntList</code> and an integer and inserts the value
into the appropriate place in the list, so that the list always remains
sorted (in ascending order). The function should fail if the original list
(before insertion)
is not sorted. Don't forget to handle the cases of (a) empty list,
(b) smallest value, (c) largest value, (d) second-smallest value,
(e) second-largest value, (f) value somewhere in the middle.
Why were these kinds of values chosen? Discuss with your partner
and propose test cases that test these and any other cases that you
can think of.
</p>
<p>
Make a directory called <code>tests</code>,
and place files containing your test cases in that directory
with one test case in each file.
A useful name strategy is to call the test files
<code>01</code>, <code>02</code>, etc.
You could create test files in various ways, e.g.
</p>
<pre>
<kbd is="sh">mkdir tests</kbd>
<kbd is="sh">seq 10 | sort -R &gt; tests/01</kbd>
<kbd is="sh">seq 10 | sort -nr &gt; tests/02</kbd>
<kbd is="sh">./randList 10 11 &gt; tests/03</kbd>
<span class="comment">etc. etc. etc.</span>
</pre>
<p>
In order to check that your program is producing the correct results,
you could compare it to the output of a known correct sorting program.
The <code>diff</code> command can help here (see <code>man diff</code> for details).
For example, you could put each test case in a file, then run both
your <code>useIntList</code> program and the built-in <code>sort</code> command,
save the results of each output in a file, and then compare the files
using <code>diff</code>. If your program is correct, there should be no
difference. The following shows an example of how to do this:
</p>
<pre>
<kbd is="sh">sort -n &lt; tests/01 &gt; tests/01.expected</kbd>      <span class="comment"># generate correct result</span>
<kbd is="sh">./useIntList &lt; tests/01 &gt; tests/01.observed</kbd> <span class="comment"># generate *your* result</span>
<kbd is="sh">diff tests/01.expected tests/01.observed</kbd>    <span class="comment"># if correct, no output</span>
</pre>
<p>
If you produce a decent number of tests (10-20), as you should, then
testing them one by one using the above is a bit tedious.
You could simplify carrying out the testing by writing a small
shell script like:
</p>
<pre>
#!/bin/sh

for t in 01 02 03 04 05 <span class="comment">... and the rest of your test files</span>
do
	echo === Test $t ===
	sort -n &lt; tests/$t &gt; tests/$t.expected
	./useIntList &lt; tests/$t &gt; tests/$t.observed
	diff tests/$t.expected tests/$t.observed
done
rm tests/*.expected tests/*.observed
</pre>
<p>
If you put the above in a file called e.g. <code>run_tests</code>, and then
run the command:
</p>
<pre>
<kbd is="sh">sh run_tests</kbd>
</pre>
<p>
the script will run all your test cases and any that fail will either
produce an assertion message or show you the difference between your
output and the expected output.
</p>
<p>
You will have some confidence that your <code>IntListInsertInorder()</code> function
is working properly when, for all test cases, the assertions in <code>useIntList.c</code>
no longer fail.
</p>

<h2>Task 2</h2>
<!--<p>
Once <code>IntListInsertInorder()</code> is working correctly, modify
<code>useIntList.c</code> so that it behaves as a sorting program: it reads
a list of numbers from its standard input, and writes a sorted version
of the numbers to its standard output. This is a simple change to the
existing program, and can be accomplished by commenting a couple of lines.
</p>-->
<p>
Once <code>IntListInsertInorder()</code> is working correctly, 
run some tests to compare the time taken by <code>useIntList</code>
with the time taken by the Unix <code>sort</code> command for the same task.
</p>
<p>
The first thing to do is to check that both commands are producing the same result
(otherwise, it's not useful to compare them). Try the following commands:
</p>
<pre>
<kbd is="sh">./randList 1000 &gt; nums</kbd>
<kbd is="sh">./useIntList &lt; nums &gt; out1</kbd>
<kbd is="sh">sort -n &lt; nums &gt; out2</kbd>
<kbd is="sh">diff out1 out2</kbd>
</pre>
<p>
If the <code>diff</code> command gives <em>no</em> output, then the files
have no difference (i.e. the observed output is he same as the expected
output).  If you try the above a number of times with different sets of
numbers each time and get the same result, then you can be more confident
that both commands are producing the same result.
(However, you cannot be absolutely certain that they will always produce
the same result for any input. Why not?)
</p>
<p>
Note that you need to use the <code>-n</code> option to <code>sort</code> because the
default sorting order is lexcial, not numeric. If you don't use <code>-n</code>,
then e.g. 111 is treated as being less than 12.
(See <code>man sort</code> for details.)
</p>
<p>
The next thing to do is to devise a set of test cases and collect some timing data.
There is a command called <code>time</code> that will produce the timing data for you.
Use it as follows:
</p>
<pre>
<kbd is="sh">./randList 100000 &gt; nums</kbd>
<kbd is="sh">time ./useIntList &lt; nums &gt; out1</kbd>
<kbd is="sh">time sort -n &lt; nums &gt; out2</kbd>
</pre>
<p>
As before, check that both commands are producing the same result.
This time, however, you will also see output that contains some
timing information (note that the output format may vary depending
on which shell you're using):
</p>
<table border="0" cellpadding="4">
<tr><td>user time</td><td>time spent executing the code of the command</td></tr>
<tr><td>system time</td><td>time spent executing system operations, such as input/output</td></tr>
<tr><td>elapsed/real time</td><td>wall-clock time between when the command starts and finishes</td></tr>
</table>
<p>
The elapsed/real time is affected by the load on the machine, and so
is not reliable. The system time should be similar for both commands
(same amount of input/output). The value that's most useful is the
<code>user time</code>, which represents the time that the program spent
doing computation. Note that the time will vary if you run the same
command multiple times.  This is because the timing uses sampling
and may sample the program at different points during the different
executions. Collect results from a number of executions on the same
output and take an average.
</p>
<p>
You will need to use large numbers of values (large argument to
<code>randList</code>) to observe any appreciable difference. Of course, if you use
very large numbers of values, the <code>nums</code> file may become too large
to store in your directory.  In this case, you could store <code>nums</code>
under the <code>/tmp</code> directory:
</p>
<pre>
<kbd is="sh">./randList 10000 &gt; /tmp/$USER.nums</kbd>
<kbd is="sh">time ./useIntList &lt; /tmp/$USER.nums &gt; /tmp/$USER.out1</kbd>
<kbd is="sh">time sort -n &lt; /tmp/$USER.nums &gt; /tmp/$USER.out2</kbd>
<kbd is="sh">diff /tmp/$USER.out1 /tmp/$USER.out2</kbd>
</pre>
<p>
It would also be worth taking your <code>/tmp/$USER.nums</code> file and
modifying it to check the timings for sorted and reverse sorted
inputs:
</p>
<pre>
<kbd is="sh">sort -n /tmp/$USER.nums &gt; alreadySortedWithDuplicates</kbd>
<kbd is="sh">sort -nr /tmp/$USER.nums &gt; reverseSortedWithDuplicates</kbd>
</pre>
<p>
As well as lists produced by <code>randList</code>, it would be worth trying
lists produced using the <code>seq</code>/<code>sort</code> combinations
mentioned above.
These will be different to the lists produced by <code>randList</code> in
that they won't have any duplicate values.
For example, you could generate data files like:
</p>
<pre>
<kbd is="sh">seq 10000 &gt; alreadySortedNoDuplicates</kbd>
<kbd is="sh">seq 10000 | sort -nr &gt; reverseSortedNoDuplicates</kbd>
<kbd is="sh">seq 10000 | sort -R &gt; randomOrderNoDuplicates</kbd>
</pre>
<p>
and use these in place of <code>/tmp/$USER.nums</code> to generate more timing
data.
</p>
<p>
Once the data files get big enough, and once you've checked that both
programs are producing the same output for a wide selection of cases,
you can avoid generating and comparing large output files by running
the timing commands as follows:
</p>
<pre>
<kbd is="sh">time ./useIntList &lt; /tmp/$USER.nums &gt; /dev/null</kbd>
<kbd is="sh">time sort -n &lt; /tmp/$USER.nums &gt; /dev/null</kbd>
</pre>
<p>
The above commands do all of the computation that we want to measure,
but send their very large output to the Unix/Linux "data sink"
(<code>/dev/null</code>), so it never takes up space on the file system.
</p>
<p>
If you do write results to files, don't forget to remove them after
you've finished the lab.
</p>
<p>
You should take note of the timing output and build a collection of test
results for different sizes/types of input and determine roughly the point at
which it becomes impractical to use <code>useIntList</code> as a sort program
(rather than using the Unix <code>sort</code> command).
</p>
<p>
You'll find
that the timing data for relatively small lists (e.g. up to 10000)
doesn't show much difference between <code>useIntList</code> and <code>sort</code>,
and shows time pretty close to zero.  Try using list sizes such as 5000,
10000, 20000, 50000, 100000, and as high as you dare to go after that.
Also, try varying the kinds of input that you supply. Consider the cases
for the order of the input: random, already sorted, reverse sorted.
Also, consider the proportion of duplicate values in the input, e.g.
all distinct values, some duplicates.
 Note that <code>./randList</code> will
most likely include duplicates as soon as you specify a relatively
large list size.
</p>
<p>
Put your results and some brief comments <span class="red">explaining</span>
the results, in a file called <code>timing.txt</code>.
The file should contain a table of results, with major rows dealing
with a particular size of data, and sub-rows dealing with the order
of the input.
You should have three columns: one to indicate how many runs of each
program were used to compute the average time-cost, one to give the
average time-cost for <code>useIntList</code> and the other to give the average
time-cost for <code>sort</code>.
The table should look something like the following:
</p>
<table>
<thead>
<tr>
 <th><b>Input<br>Size</b></th>
 <th><b>Initial<br>Order</b></th>
 <th><b>Has<br>Duplicates</b></th>
 <th><b>Number<br>of runs</b></th>
 <th><b>Avg Time<br>for useIntList</b></th>
 <th><b>Avg Time<br>for sort</b></th>
</tr>
</thead>
<tbody>
<tr>
 <td>5000</td><td>random</td><td>no</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>5000</td><td>sorted</td><td>no</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>5000</td><td>reverse</td><td>no</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>5000</td><td>random</td><td>yes</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>5000</td><td>sorted</td><td>yes</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>5000</td><td>reverse</td><td>yes</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>10000</td><td>random</td><td>no</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>10000</td><td>sorted</td><td>no</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>10000</td><td>reverse</td><td>no</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>10000</td><td>random</td><td>yes</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>10000</td><td>sorted</td><td>yes</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td>10000</td><td>reverse</td><td>yes</td>
 <td><em>N</em></td><td><em>T<sub>1</sub></em>sec</td><td><em>T<sub>2</sub></em>sec</td>
</tr>
<tr>
 <td><em>etc. etc.</em></td>
</tr>
</tbody>
</table>
<p>
Note that, given the variation in timing output, it's not worth
considering more than two significant figures in your averages.
</p>
<p>
You should also write a short paragraph to <em>explain</em> any
patterns that you notice in the timing results. Don't just re-state
the timing result in words; try to explain <em>why</em> they happened.
</p>
<p>
If you're looking for a challenge, and know how to write scripts,
write e.g. a Linux shell script to automate the testing for you,
and maybe even produce the timing file for you.
</p>
<p>
Another interesting challenge would be to plot graphs using gnuplot,
the R system (available as the Linux command <code>R</code>, a single upper-case letter),
<i>Mathematica</i>, Matlab, or a similar tool.
I'd suggest plotting a separate graph for each type (random,
ascending, descending) for a range of values (e.g. 5000, 10000, 20000,
50000, ... as far as you can be bothered, given how long larger data
files take to sort).
Alternatively, produce your <code>timing.txt</code> as a tab-separated
file and load it into a spreadsheet, from where you could also
produce graphs.
</p>
<p>
If you're feeling brave, try to find out how large input <code>sort</code>
can deal with.  However, you should try such testing on a machine where
you are the sole user. Also, you shouldn't try to store the data files;
use commands like:
</p>
<pre>
<kbd is="sh">seq <var>SomeVeryLargeNumber</var> | time sort -n &gt; /dev/null</kbd>
<kbd is="sh">seq <var>SomeVeryLargeNumber</var> | sort -nr  | time sort -n &gt; /dev/null</kbd>
<kbd is="sh">seq <var>SomeVeryLargeNumber</var> | sort -R | time sort -n &gt; /dev/null</kbd>
</pre>

<h2>Submission</h2>
<p>
You need to submit two files: <code>IntList.c</code> and <code>timing.txt</code>.
You can submit these via the command line using <code>give</code> or you can
submit them from within WebCMS. After submitting them (either in this lab
class or the next) show your tutor, who'll give you feedback on your
coding style, your timing results, and award a mark.
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
