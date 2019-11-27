
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html hola_ext_inject="disabled">
<head>
  <meta http-equiv="Content-Type" content="text/html;">
  <script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.4/MathJax.js?config=TeX-MML-AM_CHTML" async></script>

  <link rel="stylesheet" href="./styles/bootstrap.css">
  <link rel="stylesheet" href="./styles/style1.css" media="screen">
  <link rel="stylesheet" href="./styles/style_ass2_specs.css" media="screen">

  <title>COMP2521 Assignment 2</title>
</head>

<body class="container text-justify" style="max-width: 1000px;">
  
  <div align="center">
    <h2>
      <span style="font-size:18pt">COMP2521: Assignment 2</span>
      <br>
      <span style="font-size:22pt">Social Network Analysis</span>
    </h2>
    <p>
      A notice on the class web page will be posted after each major revision.
      Please check the class notice board and this assignment page frequently (for Change Log). 
      The specification may change.
    </p>
  </div>

  <div style='border-left:2px solid lightgrey; margin: 2px 30px; padding: 0px 10px; font-size:0.9em;'>
    <div style="font-weight:bold; color: dodgerblue;">FAQ:</div>
    <p>You should check <a target="_blank" href="faq.html">Ass2 FAQ</a>, it may offer answers to your queries!</p>

    <div style="font-weight:bold; color: dodgerblue;">
      Change log:
    </div>
    <ul>
      <li>07:15pm Thursday 14/Nov: Instructions on "how to submit" your assignment are now available, 
      go to the <a href="http://www.cse.unsw.edu.au/~cs2521/19T3/assigns/ass2/index.html#Submission">
      Sumission</a> section.</li>
    </ul>
  </div>

  <h2>Objectives</h2>
  <ul>
    <li>to implement graph based data analysis functions (ADTs) to mine a given social network. 
    <li>to give you further practice with C and data structures (Graph ADT)
  </ul>

  <h2>Admin</h2>
  <table border="0" cellpadding="4"  style="margin-left:40px;">
    <tbody style="font-size: 11pt; border:1px dotted lightgrey;">
      <tr valign="top">
        <td><b>Marks</b></td>
        <td>
          20 marks <small>(<span class=" ">scaled to 14 marks</span> towards total course mark)</small>
        </td>
      </tr>
      <tr valign="top">
        <td><b>Individual Assignment</b></td>
        <td>This assignment is an <b>individual</b> assignment.</td>
      </tr>
      <tr valign="top">
        <td><b>Due</b></td>
        <td>08:00pm Friday 22 November 2019</td>
      </tr>
      <tr valign="top">
        <td><b>Late<br>Penalty</b></td>
        <td>
          2 marks per day off the ceiling.<br>
          Last day to submit this assignment is 8pm Monday 25 November 2019, of course with late penalty.
        </td>
      </tr>
      <tr valign="top">
        <td><b>Submit</b></td>
        <td>TBA 
            <!--
                <code>give cs2521 assign2</code><br/>
                Read instructions in the <a href="#Submission">"Submission"</a> section below.
            -->
        </td>
      </tr>
    </tbody>
  </table>


  <h2>Aim</h2>

  <p>
    In this assignment, your task is to implement graph based data analysis functions (ADTs) to mine a given social network. For example, detect say "influenciers", "followers", "communities", etc. in a given social network.
    You should start by reading the Wikipedia entries on these topics. Later I will also discuss these topics in the lecture.
  </p>
  
  <ul>
    <li><a target="_blank" href="https://en.wikipedia.org/wiki/Social_network_analysis" target="_blank">Social network analysis</a></li>
    <li><a target="_blank" href="https://en.wikipedia.org/wiki/Centrality">Centrality</a></li>
  </ul>

  <p>
    The main focus of this assignment is to calculate measures that could identify say "influenciers", "followers", etc., and also discover possible "communities" in a given social network. 
  </p>


  <h2>Dos and Don'ts !</h2>
  <p>Please note that,
    <ul>
      <li>For this assignmet you can use source code that is available as part of the course material (lectures, exercises, tutes and labs). However, you must properly acknowledge it in your solution.</li>
      <li>All the required code for each part must be in the respective <tt>*.c</tt> file.</li>
      <li>You may implement additional helper functions in your files, please declare them as "static" functions.</li>
      <li>After implementing Dijkstra.h, you can use this ADT for other tasks in the assignment. However, please note that for our testing, we will use/supply our implementation of Dijkstra.h. So your programs MUST NOT use any implementation related information that is not available in the respective header files (<tt>*.h</tt> files). In other words, you can only use information available in the corresponding <tt>*.h</tt> files. </li>
      <li>Your program must not have any "main" function in any of the submitted files.</li>
      <li>Do not submit any other files. For example, you do not need to submit your modified test files or <tt>*.h</tt> files.</li>
      <li>If you have not implemented any part, must still submit an empty file with the corresponding file name.</li>
    </ul>.  
  </p>

  <p></p>

  <h2>Provided Files</h2>
  <p>
  We are providing implementations of <tt>Graph.h</tt> and <tt>PQ.h</tt> . 
  You can use them to implement all three parts. 
  However, your programs MUST NOT use any implementation related information 
  that is not available in the respective header files (*.h files). 
  In other words, you can only use information available in 
  the corresponding <tt>*.h</tt> files.

  <p>
  Also note: </p>
  <ul>
      <li>all edge weights will be greater than zero.</li>
      <li>we will not be testing  reflexive and/or self-loop edges. </li>
      <li>we will not be testing the case where the same edge is inserted twice.</li>
  </ul>
   
