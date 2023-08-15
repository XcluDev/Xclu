Variable can be a link. Variants:
* `webcamera1->image` 
 Link to a module's `webcamera1` value `image`.

* `module1->line(2)` 
link to a module's `module1` value `line`, interpreted as a string separated by spaces, and getting its *third* item `c` from it (numeration from 0). 
For string `a b c d`  it returns `c`.

* `module1->line(2,3)`
link to a module's `module1` value `line`, interpreted as a strings separated by new line symbols and spaces, and getting its *third* line, *fourth* item from it (numeration from 0).
For strings 
`a1 a2 a3 a4`    
`b1 b2 b3 b4`    
`c1 c2 c3 c4`    
it returns `c4`.