# Parallelizing-Prim-s-Algorithm-for-MST
# External Libraries: 
Libraries of C programming and CUDA libraries like Thrust

# Programming Language AND Hardware Details:
The programming language used for the implementation of is C++. 
The hardware details of the system are -
CPU - INTEL(R) core(TM)i5 - 7200CPU   
GPU - NVIDIA GeForce 940 MAX 8GB
The parallelization of the algorithm is done by using Compute Unified Device Architecture (CUDA).


# Application details and Design Decision:
Prims Algorithm is an algorithm which belongs to Greedy algorithm family for finding minimum spanning tree or minimum cost for traversing of all nodes of a weighted undirected graph. In a Greedy algorithm, we always starts with a random value and then find the all connected entities and choose the minimum of them  for traversing and then use  that minimum in next iteration to find next to next minimum and so on until we iterate through whole data sets.
 We implement the serial Prim’s algorithm using the Priority Queue and then in parallel version used the thrust library to sort the data structure to find the minimum weight.
 
 
# Discussions and Conclusion:
After the analysis of output we observe that the for the same set of input, the result is same and the main difference is came in execution time. For a small random unweight graph having 9 nodes and 14 edges of the execution time for sequential program is 0.037 while the execution time of the parallelized program is 0.013. The execution time could be much better and significant improves can be achieved for graphs having very large no of nodes and edges like road transportation graph of an country with using more powerful GPU Device.