<p>Download files: </p>   
<ul>
	<li><a href="Ass2_files.zip">Ass2_files.zip</a></li>
	<li><a href="Ass2_Testing.zip">Ass2_Testing.zip</a></li>
</ul>
   
  </p>


  <h2>Part-1: Dijkstra's algorithm</h2>
  <p>In order to discover say "influencers", we need to <b>repeatedly</b> find shortest paths between <b>all pairs</b> of nodes. 
      In this section, you need to implement Dijkstra's algorithm to discover shortest paths from a given source to all other 
      nodes in the graph. 
  The function offers one important <b>additional feature</b>, the function keeps track of <b>multiple predecessors for 
  a node </b> on shortest paths from the source, if they exist.  
  In the following example, while discovering shortest paths from source node '0', we 
  discovered that there are two possible shortests paths from node '0' to node '1' (<tt><span style="color:red;">0</span>->1</tt> 
  OR <tt>0-><span style="color:red;">2</span>->1</tt>), 
  so  node '1' has two possible predecessors (node '0' or node '2') on possible shortest paths, as shown below.  
  <p>
  We will discuss this point in detail in a lecture. The basic idea is,  the array of lists ("<tt>pred</tt>") 
  keeps one linked list per node, and 
  stores multiple predecessors (if they exist) for that node on shortest paths from a given source. 
  In other words, for a given source, each linked list in "<tt>pred</tt>" offers possible predecessors for the corresponding node.  
  </p>
  </p>
  <table style="margin-left: 85px; border: none;"  >
      <tr>
          <td style="border: none;">
              <img style="margin-left:60px; height:140px; " src="http://www.cse.unsw.edu.au/~cs2521/19T3/assigns/ass2/pics/ass2_graph3.png">
          </td>
          <td style="border: none;">
              <pre style="font-size:0.8em;">
                  Node 0
                    Distance
                      0 : X
                      1 : 2
                      2 : 1
                    Preds
                      0 : NULL
                      <span style="background-color: yellow;" >1 : [0]->[2]->NULL </span>
                      2 : [0]->NULL
                  
                  Node 1
                    Distance
                      0 : 2
                      1 : X
                      2 : 3
                    Preds
                      0 : [1]->NULL
                      1 : NULL
                      2 : [0]->NULL
                  
                  Node 2
                    Distance
                      0 : 3
                      1 : 1
                      2 : X
                    Preds
                      0 : [1]->NULL
                      1 : [2]->NULL
                      2 : NULL
               </pre> 
          </td>
      </tr>
  </table>
    

  <p>
  The function returns 'ShortestPaths' structure with the required information
   (i.e. 'distance' array, 'predecessor' arrays, source and no_of_nodes in the graph)
      
  </p>

  <p style="margin-top:30px; margin-left:30px;">
  <span class='taskTitle'>Your task:</span> 
  In this section, you need to implement the following file:
  <ul>
  <li><tt>Dijkstra.c</tt> that implements all the functions defined in 
  <tt><a target="_blank" href="Ass2_files/Dijkstra.h">Dijkstra.h</a></tt>.
  </ul>
   
  </p>

  <h2>Part-2: Centrality Measures for Social Network Analysis</h2>
  <p>
  Centrality measures play very important role in analysing a social network. For example, nodes with higher "betweenness" measure often correspond to "influencers" in the given social network. In this part you will implement two well known centrality measures for a given directed weighted graph. 

  <p>Descriptions of some of the following items are from Wikipedia at <a  target="_blank" href="https://en.wikipedia.org/wiki/Centrality">Centrality</a>, adapted for this assignment. 
  </p>

  <h3>Closeness Centrality</h3>
  <p>
  Closeness centrality (or closeness) of a node is calculated as the sum of the length of the shortest paths between the node (\(x\)) and all other nodes (\(y \in V \land y \ne x\)) in the graph. Generally closeness is defined as below,
  <p>
    $$ C(x)= {1 \over \sum_{y} d(y, x) }.$$

  where  \( d(y,x) \)  is the shortest distance between vertices \(x \) and \(y\). 
  </p>

  <p>
  However, considering most likely we will have isolated nodes, <b>for this assignment</b> you need to 
  <b>use Wasserman and Faust formula</b> to calculate closeness of a node in a directed graph as described below: 
  <p>
    $$ C_{WF}(u)= { n - 1 \over N - 1 } * { n - 1 \over \sum_{all\ v\ reachable\ from\ u} d(u,v) }.$$

  where  \( d(u,v) \)  is the shortest-path distance in a directed graph from vertex \(u\) to \(v\),
   \(n\) is the number of nodes that \(u\) can reach, and \(N\) denote the number of nodes in the graph. 
  </p>

  <p class=" ">For further explanations, please read the following document, it may answer many of your questions! </p>
      <ul>
          <li> <a class="hlt1" target="_blank" href="ExplanationsPart2.html">Explanations for Part-2</a>  </li>
      </ul>
  <p>
  Based on the above, the more central a node is, the closer it is to all other nodes.
  For for information, see Wikipedia entry on <a  target="_blank" href="https://en.wikipedia.org/wiki/Closeness_centrality">Closeness centrality</a>.
  <p></p>


  <h3>Betweenness Centrality</h3>

  <p>The betweenness centrality of a node \(v\) is given by the expression:
  <div style="margin-left:100px;">
  $$ g(v)=\sum _{{s\neq v\neq t}}{\frac  {\sigma _{{st}}(v)}{\sigma _{{st}}}}   $$
  </div>
  <p>
  where \(\sigma_{st}\) is the total number of shortest paths from node  \(s\) to node  \(t\) and \(\sigma_{st}(v)\) is the number of those paths that pass through \(v\).

  <div>
  <p>
  For this assignment, use the following approach to calculate normalised betweenness centrality. It is easier! and also avoids zero as denominator (for n>2). 

  <div class=" ">
  <div style="margin-left:100px;">
  $$ {\mbox{normal}}(g(v))= {\frac {1}{((n-1)(n-2))} } *{g(v)} $$
  </div>
  <p>
  where, \(n\) represents the number of nodes in the graph.
  </p>
  <p>For further explanations, please read the following document, it may answer many of your questions! </p>
      <ul>
          <li> <a class="hlt1" target="_blank" href="ExplanationsPart2.html">Explanations for Part-2</a>  </li>
      </ul>
  </p>
  </div> 
  </div>

  <p>

  <p style="margin-top:40px; margin-left:30px;">
  <span class='taskTitle'>Your task:</span> 
  In this section, you need to implement the following file:
  <ul>
  <li><tt>CentralityMeasures.c</tt> that implements all the functions defined in <tt><a target="_blank" href="Ass2_files/CentralityMeasures.h">CentralityMeasures.h</a></tt>.
  </ul>
  </p>

  <p style="margin-top:30px;">
  For more information, see Wikipedia entry on <a  target="_blank" href="https://en.wikipedia.org/wiki/Betweenness_centrality">Betweenness centrality
  </a>
  <p>

  <p><p>

  <h2>Part-3: Discovering Community </h2>
  <div class="  ">
  <p>

  In this part you need to implement the Hierarchical Agglomerative Clustering (HAC) algorithm to discover communities in a given graph. In particular, you need to implement Lance-Williams algorithm, as described below. In the lecture we will discuss how this algorithm works, and what you need to do to implement it. You may find the following document/video useful for this part:

  <ul>
  <li><a target="_blank"  href="https://en.wikipedia.org/wiki/Hierarchical_clustering">Hierarchical Clustering</a> (Wikipedia), for this assignment we are interested in only "agglomerative" approach.
  <li> Brief <a target="_blank"  href="OverviewHacLanceWilliams.pdf">overview of algorithms for hierarchical clustering</a>, including Lance-Williams approach (pdf file).
  <li> Three videos by Victor Lavrenko, watch in sequence!
  <ul>
  <li> <a target="_blank" href="https://www.youtube.com/watch?v=XJ3194AmH40">Agglomerative Clustering: how it works</a>
  <li> <a target="_blank" href="https://www.youtube.com/watch?v=VMyXc3SiEqs">Hierarchical Clustering 3: single-link vs. complete-link</a>
  <li> <a target="_blank" href="https://www.youtube.com/watch?v=aXsaFNVzzfI&t=6s">Hierarchical Clustering 4: the <b>Lance-Williams algorithm</b></a> 
  </ul>
  </ul>
  </p>

  <p><b>Distance measure:</b> For this assignment, we calculate distance between a pair of vertices as follow:
  Let \(wt\) represents maximum edge weight of all available weighted edges between a pair of vertices \(v\) and \(w\). 
  Distance \(d\) between vertices \(v\) and \(w\) is defined as \(d = 1/wt\). If \(v\) and \(w\) are not connected, \(d\) is infinite. 
  <p>
  For example, if there is one directed link between \(v\) and \(w\) with weight \(wt\), the distance between them is \(1/wt\). If there are two links, between \(v\) and w, we take maximum  of the two weights and the distance between them 
  is \(1/max(wt_{vw}, wt_{wv})\). Please note that, one can also consider alternative approaches, like take average, min, etc. However, we need to pick one approach for this assignment and we will use the above distance measure.  
  <p>
  <p>You need to use the following (adapted) Lance-Williams HAC Algorithm to derive a dendrogram: 
  <p>

  <ul class=" clPre1" >
  <li> Calculate distances between each pair of vertices as described above. 
  <li> Create clusters for every vertex \(i\), say \(c_{i}\).
  <li> Let \(Dist(c_{i},c_{j})\) represents the distance between cluster \(c_{i}\) and \(c_{j}\), initially it represents distance between vertex \( i \) and \( j \) .
  <li> For k = 1 to N-1
  <ul class="dashed">
  <li>     Find two closest clusters, say \(c_{i}\) and \(c_{j}\). If there are multiple alternatives, 
		    you can select any one of the pairs of closest clusters.  
  <li>     Remove clusters \(c_{i}\) and \(c_{j}\) from the collection of clusters and  
           add a new cluster \(c_{ij}\) (with all vertices in \(c_{i}\) and \(c_{j}\)) to the collection of clusters.
  <li>     Update dendrogram.
  <li>     Update distances, say \(Dist(c_{ij},c_{k})\), between the newly added cluster \(c_{ij}\) and 
		   the rest of the clusters (\(c_{k}\)) in the collection using Lance-Williams formula using the selected method
           ('<i>Single linkage</i>' or '<i>Complete linkage</i>' - see below).
  </ul>
  <li>  End For 
  <li>  Return dendrogram 
       
  </ul>

  </p>

  <p>


  <div class=" clPre1" style="margin-left:40px;">
  <b>Lance-Williams formula:</b> <br>
  $$ Dist(c_{ij},c_{k}) = \alpha_{i} * Dist(c_{i},c_{k}) +  \alpha_{j} * Dist(c_{j},c_{k}) + \beta * Dist(c_{i},c_{j}) + \gamma * abs(Dist(c_{i},c_{k}) - Dist(c_{j},c_{k})  ) 
  $$

  where \(\alpha_{i}\), \(\alpha_{j}\), \(\beta\), and \(\gamma\) define the agglomerative criterion. 

  <div style="border:1px dotted grey;padding:  10px;margin: 10px;border-radius: 10px; font-size:0.9em;" >
  For the <i>Single link method</i>, these values are:
   \(\alpha_{i} = 1/2 \), \(\alpha_{j} = 1/2 \), \(\beta = 0\), and \(\gamma = -1/2 \). Using these values, the formula for Single link method is:
  $$ Dist(c_{ij},c_{k}) = 1/2 * Dist(c_{i},c_{k}) +  1/2 * Dist(c_{j},c_{k}) -1/2 * abs(Dist(c_{i},c_{k}) - Dist(c_{j},c_{k})  ) 
  $$

  We can simplify the above and re-write the formula for <b>Single link method</b> as below <br>
  $$ Dist(c_{ij},c_{k}) = min ( Dist(c_{i},c_{k}), Dist(c_{j},c_{k}) ) $$ 
  </div>


  <div style="border:1px dotted grey;padding:  10px;margin: 10px;border-radius: 10px; font-size:0.9em;">
  For the <i>Complete link method</i>, the values are:
   \(\alpha_{i} = 1/2 \), \(\alpha_{j} = 1/2 \), \(\beta = 0\), and \(\gamma = 1/2 \). Using these values, the formula for Complete link method is:
  $$ Dist(c_{ij},c_{k}) = 1/2 * Dist(c_{i},c_{k}) +  1/2 * Dist(c_{j},c_{k}) + 1/2 * abs(Dist(c_{i},c_{k}) - Dist(c_{j},c_{k})  ) 
  $$

  We can simplify the above and re-write the formula for <b>Complete link method</b> as below <br>
  $$ Dist(c_{ij},c_{k}) = max ( Dist(c_{i},c_{k}), Dist(c_{j},c_{k}) ) $$ 
  </div>
  </div>

  <p> Please see the following simple example, it may answer many of your questions!

  <ul>
  <li><a class="hlt1"  href="part-3-example.xlsx">Part-3 Simple Example</a> (MS Excel file)
  </ul>
  </p>

  <p style="margin-top:40px; margin-left:30px;">
  <span class='taskTitle'>Your task:</span> 
  In this section, you need to implement the following file:
  <ul>
  <li><tt>LanceWilliamsHAC.c</tt> that implements all the functions defined in <tt><a target="_blank" href="Ass2_files/LanceWilliamsHAC.h">LanceWilliamsHAC.h</a></tt>.
  </ul>
  </p>

  </div>

  <h2>Assessment Criteria</h2>
  <ul>

  <li>Part-1: Dijkstra's algorithm (20% marks)

  <li>Part-2: 
  	<ul>
	  <li>Closeness Centrality (22% marks), 
	  <li>Betweenness Centrality (23% marks)
	  </ul>
  <li>Part-3: Discovering Community (15% marks)
  <li>Style, Comments and Complexity: 20%
  </ul>



  <h2 id="testing">Testing</h2>
  <p class="  ">

  <p>
  Please note that <b>testing</b> an API implementation is 
  <b>very important and crucial</b> part of 
  designing and implementing an API.  

  We offer the following testing interfaces (for all the APIs you need to implement) 
  for you to get started, 
  however note that they <b>only test basic cases. Importantly,</b> 
  <ul>
  <li>you need to add more advanced test cases and properly test your API implementations, 
  <li>the auto-marking program will use more advanced test cases that are not 
  included in the test cases provided to you. </li>
  </ul>

  <p>Instructions on how to test your API implementations are available on the following page:
  <ul>
  <li><a target="_blank" href="TestingInstructions.html">Testing your API Implementations</a>
  </ul>
  <p>
          
  </p>
  

  <a name="Submission"></a>
  <h2>Submission </h2>
  <div >

  <p>You need to submit the following five files:
  </p>
  <ul>
	  <li>Dijkstra.c</li>
	  <li>CentralityMeasures.c</li>
	  <li>LanceWilliamsHAC.c</li>
  </ul>

