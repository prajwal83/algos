-----------
Assumptions
-----------
1. Distance between stations is positive integer > 0
2. Duplicate edges not allowed
3. Self loop edge not allowed
4. Distance must be greater than 0
5. trip count calculation is supported only for conditions <= and = by either number of stops or by total distance
6. Only positive integer > 0 is allowed for specifying stops or distance limit for trip count calculation
7. Input station/node name is taken as a single alphabetic character - though the design can take variable length station/node name - which will only require change to input format and parsing logic

------
TODO
------
1. Query results for trip count query and also for route distance query can be cached similar to shortest path

------
Build
------
Use maven build tool to compile, test and package the binary. Check pom.xml for more details
mvn compile test
mvn package

The binary will be generated @ targets/trains-1.0-SNAPSHOT.jar

------
Input
------
First line of input must be graph definition
Further lines will be query that will be run on the graph generated from previous input
Three types of queries supported 
1. distance of <Station1> <Station2> .....
2. shortest path from <Station1> to <Station2>
3. trip count from <Station1> to <Station2> with stops <=|<|= <limit>
4. trip count from <Station1> to <Station2> with distance <=|<|= <limit>
Please take a look at sample_test_input.txt for reference

Blank lines and lines starting with # will be ignored

------
Run
------
There are 2 modes to run
1. Interactive mode
> java -jar targets/trains-1.0-SNAPSHOT.jar com.interview.thoughtworks Main -i
In this mode, you enter input from command line
The first input line shoudl be Graph definition
Then enter query in the format as explained above

2. file input mode
> java -jar targets/trains-1.0-SNAPSHOT.jar com.interview.thoughtworks Main -f <file path>
example: java -jar targets/trains-1.0-SNAPSHOT.jar com.interview.thoughtworks Main -f sample_test_input.txt
In this mode you can feed graph definition and all the queries in a single file

------
Output will be displayed on terminal