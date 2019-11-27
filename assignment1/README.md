
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
  <link rel="stylesheet" type="text/css" href="assets/bootstrap.css">
  <link rel="stylesheet" type="text/css" href="assets/main.css">
  <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>

  <title>COMP2521 Assignment 1</title>
</head>

<body class="container text-justify" style="max-width: 800px;">
  <h1 class="center">COMP2521 Assignment 1</h1>
  <hr>

  <h1 class="lead center" style="font-size: 2rem;">Textbuffer</h1>
  <h1 class="lead center" style="font-size: 1.2rem;"><a href="#submission">Submission</a></h1>
  <h1 class="lead center" style="font-size: 1.2rem;"><a href="#specification">Specification</a></h1>
  <h1 class="lead center" style="font-size: 1.2rem;"><a href="#faq">Jump to FAQ</a></h1>

  <br>

  <p>Your task is to implement an abstract textbuffer data type that meets the given interface.</p>
  <p>You will submit the C code implementing the textbuffer ADT (<code>textbuffer.c</code>).</p>
  <p>This page describes the interface of the textbuffer ADT that you are to implement. For your implementation, download <code>textbuffer.c</code> below and implement the type <code>struct textbuffer</code> as well as all of the functions whose prototypes are given in the header file <code>textbuffer.h</code>. All your code should go in <code>textbuffer.c</code>, which you have to submit.</p>

  <h1 class="display-3" style="font-size: 2rem">Changelog</h1>
  <b>1st October</b>
  <ul>
    <li>Proofreading</li>
    <li>Line numbers now always start at 1</li>
    <li>Changed <code>charIndex</code> in <code>struct _matchNode</code> to <code>columnNumber</code></li>
    <li>Changed <code>int showLineNumbers</code> in <code>dumpTB</code> to <code>bool showLineNumbers</code></li>
    <li>Added a stub test file <code>testTextbuffer.c</code> for students to write tests</li>
    <li>Improved formatting/style of <code>textbuffer.c</code> and <code>textbuffer.h</code></li>
    <li>Added some clarifications to the spec</li>
  </ul>

  <b>2nd October</b>
  <ul>
    <li>Added clarifications for <code>searchTB</code> to the FAQ</li>
    <li>Added a line to <code>testTextbuffer.c</code> that calls <code>linesTB</code></li>
    <li>Updated the comment for <code>addPrefixTB</code> in <code>textbuffer.c</code> to be consistent with <code>textbuffer.h</code>
  </ul>
  
  <b>3rd October</b>
  <ul>
    <li>Added a clarification for <code>pasteTB</code> to the FAQ</li>
    <li>Added a clarification about bonus marks</li>
    <li>Added a clarification for <code>formRichText</code> - "Note that the <tt>#</tt> character must be the first character in a line <b>and there must be more characters on that line</b> for it to be treated as a special character - otherwise, it does nothing."</li>
    <li>Moved testing for memory leaks from Style Marks to Autotesting Marks</li>
  </ul>
  
  <b>4th October</b>
  <ul>
    <li>Added a question to the FAQ under <code>newTB</code> on the input text being <code>NULL</code>.</li>
    <li>Fixed the answer to one of the <code>newTB</code> questions: "Unless <code>text</code> is the empty string, it will always have a newline at the end."</li>
  </ul>
  
  <b>8th October</b>
  <ul>
    <li>Added details to the FAQ on how <code>diffTB</code> will be tested</li>
    <li>Added an example for <code>diffTB</code> to the FAQ</li>
  </ul>
  
  <b>9th October</b>
  <ul>
    <li>Added details to "<a href="#late-submission">Late Submission</a>" section</li>
    <li>Bonus marks can now only make up for lost marks in the labs and the second assignment - not the midterm exam. Sorry!</li>
  </ul>
  
  <b>11th October</b>
  <ul>
    <li>Removed confusing question about <code>abort</code> from the FAQ</li>
  </ul>
  
  <b>13th October</b>
  <ul>
    <li><a href="#submission">Submission instructions</a> are now available</li>
  </ul>
  
  <b>14th October</b>
  <ul>
    <li>Added a clarification for <code>dumpTB</code> to the FAQ - the returned string should always be allocated such that that the user can free it.</li>
    <li>Added a clarification for <code>searchTB</code> to the FAQ about returning an empty list</li>
  </ul>
  
  <b>15th October</b>
  <ul>
  	<li>Removed the <code>-O</code> flag from the compilation line and replaced it with <code>-g</code>, which supports debugging. (<code>-O</code> is just an optimisation flag, which is unnecessary for this assignment.)</li>
  	<li>Clarified and removed vagueness from the 'Compactness' requirement for <code>diffTB</code>. There is now no 'model solution'. Instead, you'll pass each test if the number of commands in your edit solution is smaller than some threshold, determined by the sizes of the optimal and brute-force solutions (see the section for <code>diffTB</code> for details).</li>
	<li>Added a link to download all dryrun files</li>
	<li>Added clarifications on undoing <code>cutTB</code> and <code>pasteTB</code> to the FAQ.</li>
  </ul>
  
  <b>19th October</b>
  <ul>
  	<li>Added some clarifications/examples based on questions asked on WebCMS.</li>
  </ul>
  
  
  <h1 class="display-3" style="font-size: 2rem">Marks</h1>

  <p>The assignment is worth 10 marks. The mark breakdown is as follows:</p>

  <table class="table" style="margin-left: 10%; margin-right: 10%; width: 80%;">
    <thead>
      <tr>
        <th>Component</th>
        <th>Mark</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>Autotesting of functionality</td>
        <td>8 (+2 bonus)</td>
      </tr>
      <tr>
        <td>Subjective evaluation of style</td>
        <td>2</td>
      </tr>
    </tbody>
  </table>
  
  <p>Due to the bonus challenges, you could get up to 12 marks for the assignment. Any extra marks obtained during this assignment (in excess of the usual 10 marks) can be used to make up for lost marks in the labs and the second assignment.</p>

  <b>Automarking - 8 (+2) Marks</b>
  <p>We will run a number of tests against your textbuffer implementation. These will be much more comprehensive than the tests we run during submission. You get marks for each test you pass.</p>
  
  <p>We will also test your program for memory leaks (memory you have allocated and have responsibility to free but never <code>free</code>'d) and memory errors. Your program will be tested for memory leaks/errors via <code>valgrind</code>.</p>

  <b>Style - 2 Marks</b>
  <p>Style marks will include comments, indentation, variable names, etc., and will also include marks for choosing an appropriate representation for your ADT and for the efficiency of the functions you implement. For example, you will lose marks if your implementation of a function has a time complexity of <code>O(n^2)</code> when there is a solution with a time complexity of <code>O(n)</code> or <code>O(n * log n)</code>.</p>


  <h1 id="submission" class="display-3" style="font-size: 2rem">Submission</h1>
  <div class="alert alert-info">
    <b>Deadline:</b> 9am, Saturday 26 October 2019.
  </div>

  <!--<p>Instructions on how to submit will be available later.</p>-->
  <p>You need to submit one file: <tt>textbuffer.c</tt></p>

  <p>You can submit from the assignment page on WebCMS via the give interface or by running the command below:</p>
  <pre class="codeBlock">give cs2521 assign1 textbuffer.c</pre>
  
  <p>If you have issues submitting via the command line please try submitting via WebCMS.</p>
  
  <p>The submission system runs a few simple dryrun tests. All files used by the dryrun are available <a href="./dryrun/" target="_blank">here</a> (click <a href="./dryrun.zip">here</a> to download the whole lot). After the deadline, all functions will be more thoroughly tested by the automarking system.</p>
  
  <p>You can submit multiple times - only your last submission will count.</p>

  <h1 class="display-3" style="font-size: 1.5rem" id="late-submission">Late Submission</h1>
  <p>A late penalty of 15% per day will be applied. The latest you can submit the assignment is 9am, 31 October 2019, of course with late penalty.</p>

  <h1 class="display-3" style="font-size: 2rem">Files</h1>

  <ol class="breadcrumb">
    <li class="breadcrumb-item"></li>
    <li class="breadcrumb-item"><a href="skeleton/textbuffer.h"><code>textbuffer.h</code></a></li>
  </ol>
  <ol class="breadcrumb">
    <li class="breadcrumb-item"></li>
    <li class="breadcrumb-item"><a href="skeleton/textbuffer.c"><code>textbuffer.c</code></a></li>
  </ol>
  <ol class="breadcrumb">
    <li class="breadcrumb-item"></li>
    <li class="breadcrumb-item"><a href="skeleton/testTextbuffer.c"><code>testTextbuffer.c</code></a></li>
  </ol>

  </ol>
  <p><b>Note:</b> When we test your assignment, it with be compiled with <code>gcc</code> and the following flags:<p>

  <pre class="codeBlock">gcc -Wall -Werror -std=c11 -g -lm -o testTextbuffer testTextbuffer.c textbuffer.c</pre>
  
  <p><b>Note:</b> The above command may not properly link the math library when you are working on your local machine. To solve this problem, try moving <tt>-lm</tt> to the end of the command, as follows:</p>
  <pre class="codeBlock">gcc -Wall -Werror -std=c11 -g -o testTextbuffer testTextbuffer.c textbuffer.c -lm</pre>

  <!--
  <p>You may run some very basic auto tests by running the following command on a CSE system while in the directory with your <code>textbuffer.c</code> file</p>

  <pre class="codeBlock">2521 ass1_test</pre>
  -->

  <br>
  <h1 id="specification" class="center">ADT Specification</h1>
  <hr>
  <h1 class="lead center" style="font-size: 2rem;">The following is a description of the components of the interface.</h1>
  <br>
  <div class="alert alert-danger">
    As marks are awarded by an automated marking program, you must follow this specification precisely. Otherwise, you risk getting few or no marks! You must <b>NOT</b> modify the <tt>textbuffer.h</tt> file.
  </div>

  <h1 class="display-3" style="font-size: 2rem">The ADT type</h1>

  <p>We represent the ADT by way of a handle of type <code>TB</code>. The handle type is declared in the header file, but you will have to provide an implementation of the handle representation - i.e. of <code>struct textbuffer</code> - as part of your implementation:</p>

  <p><code>typedef struct textbuffer *TB;</code></p>

  <p>Refer to the lecture about ADTs for examples of this construction.</p>

  <h1 class="display-3" style="font-size: 2rem">Required properties of the implementation</h1>
  <p>A textbuffer is an ordered collection of strings, where each string represents one line of a text file. <b>Your implementation must keep the lines of a textbuffer in a linked data structure</b> (such as a linked list or a variant of that). Each line must be represented as a (dynamically allocated) string. Adding, deleting, or moving lines requires manipulation of the linked structure. Such a data structure may, for example, be used as part of a text editor.</p>


  <h1 class="display-3" style="font-size: 2rem">Constructor and destructor</h1>

  <h1 class="display-3" style="font-size: 1.5rem">newTB</h1>
  <p><code>TB newTB (char *text);</code></p>
  <p><code>newTB</code> allocates a new textbuffer and initialises its contents with the text in the given string. Each fragment of the string that ends with a newline character (<code>'\n'</code>) indicates a separate line in the textbuffer.</p>

  


  <h1 class="display-3" style="font-size: 1.5rem">releaseTB</h1>
  <p><code>void releaseTB (TB tb);</code></p>
  <p><code>releaseTB</code> frees the memory occupied by the given textbuffer. It is an error to access a textbuffer after freeing it.</p>


  <h1 class="display-3" style="font-size: 2rem">Query functions</h1>

  <div class="alert alert-info">The following functions do not alter their textbuffer argument.</div>

  <h1 class="display-3" style="font-size: 1.5rem">dumpTB</h1>
  <p><code>char *dumpTB (TB tb, bool showLineNumbers);</code></p>
  <p><code>dumpTB</code> allocates and returns a string containing the text in the given textbuffer. The returned string should contain newline characters (<code>'\n'</code>) to indicate the end of each line in the textbuffer. It is the caller's responsibility to free the memory occupied by the returned string. If there are no lines in the textbuffer, return an empty string (the string should still be allocated). If <code>showLineNumbers</code> is <code>true</code>,  prepend a line number (along with a dot and space) to each line of the output.</p>
  <p>For example, if <code>dumpTB</code> was called on a textbuffer containing the lines <code>"hello world"</code> and <code>"amazing"</code>, and <code>showLineNumbers</code> was <code>true</code>, it should return <code>"1. hello world\n2. amazing\n"</code>. If <code>showLineNumbers</code> was <code>false</code>, it should instead return <code>"hello world\namazing\n"</code>.</p>

  

  <h1 class="display-3" style="font-size: 1.5rem">linesTB</h1>
  <p><code>int linesTB (TB tb);</code></p>
  <p><code>linesTB</code> returns the number of lines in the given textbuffer.</p>


  <h1 class="display-3" style="font-size: 2rem">Textbuffer editing</h1>

  <div class="alert alert-info">For all editing functions, if any of the arguments indicating a line number is out of range (i.e., smaller than 1 or bigger than the number of lines in the textbuffer), the function must print a suitable error message and terminate the program with the standard function <tt>abort()</tt>.</div>
  <div class="alert alert-info">The first line of a textbuffer is at position/index 1.</div>

  <h1 class="display-3" style="font-size: 1.5rem">addPrefixTB</h1>
  <p><code>void addPrefixTB (TB tb, int from, int to, char *prefix);</code></p>
  <p><code>addPrefixTB</code> adds the supplied prefix to all lines between <code>from</code> and <code>to</code> (inclusive). If <code>to</code> is less than <code>from</code>, abort.</p>

  <p>For example, consider calling <code>addPrefixTB (tb, 1, 3, "goodnight ")</code>:</p>
<pre class="codeBlock">
+ ---------------------------- +        + ------------------------------------ +
| room                         |        | goodnight room                       |
| moon                         |  --->  | goodnight moon                       |
| cow jumping over the moon    |        | goodnight cow jumping over the moon  |
| light                        |        | light                                |
+ ---------------------------- +        + ------------------------------------ +
</pre>

  <h1 class="display-3" style="font-size: 1.5rem">deleteTB</h1>
  <p><code>void deleteTB (TB tb, int from, int to);</code></p>
  <p><code>deleteTB</code> deletes the lines between <code>from</code> and <code>to</code> (inclusive) from the textbuffer <code>tb</code>. It should free the memory of the deleted lines. If <code>to</code> is less than <code>from</code>, abort.</p>

  <h1 class="display-3" style="font-size: 2rem">Combining textbuffers</h1>

  <div class="alert alert-info">For all combining functions, if any of the arguments indicating a line number is out of range, the function must print a suitable error message and terminate the program with the standard function <tt>abort()</tt>.</div>
  <p>Note that for these functions, if the number of lines in <code>tb1</code> is <code>n</code>, then <code>n + 1</code> is a valid argument for <code>pos</code> (the lines in <code>tb2</code> are added to the end of <code>tb1</code>).</p>

  <h1 class="display-3" style="font-size: 1.5rem">mergeTB</h1>
  <p><code>void mergeTB (TB tb1, int pos, TB tb2);</code></p>
  <p><code>mergeTB</code> merges <code>tb2</code> into <code>tb1</code> at line <code>pos</code>. Afterwards, what was at line 1 of <code>tb2</code> will now be at line <code>pos</code> of <code>tb1</code>. Line <code>pos</code> of <code>tb1</code> will be moved to line <code>pos + linesTB (tb2)</code>, after the merged-in lines from <code>tb2</code>. After this operation, <code>tb2</code> cannot be used anymore (as if we had used <code>releaseTB</code> on it).</p>

  <h1 class="display-3" style="font-size: 1.5rem">pasteTB</h1>
  <p><code>void pasteTB (TB tb1, int pos, TB tb2);</code></p>
  <p><code>pasteTB</code> copies (i.e., pastes) all lines from <code>tb2</code> into <code>tb1</code> at line <code>pos</code>. It is like <code>mergeTB</code>, but <code>tb2</code> remains unmodified and is still usable independent of <code>tb1</code>.</p>


  <h1 class="display-3" style="font-size: 2rem">Extracting textbuffers</h1>

  <div class="alert alert-info">For all extracting functions, if any of the arguments indicating a line number is out of range, the function must print a suitable error message and terminate the program with the standard function <tt>abort()</tt>.</div>

  <p>The textbuffers returned by the extracting functions are as if they were newly created with <code>newTB()</code>.</p>

  <h1 class="display-3" style="font-size: 1.5rem">cutTB</h1>
  <p><code>TB cutTB (TB tb, int from, int to);</code></p>
  <p><code>cutTB</code> cuts the lines between <code>from</code> and <code>to</code> (inclusive) out of the textbuffer <code>tb</code> into a new textbuffer, which is then returned. If <code>to</code> is less than <code>from</code>, return <code>NULL</code>.</p>
  

  <h1 class="display-3" style="font-size: 2rem">Searching textbuffers</h1>

  
  <p><code>Match searchTB (TB tb, char *search);</code></p>
  <p><code>searchTB</code> returns a linked list of all non-overlapping matches in <code>tb</code> of a certain string. The search is <b>case sensitive</b> and the textbuffer <code>tb</code> must remain unmodified. The matches must be returned in order of their appearance in the textbuffer. It is the caller's responsibility to free the returned list.</p>

  <p>Consider calling <code> searchTB (tb, "love")</code> on the following TB:</p>

<pre class="codeBlock">
<span>1</span> Hello World My
<span>2</span> name is jarred lovegood
<span>3</span> and i love carley ray jepson
</pre>

  <p>This should return a list:</p>

<pre class="codeBlock">
+====================+    +====================+
| lineNumber: 2      |    | lineNumber: 3      |
| columnNumber: 16   |    | columnNumber: 7    |
| next: ----------------->| next: -----------------> NULL
+====================+    +====================+
</pre>

  <div class="alert alert-info">
    Note that the line number and column number are both <b>1-indexed</b> (i.e., start at 1). The column number refers to a position within the line where there is a match.
  </div>
  <div class="alert alert-info">
    Note that <tt>Match</tt> is a pointer to the first node in the list. If there are no matches, then return <tt>NULL</tt>.
  </div>


  <h1 class="display-3" style="font-size: 2rem">Rich text</h1>
  <h1 class="display-3" style="font-size: 1.5rem">formRichText</h1>
  <p><code>void formRichText (TB tb);</code></p>
  <p><code>formRichText</code> searches every line of <code>tb</code> and performs the following substitutions:</p>

  <table class="table">
    <thead>
      <tr>
        <th>String</th>
        <th>Replacement</th>
        <th>Example</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><pre>*some string*</pre></td>
        <td><pre>&lt;b&gt;some string&lt;/b&gt;</pre></td>
        <td><pre>*hello* -> &lt;b&gt;hello&lt;/b&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>_some string_</pre></td>
        <td><pre>&lt;i&gt;some string&lt;/i&gt;</pre></td>
        <td><pre>_hello_ -> &lt;i&gt;hello&lt;/i&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>#some string ...</pre></td>
        <td><pre>&lt;h1&gt;some string ...&lt;/h1&gt;</pre></td>
        <td><pre>#hello -> &lt;h1&gt;hello&lt;/h1&gt;</pre></td>
      </tr>
    </tbody>
  </table>

  <p>The matching is simplistic in that you would begin scanning at the first special character and continue to consume characters (ignoring any further special characters) until a matching special character. If there is no matching special character, nothing is done and the next special character (if there is one) is processed.</p>
  <p>Note that the <tt>#</tt> character must be the first character in a line and there must be more characters on that line for it to be treated as a special character - otherwise, it does nothing. Furthermore, it matches until the end of the line and not until a matching <tt>#</tt>. See example below.</p>
  <table class="table">
    <thead>
      <tr>
        <th>Example</th>
        <th>Result</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><pre>*some string</pre></td>
        <td><pre>*some string</pre></td>
      </tr>
      <tr>
        <td><pre>*some string*lol*</pre></td>
        <td><pre>&lt;b&gt;some string&lt;/b&gt;lol*</pre></td>
      </tr>
      <tr>
      	<td><pre>* *</pre></td>
      	<td><pre>&lt;b&gt; &lt;/b&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>*some_string*again_</pre></td>
        <td><pre>&lt;b&gt;some_string&lt;/b&gt;again_</pre></td>
      </tr>
      <tr>
        <td><pre>*some* _string_</pre></td>
        <td><pre>&lt;b&gt;some&lt;/b&gt; &lt;i&gt;string&lt;/i&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>some *string_again_</pre></td>
        <td><pre>some *string&lt;i&gt;again&lt;/i&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>some#string*once_again*</pre></td>
        <td><pre>some#string&lt;b&gt;once_again&lt;/b&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>#string_stuff_</pre></td>
        <td><pre>&lt;h1&gt;string_stuff_&lt;/h1&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>#</pre></td>
        <td><pre>#</pre></td>
      </tr>
      <tr>
        <td><pre>###</pre></td>
        <td><pre>&lt;h1&gt;##&lt;/h1&gt;</pre></td>
      </tr>
    </tbody>
  </table>

  <p>In the case of nested special characters, for example:</p>
<pre class="codeBlock">
*some_string_*
#some _string_
</pre>
  <p>Take the outermost element and ignore any nesting.</p>

  <table class="table">
    <thead>
      <tr>
        <th>Example</th>
        <th>Result</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><pre>*some_string_*</pre></td>
        <td><pre>&lt;b&gt;some_string_&lt;/b&gt;</pre></td>
      </tr>
      <tr>
        <td><pre>#some _string_</pre></td>
        <td><pre>&lt;h1&gt;some _string_&lt;/h1&gt;</pre></td>
      </tr>
    </tbody>
  </table>

  <p>If there are no characters between a pair of consecutive special characters, for example, <code>hello ** world</code>, ignore it and continue to the next pair of special characters (if there is one). For example:</p>

<pre class="codeBlock">
hello ** world    --> hello ** world
hello **world*    --> hello *&lt;b&gt;world&lt;/b&gt;
hello **world**   --> hello *&lt;b&gt;world&lt;/b&gt;*
**hello***world** --> *&lt;b&gt;hello&lt;/b&gt;*&lt;b&gt;world&lt;/b&gt;*
***hello*         --> **&lt;b&gt;hello&lt;/b&gt;
</pre>

  <p>Note that in the last case, the first <code>*</code> does nothing because there are no characters between it and the next <code>*</code>. In that case the first <code>*</code> is ignored and the next one is processed as normal.</p>

  <!------------------------------------------------------------------->

  <h1 class="display-3" style="font-size: 2rem">Assignment 1 Bonus Challenges</h1>
  <h1 class="display-3" style="font-size: 1.5rem">diffTB (1 bonus mark)</h1>
  <p><code>char *diffTB (TB tb1, TB tb2);</code></p>
  <p>Given two text files, we sometimes want to know what changes are made from one file to another file.</p>

  <p>The function <code>diffTB</code> works out which lines of texts are added or deleted from <code>tb1</code> to get <code>tb2</code>. The string returned from the function is an edit solution consisting of a series of add and delete commands. Applying such commands on <code>tb1</code> <b>in sequence</b> should result in <code>tb2</code>.</p>

  <p>An edit solution should have one command per line to either add or delete a line of text at a specific line number. An example is given below. The first command adds a line of text 'add this line please' at line 2 of the current textbuffer (counting from 1). The existing line 2 is moved to line 3, and so on. The second command deletes line 3 of the textbuffer. The last command adds the specified text at line 12 of the textbuffer.</p>

<pre>
+,2,add this line please
-,3
+,12,add this line as well please
</pre>

  <p>A mark is given if your solution satisfies two criteria given below:</p>
  <ul>
    <li><p><em>Correctness</em> - applying your edit solution on <code>tb1</code> results in <code>tb2</code>.</p></li>
    <li><p><em>Compactness</em> - the size of your edit solution (i.e., number of commands/lines) is smaller than or equal to the average of the sizes of the optimal solution and the brute-force solution (which is "delete all lines of <code>tb1</code> and add all lines of <code>tb2</code>"). This is to avoid brute-force solutions, such as the one just described.</p></li>
  </ul>

  <h1 class="display-3" style="font-size: 1.5rem">undoTB and redoTB (1 bonus mark)</h1>

  <p><code>void undoTB (TB tb);</code></p>
  <p><code>undoTB</code> allows the user to reverse up to 10 of the most-recently called operations on <code>tb</code>. Applicable operations are: <code>deleteTB</code>, <code>mergeTB</code>, <code>pasteTB</code>, and <code>cutTB</code>. Each time <code>undoTB</code> is called, one operation is reversed on <code>tb</code>. When the maximum number of allowable undo operations is reached, further calls to <code>undoTB</code> should do nothing (until one of the applicable operations is performed again or <code>redoTB</code> is called).</p>

  <p><code>void redoTB (TB tb);</code></p>
  <p>The function <code>redoTB</code> allows the user to redo operations that have been reversed by <code>undoTB</code>. Similar to <code>undoTB</code>, this function should redo one operation on <code>tb</code> per function call. However, when a new operation is called on <code>tb</code>, any reversed operations cannot be executed again with <code>redoTB</code>.</p>

  
  <div class="alert alert-info"><b>Note:</b> When testing your <tt>undoTB</tt> and <tt>redoTB</tt> functions, we will not call inapplicable operations such as <tt>addPrefixTB</tt> and <tt>formRichText</tt>, so you do not have to worry about undoing such operations.</div>
  
  <!------------------------------------------------------------------->

  <h1 class="lead center" style="font-size: 2rem;" id="faq">COMP2521 Assignment 1 FAQ</h1>
  <hr>
  <h1 class="display-3" style="font-size: 2rem">General questions</h1>

  <dl>
    <dt>Can I modify <code>textbuffer.h</code>?</dt>
    <dd style="margin-left: 2rem; margin-top: 1rem;"><p><big><big><big><big><strong>No.</strong></big></big></big></big></p></dd>

    <dt>Can I add my own structs and functions to <code>textbuffer.c</code>?</dt>
    <dd><p>Yes! Make sure your helper functions are declared <code>static</code>, and that you document what the functions and structures you add are for.</p></dd>

    <dt>Can I use functions from <code>&lt;string.h&gt;</code>?</dt>
    <dd><p>Yes. It's much, much harder if you don't.</p></dd>

    <dt>Will I need to check my code with <code>valgrind</code>?</dt>
    <dd><p>We'll certainly be checking your submission with <code>valgrind</code> for memory leaks.</p></dd>

    <dt>Can <code>TB</code> ever be <code>NULL</code>?</dt>
    <dd><p>It can be in the case something goes wrong but in any case you have a <code>TB</code> which is <code>NULL</code> the correct course of action would be to print a suitable error message and <code>abort()</code>.</p></dd>
    
    <dt>Can I use the <code>math.h</code> library?</dt>
    <dd><p>Yes.</p></dd>
    
    <dt>Will the time complexity of bonus functions affect the bonus marks?</dt>
    <dd><p>No.</p></dd>
  </dl>

  <h1 class="display-3" style="font-size: 2rem;">newTB</h1>
  <dl>
    <dt>How does <code>newTB</code> work?</dt>
    <dd><p>If the input text is, for example, <code>"Hi there,\nhow\nare\nthings\n"</code>, the textbuffer should contain the following lines: <code>{ "Hi there,", "how", "are", "things" }</code>. You will have to process the input text, extract all the substrings separated by newlines, and copy them into your textbuffer structure.</p></dd>

    <dt>Should I leave the <code>'\n'</code> characters in?</dt>
    <dd><p>Depending on your approach to splitting text, they may already be gone. The only other place you need the <code>'\n'</code> characters is in <code>dumpTB</code>, so you could probably get away without storing them. But it is up to you.</p></dd>

    <dt>Is it safe to assume that the input text will always have a newline at the end?</dt>
    <dd><p>Unless <code>text</code> is the empty string, it will always have a newline at the end.</p></dd>

    <dt>What should happen with multiple consecutive newlines?</dt>
    <dd><p>Every newline marks a new line in the textbuffer, so a newline that immediately follows another newline (or a newline at the beginning of the input text) would represent an empty line. You need to track empty lines.</p></dd>

    <dt>Can I assume a maximum length for lines?</dt>
    <dd><p>No. Your program should be able to dynamically allocate any memory needed for your strings depending on the input text.</p></dd>

    <dt>What if the input text is a empty string?</dt>
    <dd><p>Create an empty TB.</p></dd>

    <dt>What if the input text consists of just a single newline character?</dt>
    <dd><p>Create a TB with one empty line.</p></dd>
    
    <dt>What if the input text is <code>NULL</code>?</dt>
    <dd><p>We won't be testing this (as <code>NULL</code> is not a valid string), but in this case a sensible thing to do would be to print a suitable error message and <code>abort()</code>.</p></dd>
  </dl>


  <h1 class="display-3" style="font-size: 2rem">releaseTB</h1>
  <dl>
    <dt>How can I test <code>releaseTB</code>?</dt>
    <dd>
      <p>You can't. You can't write a black-box test for a destructor.</p>
      <p>When you <code>free()</code> memory, what you're saying is that you no longer need the block of memory you had a pointer to; it should be irrelevant to you whether that memory's value changes or becomes invalid in some way, because <strong>you are absolutely forbidden from accessing the memory once free'd</strong>. Use-after-free is an illegal and undefined operation.</p>
      <p>A good test that your <code>releaseTB</code> worked is that your program is still running after you do so.</p>
      <p>Do note though that <code>valgrind</code> may be useful to help diagnose memory leaks which can indirectly signal a error with your <code>releaseTB</code>.</p>
    </dd>
  </dl>


  <h1 class="display-3" style="font-size: 2rem">dumpTB</h1>
  <dl>
    <dt>My textbuffer has no lines; what should <code>dumpTB</code> return?</dt>
    <dd><p>It should return an empty string, regardless of whether <code>showLineNumbers</code> is <code>true</code> or <code>false</code>. Note that this string should still be allocated so that the user can free it.</p></dd>
  </dl>

  <h1 class="display-3" style="font-size: 2rem">addPrefixTB</h1>
  <dl>
    <dt>Can the prefix string have newlines in it?</dt>
    <dd><p>No. We will not test these cases.</p></dd>

    <dt>Can the prefix string be the empty string?</dt>
    <dd><p>Yes. In this case, do nothing.</p></dd>

    <dt>Can the prefix string be <code>NULL</code>?</dt>
    <dd><p>No. In this case, <code>abort()</code>.</p></dd>
  </dl>


  <h1 class="display-3" style="font-size: 2rem">mergeTB</h1>
  <dl>
    <dt>What should happen if I <code>mergeTB (tb1, 1, tb1)</code>?</dt>
    <dd><p>Attempts to merge a textbuffer with itself should be ignored.</p></dd>

    <dt>Should I call <code>releaseTB</code> as well?</dt>
    <dd><p><strong>No!</strong> This will probably destroy both the source and destination textbuffers. However, you've moved the contents of the source textbuffer, so you can just <code>free()</code> as you would in <code>releaseTB</code>. You must not subsequently dereference it; that's a use-after-free and <small>(say it with me, folks!)</small> use-after-free is illegal.</p></dd>

    <dt>Can I concatenate text buffers with <code>mergeTB</code>?</dt>
    <dd>
      <p>The correct behaviour should be as follows, for <code>mergeTB (dest, pos, src)</code>:</p>
      <ul>
        <li><p><code>pos == 1</code>: Insert <code>src</code> before the start of <code>dest</code>.</p></li>
        <li><p><code>pos == linesTB (dest)</code>: Insert <code>src</code> before the last line of <code>dest</code>.</p></li>
        <li><p><code>pos == linesTB (dest) + 1</code>: Append <code>src</code> to the end of <code>dest</code>.</p></li>
      </ul>
    </dd>

    <dt>What should happen if <code>tb1</code> or <code>tb2</code> are empty?</dt>
    <dd><p>Both may be empty. If <code>dest</code> is empty then the only valid value for <code>pos</code> is 1, which would cause <code>src</code> to be appended to the end of the empty TB.</p></dd>
  </dl>

  <h1 class="display-3" style="font-size: 2rem">pasteTB</h1>
  <dl>
    <dt>Can a textbuffer be pasted onto itself?</dt>
    <dd>
      <p>Yes! For example, suppose <code>tb</code> was:</p>
<pre class="codeBlock">
<span>1</span> Never gonna give you up
<span>2</span> Never gonna let you down
</pre>
      <p>Then after calling <code>pasteTB (tb, 2, tb)</code>, <code>tb</code> would look like:</p>
<pre class="codeBlock">
<span>1</span> Never gonna give you up
<span>2</span> Never gonna give you up
<span>3</span> Never gonna let you down
<span>4</span> Never gonna let you down
</pre>
    </dd>
  </dl>

  <h1 class="display-3" style="font-size: 2rem">searchTB</h1>
  <dl>
    <dt>Can the search string have newlines in it?</dt>
    <dd><p>No. We will not test these cases.</p></dd>

    <dt>Can the search string be the empty string? </dt>
    <dd><p>Yes. In this case, return an empty list.</p></dd>

    <dt>How should I return an empty list?</dt>
    <dd><p>In general, this depends on the representation of the list. If the list is represented by a structure containing metadata about the list (such as its size, the pointer to the first node, etc.), like in the Week 1 and Week 2 labs, then an empty list is represented by a (pointer to a) metadata structure where the size field is set to 0, and the pointers to the first/last nodes are set to <code>NULL</code>. If the list is represented by a pointer to the first node, then an empty list is represented by a <code>NULL</code> pointer, as there are no nodes in the list. In this assignment, because a list of matches is merely represented by a pointer to the first match node, an empty list is represented by <code>NULL</code>.</p></dd>

    <dt>Can the search string be the NULL?</dt>
    <dd><p>No. In this case, <code>abort()</code>.</p></dd>

    <dt>Can the search string occur multiple times on the same line?</dt>
    <dd>
      <p>Yes. In this case, the returned list of matches should have a node for each of the occurrences on that line. For example, if <code>searchTB (tb, "bird")</code> is called, and <code>tb</code> is:</p>
<pre class="codeBlock">
<span>1</span> A well a everybody's heard about the bird
<span>2</span> B-b-b bird, bird, bird, b-bird's the word
<span>3</span> A well a bird, bird, bird, the bird is the word
<span>4</span> A well a bird, bird, bird, well the bird is the word
<span>5</span> A well a bird, bird, bird, b-bird's the word
</pre>
      <p>The returned list should be:</p>
<pre class="codeBlock">
(1, 38) --> (2, 7) --> (2, 13) --> (2, 19) --> (2, 27) --> (3, 10) --> (3, 16) --> ...
</pre>
    </dd>

    <dt>How do you handle the case where the search string is a repeated pattern (e.g., looking for 'abab' in 'ababab')?</dt>
    <dd>
      <p>The matches you return should not overlap. After you find a match on a line, the search should resume from <i>after</i> the part of the line that was matched. For example, if we searched for <code>"abracadabra"</code> in the string <code>"abracadabracadabracadabracadabra"</code>, the matches are <code>"<u>abracadabra</u>cad<u>abracadabra</u>cadabra"</code>. So if we searched for <code>"abracadabra"</code> in this textbuffer:</p>
<pre class="codeBlock">
<span>1</span> abracadabra alacazam
<span>2</span> abracadabracadabracadabracadabra
</pre>
      <p>The returned list should be:</p>
<pre class="codeBlock">
(1, 1) --> (2, 1) --> (2, 15) --> X
</pre>
    </dd>
  </dl>

  <h1 class="display-3" style="font-size: 2rem">formRichText</h1>
  <dl>
    <dt>How should I handle cases where there are no characters between a pair of special characters (such as <code>**</code>)?</dt>
    <dd><p>In this case, nothing should happen. Only add the tags if there is at least 1 character being acted on.</p></dd>
    <dt>Can substitutions occur across lines?</dt>
    <dd><p>No.</p></dd>
  </dl>


  <h1 class="display-3" style="font-size: 2rem">diffTB</h1>
  <dl>
    <dt>Does <code>diffTB</code> change either of its textbuffer arguments?</dt>
    <dd><p>No. <code>diffTB</code> is non-destructive.</p></dd>
    
    <dt>How will <code>diffTB</code> be tested?</dt>
    <dd>
      <p>There are many possible valid sequences of commands that could be returned from <code>diffTB</code>, so comparing the output against an expected output would not work. Instead, we will parse your edit solution and apply the commands one by one to <code>tb1</code>. After applying the commands, we will call <code>dumpTB</code> on <code>tb1</code> and <code>tb2</code>. If they return the same string, and your edit solution consists of fewer commands than the threshold, then you pass the test.<p>
    </dd>
    
    <dt>Could we get an example?</dt>
    <dd>
      <p>Certainly!</p>
      <p>Suppose that these are <code>tb1</code> (left) and <code>tb2</code> (right):</p>
<pre class="codeBlock">
<span>1</span> first line                            <span>1</span> first line
<span>2</span> second line                           <span>2</span> 2nd line
<span>3</span> third line                            <span>3</span> third line
<span>4</span> fourth line                           <span>4</span> quatre
</pre>
      <p>Here are some examples of correct command strings (there are others):</p>
<pre class="codeBlock">
"+,2,2nd line\n-,3\n+,4,quatre\n-,5\n"
"-,2\n+,2,2nd line\n-,4\n+,4,quatre\n"
"-,2\n-,3\n+,2,2nd line\n+,4,quatre\n"
"-,4\n-,2\n+,3,quatre\n+,2,2nd line\n"
</pre>
    </dd>
  </dl>


  <h1 class="display-3" style="font-size: 2rem">undoTB and redoTB</h1>
  <dl>
    <dt>My implementation of <code>undoTB</code> and <code>redoTB</code> requires me to modify existing functions (e.g., <code>mergeTB</code>), which affects their time complexities. Will I be penalised for having a slow time complexity for these functions?</dt>
    <dd><p>Your implementation of the applicable functions will probably be split into two parts: (1) one part that allows <code>undoTB</code> and <code>redoTB</code> to work, and (2) a second part that actually does the main work of the function. In checking your functions' time complexities we will only consider the second part of the code.</p></dd>
    
    <dt>Should I record an operation that has no effect on the TB, such as merging an empty textbuffer?</dt>
    <dd><p>It's up to you - we won't be testing these cases.</p></dd>
    
    <dt>What should happen if I undo a merge? Is <code>tb2</code> alive again?</dt>
    <dd><p>If you called <code>mergeTB (dest, pos, src)</code>, <code>src</code> no longer exists, so calling <code>undoTB (src)</code> is invalid. Calling <code>undoTB (dest)</code> should simply remove the merged lines from <code>dest</code> (of course, they may reappear again if <code>redoTB (dest)</code> is called).</p></dd>
    
    <dt>What should happen if I undo a cut?</dt>
    <dd><p>If you called <code>cutTB (tb1, from, to)</code>, the returned TB (let's call it <code>tb2</code>) is completely independent of <code>tb1</code>. Calling <code>undoTB (tb1)</code> should restore the lines that were cut from <code>tb1</code>, but have no effect on <code>tb2</code>.</p></dd>
    
    <dt>What should happen if I undo a paste?</dt>
    <dd><p>If you called <code>pasteTB (tb1, pos, tb2)</code>, the paste operation is performed on <code>tb1</code>, not <code>tb2</code>, so <code>tb2</code> has no record of the operation taking place. Thus, calling <code>undoTB (tb1)</code> should remove the pasted lines from <code>tb1</code> (they may reappear if <code>redoTB (tb1)</code> is called), while calling <code>undoTB (tb2)</code> should do nothing unless some operation was performed on <code>tb2</code> before the paste.</p></dd>
  </dl>
  
  <!------------------------------------------------------------------->

  <hr>

  <h1 class="display-3" style="font-size: 2rem">Plagiarism</h1>

  <p>This is an individual assignment. Each student will have to develop their own solution without help from other people. In particular, it is not permitted to exchange code or pseudocode. You are not allowed to use code developed by persons other than yourself. If you have questions about the assignment, ask your tutor.</p>

  <p><b>Plagiarism</b> is <a href="https://student.unsw.edu.au/plagiarism">defined as</a> using the words or ideas of others and presenting them as your own. UNSW and CSE treat plagiarism as academic misconduct, which means that it carries penalties as severe as being excluded from further study at UNSW. There are several on-line sources to help you understand what plagiarism is and how it is dealt with at UNSW:</p>
  <ul>
    <li>
      <a href="https://student.unsw.edu.au/plagiarism">
        Plagiarism and Academic Integrity
      </a>
    </li>
    <li>
      <a href="https://www.gs.unsw.edu.au/policy/documents/plagiarismprocedure.pdf">
        UNSW Plagiarism Procedure
      </a>
    </li>
  </ul>

  <p>Make sure that you read and understand these. Ignorance is not accepted as an excuse for plagiarism. In particular, you are also responsible that your assignment files are not accessible by anyone but you by setting the correct permissions in your CSE directory and code repository, if using. Note also that plagiarism includes paying or asking another person to do a piece of work for you and then submitting it as your own work.</p>

  <p>UNSW has an ongoing commitment to fostering a culture of learning informed by academic integrity. All UNSW staff and students have a responsibility to adhere to this principle of academic integrity. Plagiarism undermines academic integrity and is not tolerated at UNSW. Plagiarism at UNSW is defined as using the words or ideas of others and passing them off as your own.</p>

  <p>If you haven't done so yet, please take the time to read the full text of</p>
  <ul>
    <li>
      <a href="https://student.unsw.edu.au/plagiarism">
        UNSW's policy regarding academic honesty and plagiarism
      </a>
    </li>
  </ul>

  <p>The pages below describe the policies and procedures in more detail:</p>
  <ul>
    <li>
      <a href="https://www.gs.unsw.edu.au/policy/documents/studentcodepolicy.pdf">
        Student Code Policy
      </a>
    </li>
    <li>
      <a href="https://www.gs.unsw.edu.au/policy/documents/studentmisconductprocedures.pdf">
        Student Misconduct Procedure
      </a>
    </li>
    <li>
      <a href="https://www.gs.unsw.edu.au/policy/documents/plagiarismpolicy.pdf">
        Plagiarism Policy Statement
      </a>
    </li>
    <li>
      <a href="https://www.gs.unsw.edu.au/policy/documents/plagiarismprocedure.pdf">
        Plagiarism Procedure
      </a>
    </li>
  </ul>

  <p>You should also read the following page which describes your rights and responsibilities in the CSE context:</p>
  <ul>
    <li>
      <a href="https://www.engineering.unsw.edu.au/computer-science-engineering/about-us/organisational-structure/student-services/policies/essential-advice-for-cse-students">
        Essential Advice for CSE Students
      </a>
    </li>
  </ul>
</body>
</html>