<!--
  <p><b>Submission instructions</b> on how to submit the above five files will be <b>available later</b>. 
-->


  <p>You can now submit the above three files, go to:  <a target="_blank" href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/resources/32223"> Assignment-2 Submission page, click the tab named "Make Submission"</a>

  <p>
  You can also submit at the command-line, by running

  <pre><b>give cs2521 assign2</b></pre>

  <p>

  <p>As mentioned earlier, please note that,
          <ul>
              <li>all the requried code for each part must be in the respective <tt>*.c</tt> file.</li>
              <li>you may implement addition helper functions in your files, please declare them as "static" functions.</li>
              <li>after implementing Dijkstra.h, you can use this ADT for the other tasks in the assignment. 
                  However, please note that for our testing, we will use/supply our implementations of Graph.h,  PQ.h and Dijkstra.h. 
                  So your programs MUST NOT use any implementation related information that is not available in the respective 
                  header files (<tt>*.h</tt> files). In other words, you can only use information available in the corresponding <tt>*.h</tt> files.  </li>
              <li>your program must not have any "main" function in any of the submitted files. </li>
              <li>do not submit any other files. For example, you do <b>not</b> need to submit your modified test files or <tt>*.h</tt> files.</li>
              <li>If you have <b>not implemented</b> any part, you need to <b>still submit an empty file</b> with the corresponding file name.</li>    
          </ul>.  
      </p>

  <p>
  </div>

  <h2>Plagiarism</h2>
  <p>This is an individual assignment. Each student will have to develop their own solution without help from other people. You are not permitted to exchange code or pseudocode. If you have questions about the assignment, ask your tutor. All work submitted for assessment must be entirely your own work. We regard unacknowledged copying of material, in whole or part, as an extremely serious offence. For further information, read the <a href="https://webcms3.cse.unsw.edu.au/COMP2521/19T3/outline" target="_blank">Course Outline</a>.</p>
  
  <hr>
  <p style="text-align: center"> -- end -- </p>
</body>
</html>

