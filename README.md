# Data Structures and Algorithms Assessment

*tldr; Created a cli predictive text system and achived a mark of 84%*
## Task: Predictive Text

Here is the [*pdf*](http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/Assessment/DSAAssessment2016.pdf) that outlines the assessment. It's unlikely that you'll be able to view this files so here is the basic outline of the assessment 

> You are to design and implement a program that can perform a predictive text function similar to
that employed in modern mobile phones.

> The program should allow the user to type text into the command prompt. If the user presses a
special key, such as tab, the program should make a number of suggestions which complete the
current word. The user should then have the choice to select one of the suggested words, or continue
typing.

> A text file called words.txt containing a list of 25,143 words is provided [here](http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/Assessment/words.txt) on the [course web
page](http://www.elec.york.ac.uk/internal_web/meng/yr2/modules/DSA/DSA/).

> Your program should read the contents of words.txt into a suitable data structure that allows
efficient storage and search. You will need to think about efficient ways of matching entered letter
sequences from the keyboard to complete words found in words.txt. Merely putting all the words in
a single list and searching through the entire list for matches linearly would be a very inefficient
solution. Programs that choose appropriate data structures and algorithms that make the predictive
text system efficient will receive higher marks. Consideration of how to enable punctuation and
capitalisation will also be welcomed.

## Marking Guidelines
The marks are broken down into the following categories:

### Choice of Data Structure (6)  
* Space complexity (with respect to size of dictionary) 2  
* Time complexity (with respect to size of dictionary) 2  
* Simplicity of data structure 2  

### Program Implementation (20)  
* Representational independence (interface and implementation separation) 3  
* Modularity of program (at least three program files with appropriate contents) 2  
* Functional modularity (program broken up into an appropriate series of functions) 3  
* Program documentation (commenting, formatting, suitable names of variables etc) 2  
* Clarity and simplicity of program (good program structure, logical flow) 3  
* Execution (how well does the actual program work) 3  
* Completeness (how complete is the submitted program, how functional) 2  
* User interface 2  

### Report (24)  
* Explanation of program 8  
* Explanation of data structure chosen and discussion of alternatives 10  
* Readability and formatting 4  
*Testing strategy (how did you test your design?) 2  

## My submition

### Source
The submitted source code is under the 'release/submitted' branch and is the release tagged as 'submitted'

### Report 
The [pdf of the report](https://github.com/zwrawr/DSA_Assessment/blob/master/Report/DSA_AssesmentReport.pdf) can be found here.

## Results
I obtained 84% for this assessment which is a starred first.

